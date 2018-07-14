//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_updater.h"
#include "home_data.h"
#include "itemperature_humidity_sensor.h"
#include "ihome_data_json_builder.h"

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

class MockJsonBuilder : public hctrl::IHomeDataJsonBuilder
{
public:
    MOCK_CONST_METHOD1(build, std::string(const hctrl::HomeData&));
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
    std::unique_ptr<MockJsonBuilder> mockJsonBuilder{ new MockJsonBuilder };
    hctrl::TemperatureHumidityUpdater updater{sensor, homeData, std::move(mockJsonBuilder)};

    //Act
    updater.update();

    //Assert
    ASSERT_EQ(10, homeData.getTemperature());
    ASSERT_EQ(80, homeData.getHumidity());
}
