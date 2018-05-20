#include "repeat_invoker.h"

namespace hctrl
{

RepeatInvoker::RepeatInvoker(
    std::function<void()> handler,
    std::chrono::milliseconds timeout)
: handler_{ std::move(handler) }
, timeout_{ timeout }
, stop_{false}
, invokeThread_{ [this]()
                 {
                     while (!stop_)
                     {
                         handler_();
                         std::this_thread::sleep_for(timeout_);
                     }
                 } }
{}


RepeatInvoker::~RepeatInvoker()
{
    stop_ = true;
    invokeThread_.join();
}

}
