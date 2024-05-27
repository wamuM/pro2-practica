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
// not same/exist city/product (I spent way too much time giving logic to the err codes)
constexpr int   PRODUCT_IN_CITY  = 7; 
constexpr int N_PRODUCT_IN_CITY  = 6;
constexpr int    CITY_N_EXIST    = 5;
constexpr int PRODUCT_N_EXIST    = 4;  
constexpr int    SAME_CITY       = 3; 
constexpr int    SAME_PRODUCT    = 2;
//My hope is that this gets optimized at compile time. (Like #define but data safe?)
void error(int errorCode){
	cout<<"error: ";
	if(errorCode == UNKNOWN_COMMAND       )cout<<"commando desconocido"<<endl;	
	else if(errorCode ==   PRODUCT_IN_CITY)cout<<"la ciudad ya tiene el producto"<<endl;	
	else if(errorCode == N_PRODUCT_IN_CITY)cout<<"la ciudad no tiene el producto"<<endl;	
	else if(errorCode ==    CITY_N_EXIST  )cout<<"no existe la ciudad"<<endl;	
	else if(errorCode == PRODUCT_N_EXIST  )cout<<"no existe el producto"<<endl;	
	else if(errorCode == SAME_CITY        )cout<<"ciudad repetida"<<endl;	
	else if(errorCode == SAME_PRODUCT     )cout<<"no se puede comprar y vender el mismo producto"<<endl;	
}
void interpret_command(bool& halt, River& river, Catalogue& catalogue, Ship& ship){
	string verb;
	cin>>verb;

	//special commands
	if(verb == "//"){
		string dummy;
		getline(cin,dummy);
		return;
	}
	if(verb == "fin"){ 
		halt = true; 
		return;
	}
	//echo command
	cout<<'#'<<verb;
		
	if(verb == "lr" or verb == "leer_rio"){
		cout<<endl;
		river.read();
		ship.clear_log();

	}else if(verb == "li" or verb == "leer_inventario"){
		string cityId; 
		int productCount;
		cin>>cityId>>productCount;
		cout<<' '<<cityId<<endl;

		if(not river.has_city(cityId)){
			consume(productCount*3);
			error(CITY_N_EXIST); 
			return;	
		}
		if(not river.apply_read_inventory(cityId, productCount, catalogue)){
			consume(2 + productCount*3);
			error(PRODUCT_N_EXIST);
		}

	}else if(verb == "ls" or verb == "leer_inventarios"){
		cout<<endl;
		string cityId;
		cin>>cityId;
		while(cityId != "#"){
			int productCount;
			cin>>productCount;
			
			if(not river.has_city(cityId)){
				consume(productCount*3);
				error(CITY_N_EXIST);
			}
				
			if(not river.apply_read_inventory(cityId, productCount, catalogue)){
				consume(2 + productCount*3);
				error(PRODUCT_N_EXIST);
			};
			cin>>cityId;
		}
	}else if(verb == "mb" or verb == "modificar_barco"){//We are not using ship.read() because ship.read() assumes the data is valid
		cout<<endl;
		int sellProductId, sellAmount,
		     buyProductId,  buyAmount;
		cin>> buyProductId >> buyAmount
		   >> sellProductId>> sellAmount;

		if((not catalogue.has_product(sellProductId)) or (not catalogue.has_product(buyProductId))) error(PRODUCT_N_EXIST);
		else if(sellProductId == buyProductId) error(SAME_PRODUCT);
		else {
			ship.set_supply(sellProductId, sellAmount);
			ship.set_demand(buyProductId,  buyAmount);
		}
	}else if(verb == "eb" or verb == "escribir_barco"){
		cout<<endl;
		ship.print();
	}else if(verb == "cn" or verb ==  "consultar_num"){
		cout<<endl
		    <<catalogue.size()<<endl;
	}else if(verb == "ap" or verb == "agregar_productos"){
		int productCount;
		cin>>productCount;
		cout<<' '<<productCount<<endl;
		catalogue.read(productCount);
	}else if(verb == "ep" or verb == "escribir_producto"){
		int productId;
		cin>>productId;
		cout<<' '<<productId<<endl;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else {
			cout<<productId<<' ';//This does not appear in the description of the instruction but it does in the "correct" outputs
			catalogue.print_product(productId);
		}
		
	}else if(verb == "ec" or verb == "escribir_ciudad"){
		string  cityId;
		cin >> cityId;
		cout<<' '<<cityId<<endl;

		if(river.has_city(cityId))river.get_city(cityId).print();
		else error(CITY_N_EXIST);
	}else if(verb == "pp" or verb == "poner_prod"){
		string cityId;
		int productId, supply, demmand;
		cin>>cityId>>productId>>supply>>demmand;
		cout<<' '<<cityId<<' '<<productId<<endl;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else{
			if(river.get_city(cityId).has_product(productId)){ error(PRODUCT_IN_CITY); return; }
		
			river.apply_set_product_market(cityId, productId, catalogue.get_product(productId), supply, demmand);
			river.get_city(cityId).print_total();
		}
	}else if(verb == "mp" or verb == "modificar_prod"){
		string cityId;
		int productId, supply, demmand;
		cin>>cityId>>productId>>supply>>demmand;
		cout<<' '<<cityId<<' '<<productId<<endl;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			if(not river.get_city(cityId).has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			
			river.apply_set_product_market(cityId, productId, catalogue.get_product(productId), supply, demmand);
			river.get_city(cityId).print_total();
		}
	}else if(verb == "qp" or verb == "quitar_prod"){
		string cityId;
		int productId;
		cin>>cityId>>productId;
		cout<<' '<<cityId<<' '<<productId<<endl;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			if(not river.get_city(cityId).has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			
			river.apply_remove_product(cityId, productId, catalogue.get_product(productId));
			river.get_city(cityId).print_total();
		}

	}else if(verb == "cp" or verb == "consultar_prod"){

		string cityId;
		int productId;
		cin>>cityId>>productId;
		cout<<' '<<cityId<<' '<<productId<<endl;

		if(not catalogue.has_product(productId)) error(PRODUCT_N_EXIST);
		else if(not river.has_city(cityId)) error(CITY_N_EXIST);
		else {
			City city = river.get_city(cityId);
			if(not city.has_product(productId)){ error(N_PRODUCT_IN_CITY); return; }
			city.print_product_market(productId);
		}

	}else if(verb == "co" or verb == "comerciar"){
		string cityId1, cityId2;
		cin>>cityId1>>cityId2;
		cout<<' '<<cityId1<<' '<<cityId2<<endl;
		     if(not river.has_city(cityId1))error(CITY_N_EXIST);
		else if(not river.has_city(cityId2))error(CITY_N_EXIST); 
		else if(cityId1 == cityId2)         error(SAME_CITY);
		else river.trade(catalogue, cityId1, cityId2);

	}else if(verb == "re" or verb == "redistribuir"){
		cout<<endl;
		river.redistribute(catalogue);

	}else if(verb == "hv" or verb == "hacer_viaje"){
		cout<<endl;
		cout<<river.do_trip(ship, catalogue)<<endl;

	} else {
		cout<<endl;
		error(UNKNOWN_COMMAND); 
	}
};

