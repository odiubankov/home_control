#include "home_data.h"
#include <gtest/gtest.h>


TEST(HomeData, Construct)
{
    //Arrange

    //Act
    hctrl::HomeData homeData;

    //Assert
    ASSERT_EQ(homeData.getTemperature(), 0);
    ASSERT_EQ(homeData.getHumidity(), 0);
}


TEST(HomeData, SetTemperature)
{
    //Arrange
    hctrl::HomeData homeData;

    //Act
    homeData.setTemperature(10);

    //Assert
    ASSERT_EQ(homeData.getTemperature(), 10);
}


TEST(HomeData, SetHumidity)
{
    //Arrange
    hctrl::HomeData homeData;

    //Act
    homeData.setHumidity(10);

    //Assert
    ASSERT_EQ(homeData.getHumidity(), 10);
}