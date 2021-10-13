/**
 * Project group 18
 * Course: II1300, HT21-1, Ingenjörsmetodik
 * 
 * \author Vincent Ferrigan, email: ferrigan@kth.se
**/

#include <stdio.h>
#include "brick.h"
#include "robot.h"

int main(void){
    if(!init()){
        return 1;
}
    find_wall();
    to_wall(70, 0.3);
    from_wall(500, 0.3);
    rotate('r', 90, 0.1, 1); 
    drive(2500, 0.3);

    find_wall();
    to_wall(70, 0.3);
    from_wall(500, 0.3);
    
    rotate('r', 180, 0.1, 1);

    drop();
    rotate('r', 90, 0.1, 1);

    drive(2500, 0.3);


    return 0;
}