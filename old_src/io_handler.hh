/**
 * @file io_handler.hh
 * @brief This file has everything necesary to deal with user input
 *
 * This file has functions to interpret commands but not to "read objects" as that task is left to each class. 
 */

#pragma once

/**
* @brief A function that reads the std input and interprets the operations there.
*
* The list of possible operations, and their function can be found in the problem statement (enunciado.pdf)
*
* @pre True
* @param halt A boolean passed by reference that is set to true whenever the program should stop
* @post The first command in the std input stream has been read (thus removed from the stream) and executed
*/
void interpret_command(bool& halt);

