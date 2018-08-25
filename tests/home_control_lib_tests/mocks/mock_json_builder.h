//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once
#include "ihome_data_json_builder.h"

#include <gmock/gmock.h>

namespace mocks {

class JsonBuilder : public hctrl::IHomeDataJsonBuilder
{
public:
    MOCK_CONST_METHOD1(build, std::string(const hctrl::HomeData&));
};

}
