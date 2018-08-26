//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once
#include "request_processor.h"

#include <memory>

namespace hctrl {

class IHomeDataProvider;

class HomeDataRequestProcessor : public RequestProcessor
{
public:
    HomeDataRequestProcessor(std::unique_ptr<IHomeDataProvider> homeDataProvider);
    ~HomeDataRequestProcessor() override = default;
    HomeDataRequestProcessor(HomeDataRequestProcessor&&) = default;
    HomeDataRequestProcessor& operator=(HomeDataRequestProcessor&&) = default;
    HomeDataRequestProcessor(const HomeDataRequestProcessor&) = default;
    HomeDataRequestProcessor& operator=(const HomeDataRequestProcessor&) = default;

    std::string process() const override;
    std::unique_ptr<RequestProcessor> clone() const override {
        return std::unique_ptr<RequestProcessor>{ new HomeDataRequestProcessor(*this) };
    }

private:
    std::shared_ptr<IHomeDataProvider> homeDataProvider_;
};

}
