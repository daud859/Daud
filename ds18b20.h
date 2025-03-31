#ifndef DS18B20_H
#define DS18B20_H

#include "mbed.h"

class DS18B20 {.h
public:
    DS18B20(PinName pin);
    float readTemperature();

private:
    DigitalInOut _oneWire;
    void writeByte(uint8_t byte);
    uint8_t readByte();
    bool reset();
};

#endif  // DS18B20_H
