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

int max_hastighet;         /* variabel för max hastighet på motorn */
POOL_T usSensor;

void from_wall(int distance_mm, float speed, int max_driving_speed){

    int distance = distance_mm;
    usSensor = sensor_search(LEGO_EV3_US);  // finns även fler som börjar på US... in och cm. 
    us_set_mode_us_dist_cm(usSensor);       // mm och inte cm
    tacho_set_speed_sp(MOTOR_BOTH, max_hastighet * -speed);

    while (sensor_get_value0(usSensor, 0) < distance){
        tacho_run_forever(MOTOR_BOTH);
    }

    printf("Stopping\n");

    tacho_stop(MOTOR_BOTH);
}