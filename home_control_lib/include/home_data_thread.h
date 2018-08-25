//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <QThread>
#include <QTcpSocket>
#include <string>

namespace hctrl {

class HomeDataThread : public QThread
{
    Q_OBJECT

public:
    HomeDataThread(
            int socketDescriptor,
            std::string text,
            QObject* parent);


    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor_;
    std::string text_;
};

}
