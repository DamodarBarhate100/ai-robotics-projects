#include "DataLogger.h"

DataLogger::DataLogger(){};

bool DataLogger::initialize_data_log(){
    if(!SD.begin(CS)){
        Serial.println("Failed to initialize SD Card Module");
        return false;
    }
    file = SD.open("/terrain_data.csv", FILE_APPEND);
    Serial.println("SD Card Module Initialized");
    if(!file){
        Serial.println("Unable to open the file");
        return false;
    }    
    if(file.size() == 0){
        file.println("bus_voltage,current_val,power");
        file.flush();
    }
    file.close();
    return true;
}



bool DataLogger::log_data(float bus_voltage, float current, float power){

    file = SD.open("/terrain_data.csv", FILE_APPEND);
    if(!file){
        Serial.println("Unable to open file and log data");
        return false;
    }
    file.printf("%.3f,%.4f,%.3f\n",bus_voltage, current, power);
    file.close();
    return true;

}



