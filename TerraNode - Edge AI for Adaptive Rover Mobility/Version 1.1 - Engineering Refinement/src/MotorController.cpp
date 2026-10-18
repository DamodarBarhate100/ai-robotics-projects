#include "MotorController.h"

MotorController::MotorController(){}
MotorController::~MotorController(){}

void MotorController::initialize_motors(){
    pinMode(EN_A, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    stop_motors();
}

void MotorController::stop_motors(){
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    analogWrite(EN_A, 0);
    analogWrite(EN_B, 0);
}

void MotorController::move_forward(){
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    
    for(int i = 100; i <= 255; i += 5) {
        analogWrite(EN_A, i);
        analogWrite(EN_B, i);
        delay(5);
    }
}

void MotorController::move_backward(){
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    for(int i = 100; i <= 255; i += 5) {
        analogWrite(EN_A, i);
        analogWrite(EN_B, i);
        delay(5);
    }
}
