#include <stdio.h>
#include "brick.h"
#include "robot.h"

int main(void){
    if(!init()){
        return 1;
}
   // rotate('r', 90, 0.1, 1); 
   // sleep_ms(5000);
   // rotate('l', 90, 0.1, 1); 
   // sleep_ms(5000);

//    rotate('r', 180, 0.1, 1); 
  //  sleep_ms(5000);
    //rotate('l', 180, 0.1, 1); 
    drive(1600, 0.3);
    return 0;
}