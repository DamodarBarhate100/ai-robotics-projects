#include <Arduino.h>
#include "MotorController.h"
#include "INA219Sensor.h"
#include <Wire.h>
#include "DataLogger.h"

MotorController mc;
INA219Sensor ina_;
DataLogger logger;

bool status_ina;
bool status_logger;
void setup(){
    Wire.begin();
    Serial.begin(115200);
    mc.initialize_motors();
    status_logger = logger.initialize_data_log();
    status_ina = ina_.begin_INA();
    if(!status_logger){
        Serial.println("Failed to initialize data logger");
    }
    if(!status_ina){
        Serial.println("Failed to initialize INA219 Current Sensor");
    }
    delay(3000); 
}

void loop() {
    mc.move_forward();

    for (int i = 0; i < 500; i += 15) {
        if (status_ina) {
            float voltage = ina_.get_bus_voltage();
            float current = ina_.get_current();
            float power = ina_.get_power();

            ina_.print_vals();

            if (status_logger) {
                logger.log_data(voltage, current, power);
            }
        }
        delay(15);
    }

    mc.stop_motors();

    for (int i = 0; i < 500; i += 15) {
        if (status_ina) {
            float voltage = ina_.get_bus_voltage();
            float current = ina_.get_current();
            float power = ina_.get_power();

            ina_.print_vals();

            if (status_logger) {
                logger.log_data(voltage, current, power);
            }
        }
        delay(15);
    }

    delay(300);
}