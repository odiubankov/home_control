//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "temperature_humidity_updater.h"
#include "itemperature_humidity_sensor.h"
#include "home_data.h"
#include "ihome_data_json_builder.h"

namespace hctrl {

TemperatureHumidityUpdater::TemperatureHumidityUpdater(hctrl::ITemperatureHumiditySensor& sensor,
                                                       hctrl::HomeData& homeData,
                                                       std::unique_ptr<IHomeDataJsonBuilder> homeDataJsonBuilder)
: sensor_(sensor)
, homeData_(homeData)
, homeDataJsonBuilder_(std::move(homeDataJsonBuilder))
{}


TemperatureHumidityUpdater::~TemperatureHumidityUpdater() = default;


void TemperatureHumidityUpdater::update()
{
    sensor_.update();
    homeData_.setHumidity(sensor_.getHumidity());
    homeData_.setTemperature(sensor_.getTemperature());
    std::lock_guard<std::mutex> lg(homeDataMutex_);
    homeDataJson_ = homeDataJsonBuilder_->build(homeData_);
}


std::string TemperatureHumidityUpdater::getHomeDataJson() const
{
    std::lock_guard<std::mutex> lg(homeDataMutex_);
    return homeDataJson_;
}

}
