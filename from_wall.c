#include <stdio.h>
#include "brick.h"
#include "from_wall.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    	OUTC
#define MOTOR_D    	OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2	IN2
#define SENSOR_3	IN3
#define SENSOR_4	IN4

#define MOTOR_BOTH  ( MOTOR_LEFT | MOTOR_RIGHT )    /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T usSensor;

void from_wall(int distance_mm, float speed){

    usSensor = sensor_search(LEGO_EV3_US);  // finns även fler som börjar på US... in och cm. 
    us_set_mode_us_dist_cm(usSensor);       // mm och inte cm

    tacho_set_speed_sp(MOTOR_BOTH, tacho_get_max_speed(MOTOR_LEFT, 0) * speed);  // Set speed for both motors

    //while (sensor_get_value0(usSensor, 0) < distance){
    tacho_run_forever(MOTOR_BOTH);
    while (sensor_get_value0(usSensor, 0) < distance_mm){
    }

    printf("Stopping\n");

    tacho_stop(MOTOR_BOTH);
}