#include <functional>
#include"scheduler.h"
#include"log.h"
#include"macro.h"
#include"fiber.h"

namespace sylar{

static sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}

static thread_local Scheduler* t_scheduler=nullptr;
static thread_local Fiber* t_scheduler_fiber=nullptr;

Scheduler::Scheduler(size_t threads,bool use_caller,const std::string& name)
    :m_name(name){
// 这部分代码正在初始化一个“Scheduler”对象，该对象用于管理线程和携程（轻量级线程）。
// 以下是每行的详细说明：
// 1. `sylar::Fiber::GetThis();` 此行获取代码正在运行的当前 Fiber（轻量级线程）。 看起来这条线是因为它的副作用而被调用的，可能会设置一些全局或线程本地状态。
// 2. `--threads;` 这一行将 `threads` 变量减 1。这样做是因为当前线程被用作调度程序的一部分，因此需要创建的附加线程的数量会减少 一。
// 3. `SYLAR_ASSERT(GetThis() == nullptr);` 这一行断言当前线程还没有与其关联的 `Scheduler`。
// 4. `t_scheduler = this;` 这行代码将当前线程的 `Scheduler` 设置为这个 `Scheduler` 对象。
// 5. `m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));` 这行代码创建一个新的 `Fiber` 来运行 `Scheduler::run` 函数 ，并将其设置为“调度程序”的根纤维。
// 6. `sylar::Thread::SetName(m_name);` 这一行将当前线程的名称设置为 `Scheduler` 的名称。
// 7. `t_scheduler_ Fiber = m_rootFiber.get();` 这一行将当前线程的携程设置为 `Scheduler` 的根携程。
// 8. `m_rootThread = sylar::GetThreadId();` 这一行将 `Scheduler` 的根线程设置为当前线程的 ID。
// 9. `m_threadIds.push_back(m_rootThread);` 这行代码将根线程的 ID 添加到 `Scheduler` 管理的线程 ID 列表中。
// 因此，总而言之，这部分代码是将 `Scheduler` 配置为使用当前线程，并设置根携程来运行 `Scheduler::run` 函数。

// `std::bind` 函数是 C++ 中的一个标准库函数，它生成一个新函数对象，将一个或多个参数“绑定”到特定值或占位符。 这可用于将采用多个参数的函数调整为采用较少参数的函数对象。
// 这是一个简单的例子：
// ````cpp
// void print_sum(int a, int b) {
//      std::cout << a + b << std::endl;
// }
// int main() {
//      自动bound_print_sum = std::bind(print_sum, 5, std::占位符::_1);
//      绑定打印总和（10）； // 打印 15
//      返回0；
// }
// ````
// 在此示例中，“std::bind(print_sum, 5, std::placeholders::_1)”创建一个带有一个参数的新函数对象“bound_print_sum”。 当使用参数调用此函数对象时，它会调用“print_sum”，第一个参数固定为“5”，第二个参数固定为传递给“bound_print_sum”的任何参数。
// 在您的代码中，“std::bind(&Scheduler::run, this)”创建一个函数对象，在调用该函数对象时，将调用“this”指向的“Scheduler”对象上的“run”方法。 这用于创建一个“Fiber”，它将在执行时运行“Scheduler::run”方法。
    SYLAR_ASSERT(threads>0);
    if(use_caller){
        sylar::Fiber::GetThis();
        --threads;
        
        SYLAR_ASSERT(GetThis()==nullptr);
        t_scheduler=this;

        // SYLAR_LOG_INFO(GetLogger())<<"构造函数 run绑定";
        m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));
        sylar::Thread::SetName(m_name);

        t_scheduler_fiber=m_rootFiber.get();
        m_rootThread=sylar::GetThreadId();
        m_threadIds.push_back(m_rootThread);
    }
    m_threadCount=threads;
}
Scheduler::~Scheduler(){
    SYLAR_ASSERT(m_stopping);//确保调度程序执行时不会被析构
    if(GetThis()==this){
        t_scheduler=nullptr;
    }
}

Scheduler* Scheduler::GetThis(){
    return t_scheduler;
}

Fiber* Scheduler::GetMainFiber(){
    return t_scheduler_fiber;
}

