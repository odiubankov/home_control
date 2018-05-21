//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

namespace hctrl {

class ITemperatureHumiditySensor
{
public:
    virtual ~ITemperatureHumiditySensor() = default;

    virtual void update() = 0;
    virtual int getTemperature() const = 0;
    virtual unsigned getHumidity() const = 0;
};

}