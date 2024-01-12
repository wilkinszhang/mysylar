#include"scheduler.h"
#include"log.h"
#include"macro.h"

namespace sylar{

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}
Scheduler::Scheduler(size_t threads,bool use_caller,const std::string& name){

}
Scheduler::~Scheduler(){

}

Scheduler* Scheduler::GetThis(){

}

Fiber* Scheduler::GetMainFiber(){
    
}

void Scheduler::start(){

}
void Scheduler::stop(){

}

void Scheduler::tickle(){
    
}

}