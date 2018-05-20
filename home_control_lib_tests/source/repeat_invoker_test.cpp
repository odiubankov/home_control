#include "repeat_invoker.h"
#include <gtest/gtest.h>
#include <thread>
#include <atomic>


TEST(RepeatInvoker, Invoke)
{
    //Arrange
    std::atomic<int> invokeTimesCnt;
    hctrl::RepeatInvoker repeatInvoker{
        [&invokeTimesCnt] { ++invokeTimesCnt; },
        std::chrono::milliseconds{1} };

    //Act
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    //Assert
    ASSERT_GT(invokeTimesCnt, 500);
}