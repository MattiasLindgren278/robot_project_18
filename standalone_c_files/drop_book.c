#include <stdio.h>
#include "brick.h"
#include "init.h"

#define MOTOR_DROP      OUTC
#define SENSOR_TOUCH    IN2

int drop_speed;
int max_driving_speed;
POOL_T touchSensor;

void drop();

void drop(){
    drop_speed = tacho_get_max_speed(MOTOR_DROP, 0) * 0.1f;//set speed for drop_speed
    
    /* Set drop speed for motor_drop
    * Start motor_drop
    * Wait one second
    * Stop motor_drop */
    printf("Dropping book\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);

    /* Set speed * -1 for motor_drop
    * Start motor_drop
    * Wait one second
    * Stop motor_drop */
    printf("Resetting position\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed * -1);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);
}