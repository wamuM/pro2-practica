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
// --- Error Codes ----
constexpr int UNKNOWN_COMMAND = 0;
// not same/exist city/product
constexpr int   PRODUCT_IN_CITY  = 7;
constexpr int N_PRODUCT_IN_CITY  = 6;
constexpr int    CITY_N_EXIST    = 5; 
constexpr int PRODUCT_N_EXIST    = 4;  
constexpr int    SAME_CITY       = 3;
constexpr int    SAME_PRODUCT    = 2;
//My hope is that this gets optimized at compile time. (Like #define but data safe?)
void error(int error_code){
	
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
		river.read();
		 ship.clear_log();

	}else if(verb == "li" or verb == "leer_inventario"){
		string cityId; 
		int productCount;
		args>>cityId;
		cin>>productCount;

		if(not river.has_city(args)){
			consume(productCount*3);
			error(CITY_N_EXIST); 
			return;	
		}
		City city = river.get_city(cityId);
		if(not city.read_inventory(catalogue)){
			consume(2 + productCount*3);
			error(PRODUCT_N_EXIST);
		}
		river.set_city(cityId, city);

	}else if(verb == "ls" or verb == "leer_inventarios"){
		string cityId;
		cin>>cityId;
		while(cityId != "#"){
			int productCount;

			if(not river.has_city(args)){
				consume(productCount*3);
				error(CITY_N_EXIST);
			}
			City city = river.get_city(cityId);	
			if(not city.read_inventory(catalogue)){
				consume(2 + productCount*3);
				error(PRODUCT_N_EXIST);
			};
			river.set_city(cityId, city);
			cin>>cityId;
		}
	}else if(verb == "mb" or verb == "modificar_barco"){//We are not using ship.read() because ship.read() assumes the data is valid
		int sellProductId, sellAmount,
		     buyProductId,  buyAmount;
		cin>>sellProductId>>sellAmount
		   >> buyProductId>> buyAmount;

		if((not catalogue.has_product(sellProductId)) or (not catalogue.has_product(buyProductId))) error(PRODUCT_N_EXIST);
		else if(sellProductId == buyProductId) error(SAME_PRODUCT);
		else {
			ship.set_supply(sellProductId, sellAmount);
			ship.set_demand(buyProductId,  buyAmount);
		}
	}else if(verb == "eb" or verb == "escribir_barco") ship.print();
	 else if(verb == "cn" or verb ==  "consultar_num") cout<<catalogue.size()<<endl;
	 else if(verb == "ap" or verb == "agregar_productos"){
		int productAmount;
		cin>>productAmount;

		catalogue.read(productAmount);

	}else if(verb == "ep" or verb == "escribir_prodcucto"){
		int productId;
		cin>>productId;

		if(catalogue.has_product(productId))catalogue.print_product(productId);
		else error(PRODUCT_N_EXIST);
		
	}else if(verb == "ec" or verb == "escribir_ciudad"){
		string  cityId;
		args >> cityId;

		if(river.has_city(cityId))river.get_city(cityId).print();
		else error(CITY_N_EXIST);
	}else if(verb == "pp" or verb == "poner_prod"){
		string cityId;
		int productId, supply, demmand;
		args>>cityId>>productId>>supply>>demmand;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else{
			City city = river.get_city(cityId);
			if(city.has_product(productId)){ error(PRODUCT_IN_CITY); return; }
		
			city.set_product_market(productId, catalogue.get_product(productId), supply, demmand);
			river.set_city(cityId, city);
		}
	}else if(verb == "mp" or verb == "modificar_producto"){
		string cityId;
		int productId, supply, demmand;
		args>>cityId>>productId>>supply>>demmand;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			City city = river.get_city(cityId);
			if(not city.has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			
			city.set_product_market(productId, catalogue.get_product(productId), supply, demmand);
			river.set_city(cityId, city);
		}
	}else if(verb == "qp" or verb == "quitar_producto"){
		string cityId;
		int productId;
		args>>cityId>>productId;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			City city = river.get_city(cityId);
			if(not city.has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			
			city.remove_product(productId, catalogue.get_product(productId));
			river.set_city(cityId, city);
		}

	}else if(verb == "cp" or verb == "consultar_producto"){

		string cityId;
		int productId;
		args>>cityId>>productId;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			City city = river.get_city(cityId);
			if(not city.has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			
			city.print_product(productId);
			river.set_city(cityId, city);
		}

	}else if(verb == "co" or verb == "comerciar"){
		string cityId1, cityId2;
		args>>cityId1>>cityId2;
		     if(not river.has_city(cityId1))error(CITY_N_EXIST);
		else if(not river.has_city(cityId2))error(CITY_N_EXIST); 
		else if(cityId1 == cityId2)         error(SAME_CITY);
		else river.trade(ship, cityId1, cityId2);

	}else if(verb == "re" or verb == "redistribuir"){
		river.redistribute(ship);

	}else if(verb == "hv" or verb == "hacer_viaje"){
		river.do_trip(ship);

	}else if(verb == "fin"){ halt = true; } 
        else error(UNKNOWN_COMMAND); 
};