void Scheduler::start(){
    MutexType::Lock lock(m_mutex);
    if(!m_stopping){//如果调度程序没有停止，返回
        return;
    }
    m_stopping=false;
    SYLAR_ASSERT(m_threads.empty());//确保调度程序不会用上次剩余的线程
    // SYLAR_LOG_DEBUG(GetLogger())<<"m_threadCount="<<m_threadCount;
    m_threads.resize(m_threadCount);
    // SYLAR_LOG_INFO(GetLogger())<<"start run绑定";
    for(size_t i=0;i<m_threadCount;++i){
        m_threads[i].reset(new Thread(std::bind(&Scheduler::run,this),m_name+"_"+std::to_string(i)));
        m_threadIds.push_back(m_threads[i]->getId());
    }
    // 这会将“m_threads”向量的大小调整为“m_threadCount”中指定的线程数。 然后它为调度程序中的每个线程创建一个新的“Thread”对象。 `Thread` 对象绑定到 `Scheduler` 类的 `run()` 方法，这意味着当线程启动时，它将执行调度程序的 `run()` 方法。 每个线程的名称是调度程序的名称，后跟线程号。 然后，每个线程的 ID 存储在“m_threadIds”中。
    lock.unlock();

    if(m_rootFiber){
        // m_rootFiber->swapIn();
        m_rootFiber->call();
    }

}
void Scheduler::stop(){
    m_autoStop=true;
    if(m_rootFiber//有主线程
        &&m_threadCount==0//没有活动线程？
        &&(m_rootFiber->getState() == Fiber::TERM
            ||m_rootFiber->getState() == Fiber::INIT)){
        SYLAR_LOG_INFO(GetLogger())<< this << " stopped";
        m_stopping=true;

        if(stopping()){//检查调度程序是否正在停止
            return;
        }
    }

    if(m_rootThread!=-1){
        SYLAR_ASSERT(GetThis()==this);
    }else{
        SYLAR_ASSERT(GetThis()!=this);
    }

    m_stopping=true;
    for(size_t i=0;i<m_threadCount;++i){
        tickle();//通知线程们，调度程序要停止
    }

    if(m_rootFiber){
        tickle();
    }

    if(m_rootFiber){
        if(!stopping()){
            m_rootFiber->call();
        }
    }

    // std::vector<Thread::ptr> thrs;
    // {
    //     MutexType::Lock lock(m_mutex);
    //     thrs.swap(m_threads);
    // }
    // for(auto & i:thrs){
    //     i->join();
    // }
}

void Scheduler::setThis(){
    t_scheduler=this;
}

void Scheduler::run(){
    // SYLAR_LOG_INFO(GetLogger())<<m_name<<" Scheduler::run()";
    setThis();//把当前线程设置为线程段读程序
    if(sylar::GetThreadId()!=m_rootThread){
        t_scheduler_fiber=Fiber::GetThis().get();
    }
    
    Fiber::ptr idle_fiber(new Fiber(std::bind(&Scheduler::idle,this)));
    Fiber::ptr cb_fiber;

    Scheduler::FiberAndThread ft;
    while(true){
        ft.reset();
        bool tickle_me=false;
        bool is_active=false;
        {
            MutexType::Lock lock(m_mutex);//锁定任务队列m_fibers
            auto it=m_fibers.begin();
            while(it != m_fibers.end()){
                if(it->thread!=-1 && it->thread!=sylar::GetThreadId()){
                    //其他携程可以再其他线程运行
                    ++it;
                    tickle_me=true;
                    continue;
                }

                SYLAR_ASSERT(it->fiber || it->cb);
                if(it->fiber && it->fiber->getState()==Fiber::EXEC){
                    ++it;
                    continue;
                }

                ft=*it;
                m_fibers.erase(it++);//把当前携程从队列中删除
                ++m_activeThreadCount;
                is_active=true;
                break;
            }
            tickle_me |= it!=m_fibers.end();
        }
        if(tickle_me){
            tickle();
        }
        if(ft.fiber && (ft.fiber->getState()!=Fiber::TERM
                        ||ft.fiber->getState()!=Fiber::EXCEPT)){
            ft.fiber->swapIn();
            --m_activeThreadCount;
            
            if(ft.fiber->getState()==Fiber::READY){
                //如果运行后仍处于就绪状态，则再次进行调度
                schedule(ft.fiber);
            }else if(ft.fiber->getState()!=Fiber::TERM
                    && ft.fiber->getState()!=Fiber::EXCEPT){
                ft.fiber->m_state=Fiber::HOLD;
            }
            ft.reset();
        }else if(ft.cb){//函数
            if(cb_fiber){
                cb_fiber->reset(ft.cb);
            }else{
                cb_fiber.reset(new Fiber(ft.cb));
            }
            ft.reset();
            cb_fiber->swapIn();
            --m_activeThreadCount;
            if(cb_fiber->getState()==Fiber::READY){
                schedule(cb_fiber);
                cb_fiber.reset();
            }else if(cb_fiber->getState()==Fiber::EXCEPT
                    ||cb_fiber->getState()==Fiber::TERM){
                cb_fiber->reset(nullptr);
            }else{
                cb_fiber->m_state=Fiber::HOLD;
                cb_fiber.reset();
            }
        }else{//idle携程
            if(is_active){
                --m_activeThreadCount;
                continue;
            }
            if(idle_fiber->getState()==Fiber::TERM){
                SYLAR_LOG_INFO(GetLogger())<<"idle fiber term";
                break;
            }
            //++m_idleThreadCount;
            idle_fiber->swapIn();
            //--m_idleThreadCount;
            if(idle_fiber->getState()!=Fiber::TERM
                &&idle_fiber->getState()!=Fiber::EXCEPT){
                idle_fiber->m_state=Fiber::HOLD;
            }
        }
    }

}

void Scheduler::tickle(){
    SYLAR_LOG_INFO(GetLogger())<<"tickle";
}
bool  Scheduler::stopping(){
    MutexType::Lock lock(m_mutex);
    return m_autoStop && m_stopping
        && m_fibers.empty() && m_activeThreadCount==0;
}
void  Scheduler::idle(){
    SYLAR_LOG_INFO(GetLogger())<<"idle";
}

}