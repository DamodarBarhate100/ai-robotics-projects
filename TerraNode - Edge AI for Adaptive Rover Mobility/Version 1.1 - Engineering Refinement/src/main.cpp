#include <Arduino.h>
#include "MotorController.h"

MotorController mc;

void setup(){
    mc.initialize_motors();
    delay(3000); 
}

void loop() {
    mc.move_forward();
    delay(2000);

    mc.stop_motors();
    delay(300);

    mc.move_backward();
    delay(2000);
    
    mc.stop_motors();
    delay(2000);
}