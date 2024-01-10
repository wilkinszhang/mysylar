#include"../sylar/sylar.h"

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}

void run_in_fiber(){
    SYLAR_LOG_INFO(GetLogger())<<"run_in_fiber begin";
    sylar::Fiber::YieldToHold();
    SYLAR_LOG_INFO(GetLogger())<<"run_in_fiber end";
    sylar::Fiber::YieldToHold();
} 

int main(int argc,char** argv){
    SYLAR_LOG_INFO(GetLogger())<<"main begin -1";
    {
        sylar::Fiber::GetThis();
        SYLAR_LOG_INFO(GetLogger())<<"main begin";
        sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
        fiber->swapIn();
        SYLAR_LOG_INFO(GetLogger())<<"main after swapIn";
        fiber->swapIn();
        SYLAR_LOG_INFO(GetLogger())<<"main after end";
    }
    SYLAR_LOG_INFO(GetLogger())<<"main after end2";
    return 0;
}