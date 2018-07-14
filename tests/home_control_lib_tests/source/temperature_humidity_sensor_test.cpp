//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_sensor.h"
#include <gtest/gtest.h>


namespace {

class SensorImpl
{
public:
    int getTemperature() const { return temperature_; }
    unsigned getHumidity() const { return humidity_; }

    void read()
    {
        ++humidity_;
        ++temperature_;
    }

private:
    int temperature_{-2};
    unsigned humidity_{0};
};

}


TEST(TemperatureHumiditySensor, UpdateCallsRead10TimesAndCalculatesTheAverage)
{
    // Arrange
    hctrl::TemperatureHumiditySensor<SensorImpl> sensor{SensorImpl{}};

    //Act
    sensor.update();

    //Assert
    ASSERT_EQ(3, sensor.getTemperature());
    ASSERT_EQ(5, sensor.getHumidity());
}