//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <string>

namespace hctrl {

class HomeData;

class IHomeDataJsonBuilder
{
public:
    virtual ~IHomeDataJsonBuilder() {}
    virtual std::string build(const HomeData& homeData) const = 0;
};

}
