//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_server.h"
#include "mock_home_data_provider.h"

#include <QTcpSocket>
#include <gtest/gtest.h>


TEST(HomeServer, ListensForConnectionsUponCreation)
{
    //Arrange
    std::unique_ptr<hctrl::IHomeDataProvider> homeDataProvider{ new mocks::HomeDataProvider };

    //Act
    hctrl::HomeServer homeServer(std::move(homeDataProvider), 1234);

    //Assert
    QTcpSocket socket;
    socket.connectToHost(QHostAddress::LocalHost, 1234);
    ASSERT_TRUE(socket.waitForConnected());
}
