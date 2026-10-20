#ifndef SERVO_CALIBRATION_H
#define SERVO_CALIBRATION_H
#include<Arduino.h>
#include <Adafruit_PWMServoDriver.h>

struct servo_config{
    int servo_id;
    const char *servo_name;
    uint8_t  pca_channel;
    double servo_offset;
    double neutral_angle;
    double current_angle = 0.0;
    double requested_angle = 0.0;


};

class Servo_Calibration{
    private:
        servo_config config;
        double max_angle = 90.0;
        double min_angle = -90.0;
        Adafruit_PWMServoDriver& pwm;
    public:
        Servo_Calibration( Adafruit_PWMServoDriver& driver, uint8_t channel, int servo_id, const char* servo_name, double neutral_angle, float offset=0);
        // Initialization
        void initialize();
        void move_to_neutral();
        
        // Movement
        void safety_check(double degree);
        void move_servo(double degree);

        // Persistance
        void save_offset(float offset_val);
        float load_offset();

        // Utility
        void move_to_center();
        void print_configuration();
        void print_logical_angle();

        void set_soft_limits(double min_deg, double max_deg);
        
        // getter
        double get_applied_angle() const;
        double get_offset() const;
        double get_requested_angle() const;
};

#endif