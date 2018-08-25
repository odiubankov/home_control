//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include "itemperature_humidity_sensor.h"

#include <gmock/gmock.h>

namespace mocks {

class TemperatureHumiditySensor : public hctrl::ITemperatureHumiditySensor
{
public:
    MOCK_METHOD0(update, void());
    MOCK_CONST_METHOD0(getTemperature, int());
    MOCK_CONST_METHOD0(getHumidity, unsigned());
};

}
