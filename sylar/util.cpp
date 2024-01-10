#include"util.h"
#include"log.h"
#include"fiber.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <cstdint>
#include<execinfo.h>
#include<iostream>
namespace sylar
{

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}

u_int32_t GetFiberId(){
    return sylar::Fiber::GetFiberId();
}

static sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");
    return g_logger;
}

void Backtrace(std::vector<std::string>& bt, int size, int skip) {
    void** array = (void**)malloc((sizeof(void*) * size));
    size_t s = ::backtrace(array, size);

    char** strings = backtrace_symbols(array, s);
    if(strings == NULL) {
        SYLAR_LOG_ERROR(GetLogger()) << "backtrace_synbols error";
        return;
    }

    for(size_t i = skip; i < s; ++i) {
        bt.push_back(strings[i]);
    }

    std::cout << "Current file: " << __FILE__ << std::endl;

    free(strings);
    free(array);
}

std::string BacktraceToString(int size, int skip, const std::string& prefix) {
    std::vector<std::string> bt;
    Backtrace(bt, size, skip);
    std::stringstream ss;
    for(size_t i = 0; i < bt.size(); ++i) {
        ss << prefix << bt[i] << std::endl;
    }
    return ss.str();
}

}
