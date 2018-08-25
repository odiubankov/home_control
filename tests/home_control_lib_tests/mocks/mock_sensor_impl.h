//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#pragma once

namespace mocks {

class SensorImpl
{
public:
    int getTemperature() const { return temperature_; }
    unsigned getHumidity() const { return humidity_; }

    void read()
    {
        ++humidity_;
        ++temperature_;
    }

private:
    int temperature_{-2};
    unsigned humidity_{0};
};

}
