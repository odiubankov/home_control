//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <QTcpServer>
#include <memory>

namespace hctrl {

class IHomeDataProvider;

class HomeServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HomeServer(
            std::unique_ptr<IHomeDataProvider> homeDataProvider,
            quint16 port,
            QObject *parent = Q_NULLPTR);
    ~HomeServer();
    HomeServer(const HomeServer&) = delete;
    HomeServer(HomeServer&&) = delete;
    HomeServer& operator=(const HomeServer&) = delete;
    HomeServer& operator=(HomeServer&&) = delete;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    std::unique_ptr<IHomeDataProvider> homeDataProvider_;
};

}
