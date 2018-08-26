//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_request_processor.h"
#include "mock_home_data_provider.h"
#include <gtest/gtest.h>

using ::testing::Return;

TEST(HomeDataRequestProcessor, GetName)
{
    //Arrange
    std::unique_ptr<hctrl::IHomeDataProvider> homeDataProvider{ new mocks::HomeDataProvider };
    hctrl::HomeDataRequestProcessor homeDataRequestProcessor{ std::move(homeDataProvider) };

    //Act
    auto name = homeDataRequestProcessor.getName();

    //Assert
    ASSERT_EQ("HomeData", name);
}

TEST(HomeDataRequestProcessor, Process)
{
    //Arrange
    std::unique_ptr<mocks::HomeDataProvider> homeDataProvider{ new mocks::HomeDataProvider };
    auto mockHomeDataProvider = homeDataProvider.get();
    hctrl::HomeDataRequestProcessor homeDataRequestProcessor{ std::move(homeDataProvider) };
    EXPECT_CALL(*mockHomeDataProvider, getHomeDataJson())
        .Times(1)
        .WillOnce(Return("test result"));
    //Act
    auto result = homeDataRequestProcessor.process();

    //Assert
    ASSERT_EQ(result, "test result");
}
