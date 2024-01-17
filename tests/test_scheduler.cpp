#include"../sylar/sylar.h"

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}

int main(int argc,char** argv){
    sylar::Scheduler sc(1,true,"test");
    sc.start();
    sc.stop();
    return 0;
}