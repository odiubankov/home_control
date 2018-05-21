//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

namespace hctrl {

class ITemperatureHumiditySensor;
class HomeData;

class TemperatureHumidityUpdater
{
public:
    TemperatureHumidityUpdater(ITemperatureHumiditySensor& sensor, HomeData& homeData);
    void operator()();

private:
    ITemperatureHumiditySensor& sensor_;
    HomeData& homeData_;
};

}