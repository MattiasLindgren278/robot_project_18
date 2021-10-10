/**
 * Project group
 * Course:
**/

#include <stdio.h>
#include "brick.h"
#include "robot.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    	OUTC
#define MOTOR_D    	OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2	IN2
#define SENSOR_3	IN3
#define SENSOR_4	IN4

#define MOTOR_BOTH     	( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T usSensor;
int max_driving_speed;  // Max speed for driving motors

int main(void){
    if(!init(&max_driving_speed, 0)){
        return 1;
}
    find_wall();
    //while (tacho_is_running(MOTOR_BOTH));
    to_wall(300, 0.5);
    while (tacho_is_running(MOTOR_BOTH));
    from_wall(300, 0.5);
    //while (tacho_is_running(MOTOR_BOTH));
    rotate('l', 90, 0.5); 
    //while (tacho_is_running(MOTOR_BOTH));
    drive(2500, 0.5);
    //while (tacho_is_running(MOTOR_BOTH));
    rotate('l', 180, 0.5);
    //while (tacho_is_running(MOTOR_BOTH));
    drop();

    return 0;
}