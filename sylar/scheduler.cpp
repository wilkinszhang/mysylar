#include"scheduler.h"
#include"log.h"
#include"macro.h"

namespace sylar{

sylar::Logger::ptr GetLogger(){
    static sylar::Logger::ptr logger=SYLAR_LOG_NAME("system");
    return logger;
}
Scheduler::Scheduler(size_t threads,bool use_caller,const std::string& name){
// 这部分代码正在初始化一个“Scheduler”对象，该对象用于管理线程和纤程（轻量级线程）。
// 以下是每行的详细说明：
// 1. `sylar::Fiber::GetThis();` 此行获取代码正在运行的当前 Fiber（轻量级线程）。 看起来这条线是因为它的副作用而被调用的，可能会设置一些全局或线程本地状态。
// 2. `--threads;` 这一行将 `threads` 变量减 1。这样做是因为当前线程被用作调度程序的一部分，因此需要创建的附加线程的数量会减少 一。
// 3. `SYLAR_ASSERT(GetThis() == nullptr);` 这一行断言当前线程还没有与其关联的 `Scheduler`。
// 4. `t_scheduler = this;` 这行代码将当前线程的 `Scheduler` 设置为这个 `Scheduler` 对象。
// 5. `m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));` 这行代码创建一个新的 `Fiber` 来运行 `Scheduler::run` 函数 ，并将其设置为“调度程序”的根纤维。
// 6. `sylar::Thread::SetName(m_name);` 这一行将当前线程的名称设置为 `Scheduler` 的名称。
// 7. `t_scheduler_ Fiber = m_rootFiber.get();` 这一行将当前线程的纤程设置为 `Scheduler` 的根纤程。
// 8. `m_rootThread = sylar::GetThreadId();` 这一行将 `Scheduler` 的根线程设置为当前线程的 ID。
// 9. `m_threadIds.push_back(m_rootThread);` 这行代码将根线程的 ID 添加到 `Scheduler` 管理的线程 ID 列表中。
// 因此，总而言之，这部分代码是将 `Scheduler` 配置为使用当前线程，并设置根纤程来运行 `Scheduler::run` 函数。
// `std::bind` 函数是 C++ 中的一个标准库函数，它生成一个新函数对象，将一个或多个参数“绑定”到特定值或占位符。 这可用于将采用多个参数的函数调整为采用较少参数的函数对象。
// 这是一个简单的例子：
// ````cpp
// 无效 print_sum(int a, int b) {
//      std::cout << a + b << std::endl;
// }
// int main() {
//      自动bound_print_sum = std::bind(print_sum, 5, std::占位符::_1);
//      绑定打印总和（10）； // 打印 15
//      返回0；
// }
// ````
// 在此示例中，“std::bind(print_sum, 5, std::placeholders::_1)”创建一个带有一个参数的新函数对象“bound_print_sum”。 当使用参数调用此函数对象时，它会调用“print_sum”，第一个参数固定为“5”，第二个参数固定为传递给“bound_print_sum”的任何参数。
// 在您的代码中，“std::bind(&Scheduler::run, this)”创建一个函数对象，在调用该函数对象时，将调用“this”指向的“Scheduler”对象上的“run”方法。 这用于创建一个“Fiber”，它将在执行时运行“Scheduler::run”方法。
    
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