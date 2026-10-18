#ifndef DATALOGGER_H
#define DATALOGGER_H

#include<Arduino.h>
#include<SD.h>
#include<SPI.h>

# define CS 5
# define SCK 18
# define MISO 19
# define MOSI 23

class DataLogger{
    private:
        File file;
    public:
        DataLogger();
        bool initialize_data_log();
        bool log_data(float bus_voltage, float current, float power);

};


#endif