//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_json_builder.h"
#include "home_data.h"

#include <gtest/gtest.h>
#include <QJsonDocument>
#include <QJsonObject>

TEST(HomeDataJsonBuilder, Build)
{
    // Arrange
    hctrl::HomeDataJsonBuilder homeDataJsonBuilder;
    hctrl::HomeData homeData;
    homeData.setHumidity(60);
    homeData.setTemperature(20);

    // Act
    auto json = homeDataJsonBuilder.build(homeData);

    // Assert
    auto doc = QJsonDocument::fromJson(json.c_str());
    ASSERT_EQ(60, doc.object()["humidity"].toInt());
    ASSERT_EQ(20, doc.object()["temperature"].toInt());
}
