//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_json_builder.h"
#include "home_data.h"

#include <QJsonDocument>
#include <QJsonObject>

namespace hctrl {

std::string HomeDataJsonBuilder::build(const HomeData &homeData) const
{
    QJsonObject json;
    json["humidity"] = static_cast<int>(homeData.getHumidity());
    json["temperature"] = homeData.getTemperature();
    return QJsonDocument{json}.toJson().constData();
}

}
