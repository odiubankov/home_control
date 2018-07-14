//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include "itemperature_humidity_sensor.h"

#include <thread>
#include <chrono>
#include <iostream>

namespace hctrl {

template <typename SensorImplT>
class TemperatureHumiditySensor : public ITemperatureHumiditySensor
{
public:
    TemperatureHumiditySensor(SensorImplT sensor)
    : sensorImpl_{std::move(sensor)}
    {}

    void update() override
    {
        const int READ_CNT = 10;
        int temperature = 0;
        unsigned humidity = 0;
        for (int i = 0; i < READ_CNT;)
        {
            try
            {
                sensorImpl_.read();
                temperature += sensorImpl_.getTemperature();
                humidity += sensorImpl_.getHumidity();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                ++i;
            }
            catch(const std::runtime_error& error)
            {
                std::cout << "Exception on reading: " << error.what() << std::endl;
            }
        }

        temperature_ = temperature / READ_CNT;
        humidity_ = humidity / READ_CNT;
    }

    int getTemperature() const override { return temperature_; }
    unsigned getHumidity() const override { return humidity_; }

private:
    SensorImplT sensorImpl_;
    int temperature_{0};
    unsigned humidity_{0};
};

}
