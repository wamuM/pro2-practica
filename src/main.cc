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
