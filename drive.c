#include <stdio.h>
#include "brick.h"
#include "drive.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_BOTH  ( MOTOR_LEFT | MOTOR_RIGHT )    /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

#define PULS_PER_CM 2.134f               /* Antalet pulsar per mm. 350 puls är ett snurr*/

void drive(int distance_mm, float speed){

    tacho_set_speed_sp(MOTOR_BOTH, tacho_get_max_speed(MOTOR_LEFT, 0) * speed);  // Set speed for both motors
    
    tacho_set_position(MOTOR_RIGHT, 0);                  //sätter start position till 0
    tacho_set_position(MOTOR_LEFT, 0);                  //sätter start position till 0
    tacho_set_position_sp(MOTOR_LEFT, distance_mm * PULS_PER_CM);  // kör motorerna position + position_sp (distance_mm * PULS_PER_CM)
    tacho_set_position_sp(MOTOR_RIGHT, distance_mm * PULS_PER_CM);  // kör motorerna position + position_sp (distance_mm * PULS_PER_CM)
    
    tacho_run_to_rel_pos(MOTOR_BOTH);                               // Run the motors to the newly set positions
}