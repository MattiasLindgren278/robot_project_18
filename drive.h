/**
 *  \brief  Drive n millimeters forward or backwards
 *  \param  distance_mm(float)          Drive n millimeters. Negative values will drive the robot backwards.       
 *  \param  speed(float)                How fast the robot will drive (0 - 1).
 *  \param  max_driving_speed(int)      Max speed for driving motors
 *  \return N/A
 */
extern void drive(int distance_mm, float speed, int max_driving_speed);