//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_server.h"
#include "mock_home_data_provider.h"
#include "mock_request_processor.h"

#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <gtest/gtest.h>
#include <sstream>


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

TEST(HomeServer, RegisterRequestProcessor)
{
    //Arrange
    std::unique_ptr<mocks::RequestProcessor> requestProcessor{ new mocks::RequestProcessor };
    auto mockRequestProcessor = requestProcessor.get();
    std::future<void> serverThread = std::async(std::launch::async, [&requestProcessor]()
    {
        int argCnt = 0;
        QCoreApplication application{ argCnt, nullptr };
        std::unique_ptr<hctrl::IHomeDataProvider> homeDataProvider{ new mocks::HomeDataProvider };
        hctrl::HomeServer homeServer(std::move(homeDataProvider), 1234);
        homeServer.registerRequestProcessor(std::move(requestProcessor));
        application.exec();
    });
    //Act
    //Assert
    QTcpSocket socket;
    socket.connectToHost(QHostAddress::LocalHost, 1234);
    socket.waitForConnected();

    std::ostringstream request;
    request << R"({ "request": ")" << mockRequestProcessor->getName() << R"(" })";
    socket.write(request.str().c_str());
    ASSERT_TRUE(socket.waitForBytesWritten());
    std::string response;
    ASSERT_TRUE(hctrl::readStringFromSocket(socket, response));

    auto doc = QJsonDocument::fromJson(response.c_str());
    std::string responseVal = doc.object()["response"].toString().toUtf8().constData();
    ASSERT_EQ(responseVal, mockRequestProcessor->process());
}
