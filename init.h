/**
 * \brief   Initialize the brick and check that all necessary components are connected.
 * \param   max_driving_speed(int*)     Address of variable storing maximum speed for driving motors.
 * \param   drop_speed(int*)            Address of variable storing speed for drop motor.
 * \return  int: Whether or not the initialization is successful (1 or 0).
 */
extern int init(int* max_driving_speed, int* drop_speed);