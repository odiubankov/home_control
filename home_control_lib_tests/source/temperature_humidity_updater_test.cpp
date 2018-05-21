//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_updater.h"
#include "home_data.h"
#include "itemperature_humidity_sensor.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


namespace {

class MockTemperatureHumiditySensor : public hctrl::ITemperatureHumiditySensor
{
public:
    MOCK_METHOD0(update, void());
    MOCK_CONST_METHOD0(getTemperature, int());
    MOCK_CONST_METHOD0(getHumidity, unsigned());
};

}

using ::testing::Return;

TEST(TemperatureHumidityUpdater, Update)
{
    //Arrange
    MockTemperatureHumiditySensor sensor;
    EXPECT_CALL(sensor, update())
        .Times(1);
    EXPECT_CALL(sensor, getTemperature())
        .Times(1)
        .WillOnce(Return(10));
    EXPECT_CALL(sensor, getHumidity())
        .Times(1)
        .WillOnce(Return(80));

    hctrl::HomeData homeData;
    hctrl::TemperatureHumidityUpdater updater{sensor, homeData};

    //Act
    updater();

    //Assert
    ASSERT_EQ(10, homeData.getTemperature());
    ASSERT_EQ(80, homeData.getHumidity());
}