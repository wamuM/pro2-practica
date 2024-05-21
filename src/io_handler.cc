#include "io_handler.hh"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "River.hh"
#include "Catalogue.hh"
#include "Ship.hh"
#include "City.hh"


void consume(int numberOfTokens){
	string dummy;//I'm sure there is a better way of doing this
	for(int i = 0; i < numberOfTokens;++i)cin>>dummy;
}
void interpret_command(bool& halt, River& river, Catalogue& catalogue, Ship& ship){
	string command;
	getline(cin,command);
	istringstream args(command);

	//echo command
	cout<<'#'<<command;

	string verb;
	args>>verb;

	if(verb == "//")return;
		
	if(verb == "lr" or verb == "leer_rio"){
		river.clear();
		river.read_river();
		ship.
	}else if(verb == "li" or verb == "leer_inventario"){
	}else if(verb == "ls" or verb == "leer_inventarios"){
	}else if(verb == "mb" or verb == "modificar_barco"){
	}else if(verb == "eb" or verb == "escribir_barco"){
	}else if(verb == "cn" or verb == "consultar_num"){
	}else if(verb == "ap" or verb == "agregar_productos"){
	}else if(verb == "ep" or verb == "escribir_prodcucto"){
	}else if(verb == "ec" or verb == "escribir_ciudad"){
	}else if(verb == "pp" or verb == "poner_prod"){
	}else if(verb == "mp" or verb == "modificar_producto"){
	}else if(verb == "qp" or verb == "quitar_producto"){
	}else if(verb == "cp" or verb == "consultar_producto"){
	}else if(verb == "co" or verb == "comerciar"){
	}else if(verb == "re" or verb == "redistribuir"){
	}else if(verb == "hv" or verb == "hacer_viaje"){
	}else if(verb == "fin"){ halt = true; } 
        else cout<<"error: commando desconocido"<<endl;
};

