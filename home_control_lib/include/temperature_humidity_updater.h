//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <string>
#include <memory>
#include <mutex>

namespace hctrl {

class ITemperatureHumiditySensor;
class HomeData;
class IHomeDataJsonBuilder;

class TemperatureHumidityUpdater
{
public:
    TemperatureHumidityUpdater(
            ITemperatureHumiditySensor& sensor,
            HomeData& homeData,
            std::unique_ptr<IHomeDataJsonBuilder> homeDataJsonBuilder);
    ~TemperatureHumidityUpdater();
    TemperatureHumidityUpdater(const TemperatureHumidityUpdater&) = delete;
    TemperatureHumidityUpdater(TemperatureHumidityUpdater&&) = delete;
    TemperatureHumidityUpdater& operator=(const TemperatureHumidityUpdater&) = delete;
    TemperatureHumidityUpdater& operator=(TemperatureHumidityUpdater&&) = delete;

    void update();
    std::string getHomeDataJson() const;

private:
    ITemperatureHumiditySensor& sensor_;
    HomeData& homeData_;
    std::unique_ptr<IHomeDataJsonBuilder> homeDataJsonBuilder_;
    mutable std::mutex homeDataMutex_;
    std::string homeDataJson_;
};

}
