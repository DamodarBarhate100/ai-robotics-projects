#include<Arduino.h>
#include "INA219Sensor.h"


INA219Sensor::INA219Sensor(){};

bool INA219Sensor::begin_INA(){
    Wire.beginTransmission(INA219_ADDRESS);
    byte status_ina = Wire.endTransmission();
    if(status_ina == 0){
        Serial.println("INA219 Sensor Initialized");
        write_register(REG_CALIBRATION,4096);
        return true;
    }
    else{
        Serial.println("INA219 Sensor Not Found");
        return false;
    }
}

void INA219Sensor::write_register(uint8_t reg_address, uint16_t value) {
    Wire.beginTransmission(INA219_ADDRESS);
    Wire.write(reg_address);
    Wire.write((uint8_t)(value >> 8));   
    Wire.write((uint8_t)(value & 0xFF)); 
    Wire.endTransmission();
}

uint16_t INA219Sensor::read_register(uint8_t reg_address){
        Wire.beginTransmission(INA219_ADDRESS);
        Wire.write(reg_address);
        Wire.endTransmission(false);
        Wire.requestFrom(INA219_ADDRESS,2);
        if(Wire.available() == 2){
            msb = Wire.read();
            lsb = Wire.read();
            return (uint16_t)((msb<<8)|lsb);
        }
        // returning 0 if failed
        return 0x0000;
}


float INA219Sensor::get_bus_voltage(){
    uint16_t raw_bus_v = read_register(REG_BUS_VOLT)>>3;
    bus_voltage = raw_bus_v * 0.004f;
    return bus_voltage;
}

float INA219Sensor::get_current(){
    uint16_t raw_current = read_register(REG_CURRENT);
    current_val = ((int16_t)raw_current) * 0.0001f;
    return current_val;
}
float INA219Sensor::get_power(){
    uint16_t raw_power = read_register(REG_POWER);
    power_val = raw_power  * 0.002f;
    return power_val;
}



void INA219Sensor::print_vals(){
    Serial.print("Current:");
    Serial.print(current_val);
    Serial.print("Bus Voltage:");
    Serial.print(bus_voltage);
    Serial.print("Power:");
    Serial.println(power_val);
}