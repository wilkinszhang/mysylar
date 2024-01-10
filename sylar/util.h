#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__
#include<sys/types.h>
#include<string>
#include<vector>
#include <cxxabi.h>
#include<string>
namespace sylar{
pid_t GetThreadId();
u_int32_t GetFiberId();


void Backtrace(std::vector<std::string>& bt,int size=64,int skip=1);
std::string BacktraceToString(int size=64,int skip=2,const std::string& prefix="");

template<class T>
const char* TypeToName(){
    static const char* s_name=abi::__cxa_demangle(typeid(T).name(),nullptr,nullptr,nullptr);
    return s_name;
}
}

#endif