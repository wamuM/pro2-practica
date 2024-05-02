#include "io_hanlder.hh"

#include <string>
using namespace std;

void interpret_command(bool& halt, River& river, Catalogue& catalogue, Ship& ship){
	string command;
	if(command == "lr" or command == "leer_rio"){
		river.read();
	}else if(command == "li" or command == "leer_inventario"){
		string cityId;
		cin>>cityId;
		if(river.hasCity(cityId)){
			river.getCity(cityId).getStock().print();
		}else cout<<"Error: city does not exist"<<endl;
	}else if(command == "ls" or command == "leer_inventarios"){
		// TODO
	}else if(command == "mb" or command == "modificar_barco"){
		int buyId, buyAmount, sellId, sellAmount;
		cin>>buyId>>buyAmount>>sellId>>sellAmount;
		
		if(not catalogue.hasProduct(buyId) or not catalogue.hasProduct(sellId)){
			cout<<"Error: the product doesn't exist"<<endl;
		}else if(buyId == sellId){
			cout<<"Error: ship wants and sells the same"<<endl;
		}else{
			ship.setBuy(buyId, buyAmount);
			ship.setSell(sellId, sellAmount);
		}
	}else if(command == "eb" or command == "escribir_barco"){
		ship.printCargo(); 
		ship.printLog();
	}else if(command == "cn" or command == "consultar_num"){
		cout<<catalogue.size()<<endl;
	}else if(command == "ap" or command == "agregar_productos"){
		catalogue.read();		
	}else if(command == "ep" or command == "escribir_prodcucto"){
		int productId;
		cin>>productId;
		if(not catalogue.hasProduct(productId)){
			cout<<"Error: the product doesn't exist"<<endl;
		}else{
			catalogue.printProduct(productId);
		}
	}
};

