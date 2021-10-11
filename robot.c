#include <stdio.h>
#include "brick.h"
#include "robot.h"

#define MOTOR_RIGHT     OUTA
#define MOTOR_LEFT      OUTB
#define MOTOR_BOTH      (MOTOR_LEFT | MOTOR_RIGHT)
#define MOTOR_DROP      OUTC
#define SENSOR_US       IN3

#define ROTATION_CORRECTION  2.05f
#define PULSE_PER_MM 1.9f
#define SENSOR_US_MARGIN 5
#define DRIVING_CORRECTION 0.9995f
int max_driving_speed;
int drop_speed;

POOL_T sensor_us;

int init(){
    printf("Initializing...\n");

    /* Unsuccessful initialization for an unknown reason
     * Print the error and return 0 */
    if(!brick_init()){
        printf("ERROR: Unable to initialize brick. Error called from function init() located in init.c.\n");
        sleep_ms(100);
        return 0;
    }

    /* Check if every necessary component is plugged in
     * If one is not, print an error and return 0
     */
    if(!(tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_) && tacho_is_plugged(MOTOR_DROP, TACHO_TYPE__NONE_) && sensor_is_plugged(SENSOR_US, TACHO_TYPE__NONE_))){
        brick_uninit();
        printf("ERROR: One or more components are not connected. Error called from function init() located in init.c.\n");
        sleep_ms(100);
        return 0;
    }
    
    // Set maximum speed of driving and drop motors
    max_driving_speed = tacho_get_max_speed(MOTOR_LEFT, 0);
    drop_speed = tacho_get_max_speed(MOTOR_DROP, 0) * 0.1f;

    // Find ultrasonic sensor and set distance mode to millimeters
    sensor_us = sensor_search(LEGO_EV3_US);
    us_set_mode_us_dist_cm(sensor_us);

    // Reset driving and drop motors
    tacho_reset(MOTOR_BOTH);
    tacho_reset(MOTOR_DROP);

    // Print that initialization was successful and return 1
    printf("Initialization successful!\n"
            "******** Welcome! ********\n");
    sleep_ms(100);
    return 1;
}

void rotate(char direction, int degrees, float speed, int halt){
    tacho_set_speed_sp(MOTOR_BOTH, tacho_get_max_speed(MOTOR_LEFT, 0) * speed);  // Set speed for both motors

    switch(direction){
        /* Set a new position for both motors
         * Positive for the left motor relative to the current position
         * Negative for the right motor relative to the current position
         * Results in rotation to the right */
        case('r'):
            printf("Rotating right %d degrees\n", degrees);
            tacho_set_position_sp(MOTOR_LEFT, degrees * ROTATION_CORRECTION);
            tacho_set_position_sp(MOTOR_RIGHT, -degrees * ROTATION_CORRECTION);
            break;

        /* Set a new position for both motors
         * Positive for the right motor relative to the current position
         * Negative for the left motor relative to the current position
         * Results in rotation to the left */
        case('l'):
            printf("Rotating left %d degrees\n", degrees);
            tacho_set_position_sp(MOTOR_RIGHT, degrees * ROTATION_CORRECTION);
            tacho_set_position_sp(MOTOR_LEFT, -degrees * ROTATION_CORRECTION);
            break;

        /* No valid direction given
         * Print the error and exit the function */
        default:
            printf("ERROR: Parameter direction only accepts argument 'r' or 'l'. Error called from function rotate() located in rotation.c.\n");
            return;
    }
    tacho_run_to_rel_pos(MOTOR_BOTH);   // Run the motors to the newly set positions

    // Halt the program until the rotation is finished if halt is given
    if(halt){
        while(tacho_is_running(MOTOR_BOTH));
    }
}

void drop(){
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

void find_wall(){
    int min_dist = 2500;

    rotate('r', 360, 0.1, 0);
    sleep_ms(1);
    while (tacho_is_running(MOTOR_RIGHT)){
        int curr_dist = sensor_get_value0(sensor_us, 0);
        sleep_ms(1);

        if (curr_dist < min_dist){
            min_dist = curr_dist;
            printf("min dist: %d\n", min_dist);
        }
    }

    rotate('l', 360, 0.1, 0);
    sleep_ms(1);
    while (tacho_is_running(MOTOR_LEFT)){
        int curr_dist = sensor_get_value0(sensor_us, 0);
        sleep_ms(1);
        printf("curr dist: %d\n", curr_dist);

        if (curr_dist <= (min_dist + SENSOR_US_MARGIN)){
            tacho_stop(MOTOR_BOTH);
        }
    }
}

void drive(int distance, float speed){
    tacho_set_speed_sp(MOTOR_RIGHT, max_driving_speed * speed * DRIVING_CORRECTION); // Helst 0.5
    tacho_set_speed_sp(MOTOR_LEFT, max_driving_speed * speed); // Helst 0.5

    tacho_set_position_sp(MOTOR_RIGHT, distance * PULSE_PER_MM);    // sätter antalet pulsar den ska köra
    tacho_set_position_sp(MOTOR_LEFT, distance * PULSE_PER_MM);    // sätter antalet pulsar den ska köra

    tacho_run_to_rel_pos(MOTOR_BOTH);                   // kör motorerna position + position_sp

    while(tacho_is_running(MOTOR_BOTH));
}

void from_wall(int distance, float speed){
    tacho_set_speed_sp(MOTOR_BOTH, max_driving_speed * -speed);

    tacho_run_forever(MOTOR_BOTH);
    while (sensor_get_value0(sensor_us, 0) < distance);

    printf("Stopping\n");
    tacho_stop(MOTOR_BOTH);
}

void to_wall(int distance, float speed){
    tacho_set_speed_sp(MOTOR_BOTH, max_driving_speed * speed);  // Set speed for both motors

    tacho_run_forever(MOTOR_BOTH);
    while (tacho_is_running(MOTOR_BOTH)){
        if(sensor_get_value0(sensor_us, 0) < distance){
            sleep_ms(2000);
            break;
        }
    }

    printf("Stopping\n");
    tacho_stop(MOTOR_BOTH);
}
