#include "ds18b20.h"

DS18B20::DS18B20(PinName pin) : _oneWire(pin) {
    _oneWire.output();
    _oneWire.write(1);
}

bool DS18B20::reset() {
    _oneWire.output();
    _oneWire.write(0);
    wait_us(480);
    _oneWire.input();
    wait_us(70);
    bool presence = !_oneWire.read();
    wait_us(410);
    return presence;
}

void DS18B20::writeByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        _oneWire.output();
        _oneWire.write(byte & (1 << i));
        wait_us(60);
        _oneWire.input();
        wait_us(10);
    }
}

uint8_t DS18B20::readByte() {
    uint8_t value = 0;
    for (int i = 0; i < 8; i++) {
        _oneWire.output();
        _oneWire.write(0);
        wait_us(2);
        _oneWire.input();
        if (_oneWire.read()) {
            value |= (1 << i);
        }
        wait_us(60);
    }
    return value;
}

float DS18B20::readTemperature() {
    if (!reset()) {
        return -1000.0; // Sensor not found
    }
    writeByte(0xCC); // Skip ROM
    writeByte(0x44); // Start temperature conversion
    wait_us(750000);

    if (!reset()) {
        return -1000.0;
    }
    writeByte(0xCC);
    writeByte(0xBE);

    uint8_t temp_lsb = readByte();
    uint8_t temp_msb = readByte();
    int16_t temp = (temp_msb << 8) | temp_lsb;
    return temp / 16.0; // Convert to Celsius
}
