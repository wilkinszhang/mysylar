#include"fiber.h"
#include"config.h"
#include"macro.h"
#include<atomic>
#include"log.h"

namespace sylar{

Logger::ptr GetLogger(){
    static Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}
static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber=nullptr;
static thread_local Fiber::ptr t_threadFiber=nullptr;

ConfigVar<uint32_t>::ptr GetFiberStackSize(){
    static ConfigVar<uint32_t>::ptr g_fiber_stack_size=
        Config::Lookup<uint32_t>("fiber.stack_size",1024*1024,"fiber stack size");
    return g_fiber_stack_size;
}

class MallocStackAllocator{
public:
    static void* Alloc(size_t size){
        return malloc(size);
    }
    static void Dealloc(void * vp,size_t size){//预留size
        return free(vp);
    }
};

using StackAllocator=MallocStackAllocator;//方便换成其他的分配器

Fiber::Fiber(){//主协程
    m_state=EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }
    ++s_fiber_count;
    SYLAR_LOG_DEBUG(GetLogger())<<"Fiber::Fiber main id="<<m_id
                                <<" total="<<s_fiber_count;
}

Fiber::Fiber(std::function<void()> cb,size_t stacksize)//子协程
    :m_id(++s_fiber_id),m_cb(cb){
    ++s_fiber_count;
    m_stacksize=stacksize?stacksize:GetFiberStackSize()->getValue();

    m_stack=StackAllocator::Alloc(m_stacksize);
    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }
    m_ctx.uc_link=nullptr;
    m_ctx.uc_stack.ss_sp=m_stack;
    m_ctx.uc_stack.ss_size=m_stacksize;

    makecontext(&m_ctx,&Fiber::MainFunc,0);
    SYLAR_LOG_DEBUG(GetLogger())<<"Fiber::Fiber id="<<m_id
                                <<" total="<<s_fiber_count;
}


Fiber::~Fiber(){
    --s_fiber_count;
    if(m_stack){
        std::cout<<"子协程"<<std::endl;
        SYLAR_ASSERT(m_state==TERM || m_state==INIT || m_state==EXCEPT);
        StackAllocator::Dealloc(m_stack,m_stacksize);
    }else{
        std::cout<<"主协程"<<std::endl;
        SYLAR_ASSERT(!m_cb);
        SYLAR_ASSERT(m_state==EXEC);

        Fiber* cur=t_fiber;
        if(cur==this){
            SetThis(nullptr);
        }
    }
    SYLAR_LOG_DEBUG(GetLogger())<<"Fiber::~Fiber id="<<m_id
                                <<" total="<<s_fiber_count;
}

//重置携程函数，并重置状态
void Fiber::reset(std::function<void()> cb){
    SYLAR_ASSERT(m_stack);
    SYLAR_ASSERT(m_state==TERM || m_state==INIT || m_state==EXCEPT);
    m_cb=cb;
    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }
    m_ctx.uc_link=nullptr;
    m_ctx.uc_stack.ss_sp=m_stack;
    m_ctx.uc_stack.ss_size=m_stacksize;

    makecontext(&m_ctx,&Fiber::MainFunc,0);
    m_state=INIT;
}
//切换到当前携程执行
void Fiber::swapIn(){
    SetThis(this);
    SYLAR_ASSERT(m_state!=EXEC);
    m_state=EXEC;
    if(swapcontext(&t_threadFiber->m_ctx,&m_ctx)){
        SYLAR_ASSERT2(false,"swapcontext");
    }
}
//切换到后台（主线程）执行
void Fiber::swapOut(){
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx,&t_threadFiber->m_ctx)){
        SYLAR_ASSERT2(false,"swapcontext");
    }
}
void Fiber::SetThis(Fiber* f){
    t_fiber=f;
}
//返回当前线程
Fiber::ptr Fiber::GetThis(){
    if(t_fiber){
        return t_fiber->shared_from_this();
    }
    Fiber::ptr main_fiber(new Fiber);
    SYLAR_ASSERT(t_fiber==main_fiber.get());
    t_threadFiber=main_fiber;
    return t_fiber->shared_from_this();
}
//携程切换到后台，并设置为Ready
void Fiber::YieldToReady(){
    Fiber::ptr cur=GetThis();
    SYLAR_ASSERT2(cur->m_state==EXEC,"YieldToReady error");
    cur->m_state=READY;
    cur->swapOut();
}
//携程切换到后台，并设置为Hold
void Fiber::YieldToHold(){
    Fiber::ptr cur=GetThis();
    SYLAR_ASSERT2(cur->m_state==EXEC,"YieldToHold error");
    cur->m_state=HOLD;//这里有问题，作者把这里注释了，但是我觉得应该是HOLD
    cur->swapOut();
}
//总携程数
uint64_t Fiber::TotalFibers(){
    return s_fiber_count;
}

uint64_t Fiber::GetFiberId(){
    if(t_fiber){
        return t_fiber->getId();
    }
    return 0;
}

void Fiber::MainFunc(){
    Fiber::ptr cur=GetThis();
    SYLAR_ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb=nullptr;
        cur->m_state=TERM;
    }catch(std::exception& ex){
        cur->m_state=EXCEPT;
        SYLAR_LOG_ERROR(GetLogger())<<"Fiber Except: "<<ex.what()
            <<" fiber_id="<<cur->getId()
            <<std::endl
            <<sylar::BacktraceToString();
    }catch(...){
        cur->m_state=EXCEPT;
        SYLAR_LOG_ERROR(GetLogger())<<"Fiber Except"
            <<" fiber_id="<<cur->getId()
            <<std::endl
            <<sylar::BacktraceToString();
    }
    //解决只执行主携程析构函数的问题,还有不打印携程执行完回不到main函数的问题
    auto raw_ptr=cur.get();
    cur.reset();
    raw_ptr->swapOut();
    SYLAR_ASSERT2(false, "never reach fiber_id=" + std::to_string(raw_ptr->getId()));
}

}