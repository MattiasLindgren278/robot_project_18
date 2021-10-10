/**
 * \author  Otto Heile, email: ottoeh@kth.se
 * \brief   Initialize the brick and check that all necessary components are connected.
 * \return  int: Whether or not the initialization is successful (1 or 0).
 */
extern int init();

/**
 * \author  Otto Heile, email: ottoeh@kth.se
 *  \brief  Rotate the robot.
 *  \param  direction(char)     Which direction the robot will rotate ('r' or 'l').
 *  \param  degrees(int)        How much the robot will rotate.
 *  \param  speed(float)        How fast the robot will rotate (0 - 1).
 *  \return N/A
 */
extern void rotate(char direction, int degrees, float speed);

/**
 * \author  Mattias Lindgren Swenne, email: mattls@kth.se
 * \brief   Drop the book.
 * \return  N/A
 */
extern void drop();

/**
 * \author Zhonghao Yang, email: zhyang@kth.se
 */
extern void find_wall();

/**
 * \author Vincent Ferrigan, email: ferrigan@kth.se
 * \brief  Drive forwards or backwards.
 * \param  distance(int)    Distance to drive in millimeters. Negative values will drive the robot backwards.       
 * \param  speed(float)     How fast the robot will drive (0 - 1).
 * \return N/A
 */
extern void drive(int distance, float speed);

/**
 * \author  Vincent Ferrigan, email: ferrigan@kth.se
 * \brief   Drive away from a wall. 
 * \param   distance(int)   Distance from the wall in millimeters. 
 * \param   speed(float)    How fast the robot will drive (0 - 1).
 * \return  N/A  
 */
extern void from_wall(int distance, float speed);

/** 
 * \author  Vincent Ferrigan, email:ferrigan@kth.se
 * \brief   Drive towards a wall.
 * \param   distance(int)   Approximate distance to the wall in millimeters.
 *                          When this distance is reached, the robot will drive 2 more seconds to ensure correct positioning.
 * \param   speed(float)    How fast the robot will drive (0 - 1).
 * \return  N/A
 */
extern void to_wall(int distance, float speed);
