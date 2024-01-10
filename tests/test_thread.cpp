#include"../sylar/sylar.h"
#include<unistd.h>

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();
    return g_logger;
}

int count=0;
// sylar::RWMutex s_mutex;
sylar::Mutex s_mutex;

void fun1(){
    SYLAR_LOG_INFO(GetLogger())<<"name: "<<sylar::Thread::GetName()
                               <<" this.name: "<<sylar::Thread::GetThis()->getName()
                               <<" id: "<<sylar::GetThreadId()
                               <<" this.id: "<<sylar::Thread::GetThis()->getId();
    // sleep(20);
    for(size_t i=0;i<100000;++i){
        // sylar::RWMutex::WriteLock lock(s_mutex);
        sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2(){
    while(true){
        SYLAR_LOG_INFO(GetLogger())<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3(){
    while(true){
        SYLAR_LOG_INFO(GetLogger())<<"==================================================";
    }
}

int main(int argc,char**argv){
    SYLAR_LOG_INFO(GetLogger())<<"thread test begin";
    YAML::Node root=YAML::LoadFile("/home/whut4/zwj/mysylar/bin/conf/log2.yml");
    sylar::Config::LoadFromYaml(root);

    std::vector<sylar::Thread::ptr> thrs;
    for(size_t i=0;i<2;i++){
        sylar::Thread::ptr thr(new sylar::Thread(&fun2,"name_"+std::to_string(i*2)));
        sylar::Thread::ptr thr2(new sylar::Thread(&fun3,"name_"+std::to_string(i*2+1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }
    for(size_t i=0;i<thrs.size();i++){
        thrs[i]->join();
    }
    SYLAR_LOG_INFO(GetLogger())<<"count="<<count<<std::endl;
    SYLAR_LOG_INFO(GetLogger())<<"thread test end";
    return 0;
}