//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once
#include "request_processor.h"
#include <memory>
#include <gmock/gmock.h>

namespace mocks {

class RequestProcessor : public hctrl::RequestProcessor
{
public:
    RequestProcessor()
        : hctrl::RequestProcessor("mock_request_processor")
    {}
    RequestProcessor(const RequestProcessor& rp)
        : hctrl::RequestProcessor(rp)
    {}
    RequestProcessor(RequestProcessor&) = default;
    RequestProcessor& operator=(const RequestProcessor&) = default;
    RequestProcessor& operator=(RequestProcessor&&) = default;

    MOCK_CONST_METHOD0(process, std::string());

    std::unique_ptr<hctrl::RequestProcessor> clone() const override {
        return std::unique_ptr<hctrl::RequestProcessor>{ new mocks::RequestProcessor(*this) };
    }
};

}
