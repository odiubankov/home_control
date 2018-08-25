//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_sensor.h"
#include "mock_sensor_impl.h"

#include <gtest/gtest.h>

TEST(TemperatureHumiditySensor, UpdateCallsRead10TimesAndCalculatesTheAverage)
{
    // Arrange
    hctrl::TemperatureHumiditySensor<mocks::SensorImpl> sensor{mocks::SensorImpl{}};

    //Act
    sensor.update();

    //Assert
    ASSERT_EQ(3, sensor.getTemperature());
    ASSERT_EQ(5, sensor.getHumidity());
}
