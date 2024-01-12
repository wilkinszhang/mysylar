#ifndef __SYLAR_SCHEDULER_H__
#define __SYLAR_SCHEDULER_H__
#include<memory>
#include<vector>
#include<list>
#include"fiber.h"
#include"thread.h"
// #include"mutex.h"

namespace sylar{

class Scheduler{
public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    //use_caller:是否将当前进程包含进去
    Scheduler(size_t threads=1,bool use_caller=true,const std::string& name="");
    virtual ~Scheduler();

    const std::string& getName() const {return m_name;}

    //当前协程调度器
    static Scheduler* GetThis();
    //调度器的主协程，和Fiebr.cpp里面的不太一样
    static Fiber* GetMainFiber();

    void start();
    void stop();

    template<class FiberOrCb>
    void schedule(FiberOrCb fc,int thread=-1){
        bool need_tickle=false;
        {
            MutexType::Lock lock(m_mutex);
            need_tickle=scheduleNoLock(fc,thread);
        }
        if(need_tickle){
            tickle();
        }
    }

    template<class InputIterator>
    void schedule(InputIterator begin,InputIterator end){
        bool need_tickle=false;
        {
            MutexType::Lock lock(m_mutex);
            while(begin!=end){
                need_tickle=scheduleNoLock(&*begin,-1)||need_tickle;
                //&*begin用迭代器获得裸指针
                begin++;
            }
        }
        if(need_tickle){
            tickle();
        }
    }
protected:
    virtual void tickle();
private:
    template<class FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc,int thread){
        bool need_tickle=m_fibers.empty();
        FiberAndThread ft(fc,thread);
        if(ft.fiber||ft.cb){//协程或者funcitonal
            m_fibers.push_back(ft);
        }
        return need_tickle;//true表示以前没有任务，都内核态
    }
private:
    struct FiberAndThread{
        Fiber::ptr fiber;
        std::function<void()> cb;
        int thread;

        FiberAndThread(Fiber::ptr f,int thr):fiber(f),thread(thr){
        }
        //swap函数，交换两个对象的内容,传入的f会变成空的
        FiberAndThread(Fiber::ptr* f,int thr):thread(thr){
            fiber.swap(*f);
        }
        FiberAndThread(std::function<void()> f,int thr):cb(f),thread(thr){

        }
        FiberAndThread(std::function<void()>*f,int thr):thread(thr){
            cb.swap(*f);
        }
        //stl容器分配对象需要有默认构造函数
        FiberAndThread():thread(-1){
        }

        void reset(){
            fiber=nullptr;
            cb=nullptr;
            thread=-1;
        }
    };
    
private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<FiberAndThread> m_fibers;
    std::string m_name;
};

}

#endif