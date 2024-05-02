using namespace std;
#include "io_handler.hh"

int main(){
	Catalogue catalogue;
	catalogue.read();

	River river;
	river.read();
	
	Ship ship;

	bool halt = false;
	while(not halt) interpet_command(halt, river, catalogue, ship);

}
