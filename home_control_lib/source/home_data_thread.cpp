//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_thread.h"

#include <QtNetwork>

namespace hctrl {

HomeDataThread::HomeDataThread(
        int socketDescriptor,
        std::string text,
        QObject *parent)
    : QThread(parent)
    , socketDescriptor_(socketDescriptor)
    , text_(std::move(text))
{
}


void HomeDataThread::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor_)) {
        emit error(tcpSocket.error());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << QString::fromStdString(text_);

    tcpSocket.write(block);
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}

}
