//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "home_server.h"
#include "home_data_provider.h"

namespace {
    const quint16 Port = 1234;
}

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    std::unique_ptr<hctrl::HomeDataProvider> homeDataProvider(new hctrl::HomeDataProvider);
    hctrl::HomeServer homeServer(std::move(homeDataProvider), Port);
    return application.exec();
}
