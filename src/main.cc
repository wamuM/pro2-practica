/**
 * @file main.cc
 * @brief Main Program 
 *
*/
/**
* @mainpage
* For a better organized code file tree go to the github repo since jutge.org didn't allow to use folders.
* 
* The main program can be found at main.cc.
*
* Typedefs where used to abstract complex types or for clarity like Market, Product and Inventory. 
*
* English was used in comments and code (besides I/O) for cohesion with the names of the std library).
*
* Github: https://github.com/wamuM/pro2-practica
*/
#include "Catalogue.hh"
#include "River.hh"
#include "Ship.hh"

#include "io_handler.hh"


int main(){
	Catalogue catalogue;
	catalogue.read();

	River river;
	river.read();

	Ship ship;
	ship.read();

	bool halt = false;
	while(not halt) interpret_command(halt, river, catalogue, ship);

}
