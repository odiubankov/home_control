//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_server.h"
#include "ihome_data_provider.h"
#include "home_data_thread.h"
#include "request_processor.h"

#include <iostream>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

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
    if (!listen(QHostAddress::Any, port)) {
        std::cout << "Can't listen "  << std::endl;
        close();
    }
}


HomeServer::~HomeServer() = default;


void HomeServer::registerRequestProcessor(std::unique_ptr<RequestProcessor> requestProcessor)
{
    std::lock_guard<std::mutex> lg{ requestProcessorsMutex_ };
    auto requestProcessorIt = requestProcessors_.find(requestProcessor->getName());
    if (requestProcessorIt == std::end(requestProcessors_))
        requestProcessors_.emplace(requestProcessor->getName(), std::move(requestProcessor));
    else
        requestProcessorIt->second = std::move(requestProcessor);
}


std::unique_ptr<RequestProcessor> HomeServer::getRequestProcessor(const std::string& name) const
{
    std::unique_ptr<RequestProcessor> result;

    std::lock_guard<std::mutex> lg{ requestProcessorsMutex_ };
    auto requestProcessorIt = requestProcessors_.find(name);
    if (requestProcessorIt != std::end(requestProcessors_))
        result = requestProcessorIt->second->clone();

    return result;
}


void HomeServer::incomingConnection(qintptr socketDescriptor)
{
    removeProcessedConnections();
    connections_.emplace_back(std::async(std::launch::async, [this, socketDescriptor]() { processConnection(socketDescriptor); } ));
//    std::cout << "Incoming connection" << std::endl;
//    auto thread = new HomeDataThread(socketDescriptor, homeDataProvider_->getHomeDataJson(), this);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    thread->start();
}

std::string getProcessorName(std::string request)
{
    auto doc = QJsonDocument::fromJson(request.c_str());
    return std::string{ doc.object()["request"].toString().toUtf8().constData() };
}


void HomeServer::processConnection(qintptr socketDescriptor)
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        std::cout << "error " << __func__ << std::endl;
        return;
    }

    std::string request;
    if (!readStringFromSocket(tcpSocket, request))
    {
        std::cout << "error reading from socket" << std::endl;
        return;
    }

    auto processorName = getProcessorName(request);
    auto processor = getRequestProcessor(processorName);
    tcpSocket.write(processor->process().c_str());
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}


void HomeServer::removeProcessedConnections()
{
    connections_.erase( std::remove_if(begin(connections_), end(connections_),
        [](const std::future<void>& connection){
            return connection.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
        }), end(connections_));
}


bool readStringFromSocket(QTcpSocket& socket, std::string& str)
{
    QDataStream dataStream(&socket);
    dataStream.setVersion(QDataStream::Qt_4_0);

    QString socketData;
    do {
        if (!socket.waitForReadyRead())
            return false;

        dataStream.startTransaction();
        dataStream >> socketData;
    } while (!dataStream.commitTransaction());

    str = std::string{ socketData.toUtf8().constData() };
    return true;
}

}
