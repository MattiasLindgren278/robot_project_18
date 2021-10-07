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

    //while(!sensor_get_value(0, touchSensor, 0));

/* del av init koden */

    if(!sensor_is_plugged(SENSOR_3, SENSOR_TYPE__NONE_)) {
        printf("Stoppa in sensorn i port 3\n");
        brick_uninit();
        return(0);
        }

    usSensor = sensor_search(LEGO_EV3_US); // finns även fler som börjar på US... in och cm. 
    
    //us_set_mode_us_dc_cm(usSensor);
    us_set_mode_us_dist_cm(usSensor); // mm och inte cm
    
    //int buffer_fulltravel;
//    int buffer_sp;
//    int buffer_cycle_sp;
//    int buffer_rot;
    int buffer;
    int buffer_cycle;
//    int count_pm;
    // get_tacho_position(MOTOR_BOTH, &buffer);
    //get_tacho_position_sp(MOTOR_BOTH, &buffer_sp);
    drive(1,0);

    while (sensor_get_value0(usSensor, 0) > 500)
    {
        // buffer_fulltravel = tacho_get_full_travel_count(MOTOR_RIGHT, 0);
 //       buffer_sp = tacho_get_position_sp(MOTOR_RIGHT, 0);
  //      buffer_cycle_sp = tacho_get_duty_cycle_sp(MOTOR_RIGHT, 0);
//        buffer_rot = tacho_get_count_per_rot(MOTOR_RIGHT, 0);

        buffer = tacho_get_position(MOTOR_RIGHT, 0);
        buffer_cycle = tacho_get_duty_cycle(MOTOR_RIGHT, 0);

//        count_pm = tacho_get_count_per_m(MOTOR_RIGHT, 0);
        
        // printf("buffern travel är %d\n", buffer_fulltravel);
//        printf("buffern med sp %d\n", buffer_sp);
//        printf("buffern med cycle sp %d\n", buffer_cycle_sp);
//        printf("buffern med rot %d\n", buffer_rot);
        printf("\nDistansen %f\n", sensor_get_value0(usSensor, 0));
        printf("Position %d\n", buffer);
        printf("Dutycycle %d\n", buffer_cycle);

//        printf("count pm är %d\n", count_pm);


    }
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