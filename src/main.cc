/**
 * @file main.cc
 * @brief Main Program 
 *
*/
/**
* @mainpage
* Final solution to the PRO2 Practical Exercice. 
* English was used in both comments and code (besides I/O messages) for cohesion with the names of the std library, our modules and the documentation.
* 
* ## General Description
* 
* The goal of this project is to simulate commerce between cities in a river basin. For that purpose the user is able to prompt to the program some information on the basin followed by a selection of commands until the "fin" command is executed. 
*
* ### Problem Statement and other documents
* We were provided the following documents:
* - [Problem Statement](https://www.cs.upc.edu/pro2/data/uploads/qp2024/practica/enunqp2024.pdf)
* - [Instructions](https://www.cs.upc.edu/pro2/data/uploads/qp2024/practica/instruccions_pra.pdf)
* - [Grading Criteria](https://www.cs.upc.edu/pro2/data/uploads/qp2024/practica/avaluacio_pra.pdf)
*
* [more...](https://www.cs.upc.edu/pro2/index.php?id=practica-primavera-2024)
* 
* ### Proof of validity
* We were also tasked to proove the validity of the following functions:
* - City::trade (comerciar)
* - River::_find_best_path (auxiliar de hacer_viaje)
*   
* Such proof can be found [here](nothingtoseehere)
*
* #### Notes
* - All complexity is in Big O notation
* - This code was submited at [jutge.org](https://jutge.org/problems/X20610_es) in a directory free format. For a more structured file directory check the [git repository](https://github.com/wamuM/pro2-practica).
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
