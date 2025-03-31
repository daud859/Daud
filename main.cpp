#include "mbed.h"
#include "ds18b20.h"

DS18B20 tempSensor(PA_1); // Connect DS18B20 to PA_1

int main() {
    while (1) {
        float temp = tempSensor.readTemperature();
        printf("Temperature: %.2f°C\n", temp);
        ThisThread::sleep_for(1s);
    }
}
