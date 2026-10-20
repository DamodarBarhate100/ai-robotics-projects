#include <Arduino.h>
#include <math.h>
#include "JARVIS.h"

JARVIS J1;

void setup() {
    Serial.begin(115200);
    J1.initialize();

    J1.set_servo_offset(2, 5.0);
    J1.move_servo(2, 60.0);

    double applied = J1.get_servo_applied_angle(2);
    double requested = J1.get_servo_requested_angle(2);
    double offset = J1.get_servo_offset(2);

    Serial.print("Requested angle: ");
    Serial.println(requested);

    Serial.print("Applied angle: ");
    Serial.println(applied);

    Serial.print("Offset: ");
    Serial.println(offset);

    Serial.print("Is applied angle invalid? ");
    Serial.println(isnan(applied));
}

void loop() {}