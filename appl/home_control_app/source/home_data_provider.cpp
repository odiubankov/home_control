//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_provider.h"
#include "home_data.h"
#include "temperature_humidity_sensor.h"
#include "temperature_humidity_updater.h"
#include "repeat_invoker.h"
#include "memory_mapped_io.h"
#include "gpio_pin.h"
#include "dht_sensor_11.h"
#include "home_data_json_builder.h"

#include <chrono>

namespace {
    // GPIO pin connected to DHT11 sensor
    const unsigned CONNECTED_PIN = 4;
}

namespace hctrl {

HomeDataProvider::HomeDataProvider()
    : homeData_(new HomeData)
{
    raspby::MemoryMappedIO memoryMappedIO;
    auto pin = raspby::GpioPin::create<CONNECTED_PIN>();
    dht::DhtSensor11 sensorImpl{memoryMappedIO, pin};
    sensor_.reset(new TemperatureHumiditySensor<dht::DhtSensor11>(std::move(sensorImpl)));
    std::unique_ptr<HomeDataJsonBuilder> jsonBuilder(new HomeDataJsonBuilder);
    updater_.reset(new TemperatureHumidityUpdater(*sensor_, *homeData_, std::move(jsonBuilder)));
    repeatInvoker_.reset(new RepeatInvoker([this](){ updater_->update(); }, std::chrono::milliseconds{60000}));
}


HomeDataProvider::~HomeDataProvider() = default;


std::string HomeDataProvider::getHomeDataJson() const
{
    return updater_->getHomeDataJson();
}

}
