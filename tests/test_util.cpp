#include"./sylar/sylar.h"
#include<assert.h>
#include<string>
static sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();
    return g_logger;
}

void test_assert(){
    SYLAR_LOG_INFO(GetLogger())<<sylar::BacktraceToString(10,0,"    ");
    // SYLAR_ASSERT2(0==1,"test assert");
}


int main(int argc, char** argv){
    test_assert();
    // assert(0);
    return 0;
}