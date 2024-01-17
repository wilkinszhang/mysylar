#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include<memory>
#include<functional>
#include<ucontext.h>
// #include"thread.h"

namespace sylar{

class Fiber : public std::enable_shared_from_this<Fiber>{
friend class Scheduler;
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State{
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };
private:
    Fiber();
public:
    Fiber(std::function<void()> cb,size_t stacksize=0,bool use_caller=false);
    ~Fiber();
    //重置携程函数，并重置状态
    void reset(std::function<void()> cb);
    //切换到当前携程执行
    void swapIn();
    void call();
    void back();
    //切换到后台（主线程）执行
    void swapOut();
    uint64_t getId()const{return m_id;}
    State getState()const{return m_state;}
public:
    static void SetThis(Fiber* f);
    //返回当前线程
    static Fiber::ptr GetThis();
    //携程切换到后台，并设置为Ready
    static void YieldToReady();
    //携程切换到后台，并设置为Hold
    static void YieldToHold();
    //总携程数
    static uint64_t TotalFibers();
    static uint64_t GetFiberId();

    static void MainFunc();
    static void CallerMainFunc();

private:
    uint64_t m_id=0;
    uint32_t m_stacksize=0;
    State m_state=INIT;
    ucontext_t m_ctx;
    void* m_stack=nullptr;
    std::function<void()> m_cb;
};

}

#endif