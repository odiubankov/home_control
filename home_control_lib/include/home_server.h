//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <QTcpServer>
#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>
#include <future>
#include <vector>

namespace hctrl {

class IHomeDataProvider;
class RequestProcessor;

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

    void registerRequestProcessor(std::unique_ptr<RequestProcessor> requestProcessor);
    std::unique_ptr<RequestProcessor> getRequestProcessor(const std::string& name) const;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void removeProcessedConnections();
    void processConnection(qintptr socketDescriptor);

    std::unique_ptr<IHomeDataProvider> homeDataProvider_;

    mutable std::mutex requestProcessorsMutex_;
    std::unordered_map<std::string, std::unique_ptr<RequestProcessor>> requestProcessors_;
    std::vector<std::future<void>> connections_;
};

bool readStringFromSocket(QTcpSocket& socket, std::string& str);

}
