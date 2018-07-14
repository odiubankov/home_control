//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_server.h"
#include "ihome_data_provider.h"
#include "home_data_thread.h"
#include <iostream>

QT_USE_NAMESPACE

namespace hctrl {

HomeServer::HomeServer(
        std::unique_ptr<IHomeDataProvider> homeDataProvider,
        quint16 port,
        QObject* parent)
    : QTcpServer(parent)
    , homeDataProvider_(std::move(homeDataProvider))
{
    std::cout << "HomeServer construct" << std::endl;
    if (!listen(/*QHostAddress::LocalHost, port*/)) {
        std::cout << "Can't listen "  << std::endl;
        //TODO error handling
        close();
    }

    std::cout << "port: " << serverPort() << std::endl;
}


HomeServer::~HomeServer() = default;


void HomeServer::incomingConnection(qintptr socketDescriptor)
{
    std::cout << "Incoming connection" << std::endl;
    auto thread = new HomeDataThread(socketDescriptor, homeDataProvider_->getHomeDataJson(), this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

}
