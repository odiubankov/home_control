//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_updater.h"
#include "home_data.h"
#include "mock_temperature_humidity_sensor.h"
#include "mock_json_builder.h"

#include <gtest/gtest.h>

using ::testing::Return;

TEST(TemperatureHumidityUpdater, Update)
{
    //Arrange
    mocks::TemperatureHumiditySensor sensor;
    EXPECT_CALL(sensor, update())
        .Times(1);
    EXPECT_CALL(sensor, getTemperature())
        .Times(1)
        .WillOnce(Return(10));
    EXPECT_CALL(sensor, getHumidity())
        .Times(1)
        .WillOnce(Return(80));

    hctrl::HomeData homeData;
    std::unique_ptr<mocks::JsonBuilder> mockJsonBuilder{ new mocks::JsonBuilder };
    hctrl::TemperatureHumidityUpdater updater{sensor, homeData, std::move(mockJsonBuilder)};

    //Act
    updater.update();

    //Assert
    ASSERT_EQ(10, homeData.getTemperature());
    ASSERT_EQ(80, homeData.getHumidity());
}
