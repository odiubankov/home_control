//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <string>
#include <functional>
#include <memory>

namespace hctrl {

class RequestProcessor
{
public:
    RequestProcessor(std::string name)
        : name_{ std::move(name) }
    {}
    virtual ~RequestProcessor() {}
    RequestProcessor(const RequestProcessor&) = default;
    RequestProcessor(RequestProcessor&&) = default;
    RequestProcessor& operator=(const RequestProcessor&) = default;
    RequestProcessor& operator=(RequestProcessor&&) = default;

    const std::string& getName() const { return name_; }
//    virtual std::string process() const = 0;
//    virtual std::unique_ptr<RequestProcessor> clone() const = 0;
    virtual std::string process() const { return ""; }
    virtual std::unique_ptr<RequestProcessor> clone() const { return std::unique_ptr<RequestProcessor>{}; }

private:
    std::string name_;
};

}
