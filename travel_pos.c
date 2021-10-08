#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define sleep( msec ) usleep(( msec ) * 1000 ) /* Definerar sleep, Sleep(1000)= 1 sekund */

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    	OUTC
#define MOTOR_D    	OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2	IN2
#define SENSOR_3	IN3
#define SENSOR_4	IN4

#define MOTOR_BOTH     	( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

int max_hastighet;         /* variabel för max hastighet på motorn */
POOL_T usSensor;
// POOL_T touchSensor;

int init();
void drive(float, int);

int main( void )
{
    init();

/* del av init koden */

    if(!sensor_is_plugged(SENSOR_3, SENSOR_TYPE__NONE_)) {
        printf("Stoppa in sensorn i port 3\n");
        brick_uninit();
        return(0);
        }

    usSensor = sensor_search(LEGO_EV3_US); // finns även fler som börjar på US... in och cm. 
    
    us_set_mode_us_dist_cm(usSensor); // mm och inte cm
    
    float   travel_distance_mm  = 2500;                             //mm
    float   puls_per_mm    = 2.13427856547123;                      //antalet pulsar per mm. 350 puls är ett snurr
    float   travel_distance_pos = puls_per_mm * travel_distance_mm; //stop i antal puls.

    travel_distance_pos = (int)travel_distance_pos;


    //int count_position = tacho_get_position(MOTOR_RIGHT, 0);      //kopplat till while-loopen   
    //int stop_position = count_position + travel_distance_pos;     //kopplat till while-loopen

    int stop_position = travel_distance_pos;   


tacho_set_speed_sp(MOTOR_BOTH, max_hastighet * 0.5);
tacho_set_position(MOTOR_BOTH, 0);                              //sätter start pos till 0
tacho_set_position_sp(MOTOR_BOTH, travel_distance_pos);         // sätter antalet pulsar den ska köra 
// tacho_run_to_rel_pos(MOTOR_BOTH);                               // kör motorerna position + position_sp 
tacho_run_to_abs_pos(MOTOR_BOTH);

    //drive(1,0);
 /*   while (count_position < stop_position)
    {


        count_position = tacho_get_position(MOTOR_RIGHT, 0);
        printf("position %d", count_position);

    }
*/
    printf("Stopping\n");
    
    tacho_stop(MOTOR_BOTH);

    brick_uninit();
    printf("Shutting down...\n");
    return 0;
}

int init(){
    printf("Initializing...\n");

    if (!brick_init()){
        printf("ERROR: Unable to initialize brick.\n");
        sleep(100);
        return 0;
    }

    if (tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )){
        max_hastighet = tacho_get_max_speed(MOTOR_LEFT, 0);
        tacho_reset(MOTOR_BOTH);
        printf("Initialization successful!\n"
               "******** Welcome! ********\n");
        sleep(100);
        return 1;
    } 
    else{
        brick_uninit();
        printf("ERROR: No motors connected.\n"
        "Connect left motor to port A and right motor to port B.\n");
        sleep(100);
        return 0;
    }
}
void drive(float speed, int runtime_msec){
    printf("Driving\n");
    tacho_set_speed_sp(MOTOR_BOTH, max_hastighet * speed * 0.5);
    tacho_run_forever(MOTOR_BOTH);
    sleep(runtime_msec);
}