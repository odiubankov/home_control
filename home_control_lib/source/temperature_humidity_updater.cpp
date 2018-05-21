//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_updater.h"
#include "itemperature_humidity_sensor.h"
#include "home_data.h"

namespace hctrl {

TemperatureHumidityUpdater::TemperatureHumidityUpdater(hctrl::ITemperatureHumiditySensor& sensor,
                                                       hctrl::HomeData& homeData)
: sensor_{ sensor }
, homeData_{ homeData }
{}


void TemperatureHumidityUpdater::operator()()
{
    sensor_.update();
    homeData_.setHumidity(sensor_.getHumidity());
    homeData_.setTemperature(sensor_.getTemperature());
}

}