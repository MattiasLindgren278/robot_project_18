#include <stdio.h>
#include "brick.h"
#include "rotation.h"

#define MOTOR_RIGHT         OUTA
#define MOTOR_LEFT          OUTB
#define MOTOR_BOTH          (MOTOR_LEFT | MOTOR_RIGHT)

#define ROTATION_CORRECTION  1.83f

void rotate(char direction, int degrees, float speed){
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
}