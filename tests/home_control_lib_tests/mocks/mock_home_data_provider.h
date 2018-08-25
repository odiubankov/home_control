//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once
#include "ihome_data_provider.h"

#include <gmock/gmock.h>

namespace mocks {

class HomeDataProvider : public hctrl::IHomeDataProvider
{
public:
  MOCK_CONST_METHOD0(getHomeDataJson, std::string());
};

}
