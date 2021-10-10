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
