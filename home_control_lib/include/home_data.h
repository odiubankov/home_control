//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

namespace hctrl
{

class HomeData
{
public:
    unsigned getHumidity() const { return humidity_; }
    void setHumidity(unsigned humidity){ humidity_ = humidity; };

    int getTemperature() const { return temperature_; }
    void setTemperature(int temperature) { temperature_ = temperature; }

private:
    int temperature_{0};
    unsigned humidity_{0};
};

}
