#include<Arduino.h>
#include "Servo_Calibration.h"
#include<Preferences.h>


Preferences pref;

Servo_Calibration::Servo_Calibration(Adafruit_PWMServoDriver &driver, uint8_t channel, int servo_id, const char* servo_name, double neutral_angle, float offset)
    :pwm(driver){
    config.servo_name = servo_name;
    config.pca_channel = channel;
    config.servo_offset = offset;
    config.neutral_angle = neutral_angle;
    config.servo_id = servo_id;
}

void Servo_Calibration::initialize(){
    load_offset();
    move_to_neutral();
}

void Servo_Calibration::safety_check(double degrees){
    config.requested_angle = degrees;


    config.current_angle = degrees + config.servo_offset;
    if(config.current_angle>max_angle){
        config.current_angle = max_angle;
    }
    else if(config.current_angle<min_angle){
        config.current_angle = min_angle;
    }
}

void Servo_Calibration::move_servo(double degrees){
    safety_check(degrees);
    double physical_angle = config.current_angle + 90;
    int pulse = map( physical_angle,0, 180, 102,512);
    pwm.setPWM(config.pca_channel, 0, pulse);
}

void Servo_Calibration::save_offset(float offset_val){
    config.servo_offset = offset_val;

    if(!pref.begin("Servo-cal",false)){
        Serial.println("Could not open servo preferences");
        return;
    }
    size_t written = pref.putFloat(config.servo_name, offset_val);
    pref.end();

    if (written == 0){
        Serial.println("Failed to persist servo offset");
    }
}

float Servo_Calibration::load_offset(){
    pref.begin("Servo-cal",true);
    config.servo_offset = pref.getFloat(config.servo_name, 0.0f);
    pref.end();
    return config.servo_offset;
}

void Servo_Calibration::move_to_center(){
    move_servo(0);
}
void Servo_Calibration::move_to_neutral(){
    move_servo(config.neutral_angle);
}

void Servo_Calibration::print_configuration(){
    Serial.print("Servo_id:");
    Serial.println(config.servo_id);
    Serial.print("Servo Name:");
    Serial.println(config.servo_name);
    Serial.print("PCA9685 Channel:");
    Serial.println(config.pca_channel);
    Serial.print("Calibration Offset:");
    Serial.println(config.servo_offset);
    Serial.print("Current Angle:");
    Serial.println(config.current_angle);
    Serial.print("Requested Angle:");
    Serial.println(config.requested_angle);
    Serial.print("Max limit:");
    Serial.println(max_angle);
    Serial.print("Min limit:");
    Serial.println(min_angle);
    Serial.print("Neutral Angle:");
    Serial.println(config.neutral_angle);
}

void Servo_Calibration::print_logical_angle(){
    Serial.print("Logical Angle of :");
    float logical_angle = config.current_angle - config.servo_offset;
    Serial.println(logical_angle);
}


void Servo_Calibration::set_soft_limits(
    double min_deg,
    double max_deg
) {
    if (min_deg < -90.0 ||
        max_deg > 90.0 ||
        min_deg > 90.0 ||
        max_deg < -90.0 ||
        min_deg >= max_deg) {

        Serial.println("Invalid servo soft limits");
        return;
    }

    min_angle = min_deg;
    max_angle = max_deg;
}

double Servo_Calibration:: get_applied_angle() const{
    return config.current_angle;
}

double Servo_Calibration::get_offset() const{
    return config.servo_offset;
}

double Servo_Calibration::get_requested_angle() const{
    return config.requested_angle;
}

