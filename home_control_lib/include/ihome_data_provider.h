//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

#include <string>

namespace hctrl {

class IHomeDataProvider
{
public:
    virtual ~IHomeDataProvider() {}
    virtual std::string getHomeDataJson() const = 0;
};

}
