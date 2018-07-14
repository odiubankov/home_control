//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include "ihome_data_provider.h"

#include <memory>

namespace hctrl {

class ITemperatureHumiditySensor;
class HomeData;
class TemperatureHumidityUpdater;
class RepeatInvoker;

class HomeDataProvider : public IHomeDataProvider
{
public:
    HomeDataProvider();
    ~HomeDataProvider();
    HomeDataProvider(const HomeDataProvider&) = delete;
    HomeDataProvider(HomeDataProvider&&) = delete;
    HomeDataProvider& operator=(const HomeDataProvider&) = delete;
    HomeDataProvider& operator=(HomeDataProvider&&) = delete;

    std::string getHomeDataJson() const override;

private:
    std::unique_ptr<HomeData> homeData_;
    std::unique_ptr<ITemperatureHumiditySensor> sensor_;
    std::unique_ptr<TemperatureHumidityUpdater> updater_;
    std::unique_ptr<RepeatInvoker> repeatInvoker_;
};

}
