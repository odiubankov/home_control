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
