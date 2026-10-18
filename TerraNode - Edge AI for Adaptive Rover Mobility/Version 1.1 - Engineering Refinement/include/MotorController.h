#ifndef MOTORCONTROLLER_H
# define MOTORCONTROLLER_H
#include<Arduino.h>


class MotorController{
    private:
        int EN_A = 25;   
        int IN_1 = 26;
        int IN_2 = 27;
        int IN_3 = 14;
        int IN_4 = 12;
        int EN_B = 13;
    public:
        MotorController();
        void move_forward();
        void stop_motors();
        void initialize_motors();
        void move_backward();
        ~MotorController();

        
};


#endif