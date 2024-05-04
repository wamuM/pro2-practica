#include "io_hanlder.hh"

#include <string>
#include <iostream>
#include <stream>
using namespace std;

#include "River.hh"
#include "Catalogue.hh"
#include "Ship.hh"
#include "City.hh"

void interpret_command(bool& halt, River& river, Catalogue& catalogue, Ship& ship){
	string command;
	getline(cin,command);
	istringstream args(command);

	//echo command
	cout<<'#'<<command;

	args>>verb;
	if(verb != "//"){
	if(verb == "lr" or verb == "leer_rio"){
		river.read();
		ship.clear_log();
	}else if(verb == "li" or verb == "leer_inventario"){
		string cityId;
		args>>cityId;
		if(river.has_city(cityId)){
			City city;	
			city.read();
			river.set_city(cityId, city);
		}else cout<<"error: no existe la ciudad"<<endl;
	}else if(verb == "ls" or verb == "leer_inventarios"){
		
	}else if(verb == "mb" or verb == "modificar_barco"){
		int buyId, buyAmount, sellId, sellAmount;
		args>>buyId>>buyAmount>>sellId>>sellAmount;
		
		if(not catalogue.has_product(buyId) or not catalogue.has_product(sellId)){
			cout<<"error: no existe el producto"<<endl;
		}else if(buyId == sellId){
			cout<<"error: no se puede comprar y vender el mismo producto"<<endl;
		}else{
			ship.set_buy(buyId, buyAmount);
			ship.set_sell(sellId, sellAmount);
		}
	}else if(verb == "eb" or verb == "escribir_barco"){
		ship.print_cargo(); 
		ship.print_log();
	}else if(verb == "cn" or verb == "consultar_num"){
		cout<<catalogue.size()<<endl;
	}else if(verb == "ap" or verb == "agregar_productos"){
		catalogue.read();		
	}else if(verb == "ep" or verb == "escribir_prodcucto"){
		int productId;
		args>>productId;
		if(not catalogue.has_product(productId)){
			cout<<"error: no existe el producto"<<endl;
		}else{
			catalogue.print_product(productId);
		}
	}else if(verb == "ec" or verb == "escribir_ciudad"){
		string cityId;
		args>>cityId;
		if(not river.has_city(cityId)){
			cout<<"error: no existe la ciudad"<<endl;
		}else{
			river.get_city(cityId).print();
		}

	}else if(verb == "pp" or verb == "poner_prod"){
		string cityId, productId;
		int stock, demand;
		args>>cityId>>productId>>stock>>demand;
		if(not catalogue.has_product(productId)){
			cout<<"error: no existe el producto"<<endl;
		}else if(not river.has_city(cityId)){
			cout<<"error: no existe la ciudad"<<endl;	
		}else{
			City city = river.get_city(cityId);	
			if(city.has_product(productId)){
				cout<<"error: la ciudad ya tiene el producto"<<endl;	
			} else {
				Product product = catalogue.get_product(productId);
				city.set_stock(product, stock);
				city.set_demand(product, demand);	
			}

		}
	}else if(verb == "mp" or verb == "modificar_producto"){
		string cityId, productId;
		int stock, demand;
		args>>cityId>>productId>>stock>>demand;

		if(not catalogue.has_product(productId)){
			cout<<"error: no existe el producto"<<endl;	
		}else if(not river.has_city(cityId)){
			cout<<"error: no existe la ciudad"<<endl;	
		}else{
			City city = river.get_city(cityId);	
			if(not city.has_product(productId)){
				cout<<"error: la ciudad no tiene el producto"<<endl;	
			} else {
				Product product = catalogue.get_product(productId);
				city.set_stock(product, stock);
				city.set_demand(product, demand);	
			}
		}
	}else if(verb == "qp" or verb == "quitar_producto"){
		string cityId, productId;
		args>>cityId>>productId;

		if(not catalogue.has_product(productId)){
			cout<<"error: no existe el producto"<<endl;	
		}else if(not river.has_city(cityId)){
			cout<<"error: no existe la ciudad"<<endl;	
		}else{
			City city = river.get_city(cityId);	
			if(not city.has_product(productId)){
				cout<<"error: la ciudad no tiene el producto"<<endl;	
			} else {
				Product product = catalogue.get_product(productId);
				city.remove_product(product);
			}
		}
	}else if(verb == "cp" or verb == "consultar_producto"){
		string cityId, productId;
		args>>cityId>>productId;

		if(not catalogue.has_product(productId)){
			cout<<"error: no existe el producto"<<endl;	
		}else if(not river.has_city(cityId)){
			cout<<"error: no existe la ciudad"<<endl;	
		}else{
			City city = river.get_city(cityId);	
			if(not city.has_product(productId)){
				cout<<"error: la ciudad no tiene el producto"<<endl;	
			} else {
				cout<<  city.get_stock().get_amount(productId) << ' '
				    << city.get_demand().get_amount(productId) << endl;
			}
		}
	}else if(verb == "co" or verb == "comerciar"){
		string cityId1, cityId2;
		args>>cityId1>>cityId2;		
		if(not river.has_city(cityId1) or not river.has_city(cityId2)){
			cout<<"error: no existe la ciudad"<<endl;	
		}else {
			river.trade(ship, cityId1, cityId2);	
		}
	}else if(verb == "re" or verb == "redistribuir"){
		river.redistribute(ship);	
	}else if(verb == "hv" or verb == "hacer_viaje"){
		river.do_trip()
	}else if(verb == "fin")halt = true;
         else cout<<"error: commando desconocido"<<endl;
	}	
};

