#include"../sylar/sylar.h"

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}

int main(int argc,char** argv){
    SYLAR_LOG_INFO(GetLogger())<<"main begin";
    sylar::Scheduler sc(1,true,"test");
    sc.start();
    sc.stop();
    SYLAR_LOG_INFO(GetLogger())<<"main over";
    return 0;
}
// 这个代码的执行顺序
//         CallerMainFunc->run->MainFunc
// Fiberid        1         1     2