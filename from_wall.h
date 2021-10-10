/**
*   \brief      Drive towards the wall. 
*   \param      distance_to_wall_mm(float)  Distance from the wall, in millimeters. 
*   \param      speed(float)                How fast the robot will drive (0 - 1).
*   \param      max_driving_speed()         Max speed driving motors
*   \return     N/A  
*/
extern void from_wall(int distance_mm, float speed, int max_driving_speed);