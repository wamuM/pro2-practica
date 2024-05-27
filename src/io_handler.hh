/**
 * @file io_handler.hh
 * @brief This file has everything necesary to deal with user input and program output
 *
 * This file has functions to throw erros, deal with input and to interpret commands but not to "read objects" as that task is left to each class.
 */

#pragma once

#include "River.hh"
#include "Catalogue.hh"
#include "Ship.hh"
#include "City.hh"

/**
* @brief A function that reads the std input and interprets the operations there.
*
* The list of possible operations, and their function can be found in the problem statement (enunciado.pdf)
*
* @pre halt is set to false and river, catalogue and ship have been properly initialized
* @post The first command in the std input stream has been read (thus removed from the stream) and executed
* @cplx Depends on the command
*/
void interpret_command(bool& halt, River& river, Catalogue& catalogue, Ship& ship);

/**
 * @brief A function that prints an error message corresponding to an error code
 *
 * @pre errorCode is a valid errorCode
 *
 * @post The error message has been printed in the std output
 *
 * @cplx Constant
 */
void error(int error_code);

/**
* @brief A function that consumes a specified number of tokens from the std input
*
* @pre There are numberOfTokens tokens in the std input
* @post A total of numberOfTokens tokens have been consumed from the std input
*
* @cplx Linear to numberOfTokens
*/
void consume(int numberOfTokens);


