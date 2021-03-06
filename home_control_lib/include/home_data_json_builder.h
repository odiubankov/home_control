//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include "ihome_data_json_builder.h"

namespace hctrl {

class HomeData;

class HomeDataJsonBuilder : public IHomeDataJsonBuilder
{
public:
    std::string build(const HomeData& homeData) const override;
};

}
