//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <chrono>
#include <functional>
#include <thread>

namespace hctrl {

class RepeatInvoker
{
public:
    RepeatInvoker(std::function<void()> handler, std::chrono::milliseconds timeout);
    ~RepeatInvoker();
    RepeatInvoker(const RepeatInvoker&) = delete;
    RepeatInvoker& operator=(const RepeatInvoker&) = delete;
    RepeatInvoker(RepeatInvoker&&) = delete;
    RepeatInvoker& operator=(RepeatInvoker&&) = delete;

private:
    std::function<void()> handler_;
    std::chrono::milliseconds timeout_;
    std::atomic<bool> stop_;
    std::thread invokeThread_;
};

}
