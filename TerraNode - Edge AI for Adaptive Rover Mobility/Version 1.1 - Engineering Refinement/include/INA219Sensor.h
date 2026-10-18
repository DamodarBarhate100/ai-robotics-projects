#ifndef INA219SENSOR_H
#define INA219SENSOR_H
#include<Arduino.h>
#include <Wire.h>
// Default I2C Adress for INA219
#define INA219_ADDRESS 0x40 

// INA219 Register Addresses
#define REG_CONFIG      0x00
#define REG_SHUNT_VOLT  0x01
#define REG_BUS_VOLT    0x02
#define REG_POWER       0x03
#define REG_CURRENT     0x04
#define REG_CALIBRATION 0x05

class INA219Sensor{
    private:
        uint8_t msb;
        uint8_t lsb;
        float bus_voltage;
        float current_val;
        float power_val;
    public:
        // Constructor
        INA219Sensor();
        bool begin_INA();
        void write_register(uint8_t reg_address, uint16_t value);
        uint16_t read_register(uint8_t reg_address);
        float get_bus_voltage();
        float get_current();
        float get_power();
        void print_vals();

};

#endif
