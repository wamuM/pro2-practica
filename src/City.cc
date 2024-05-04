#include "City.hh"

#include <string>
using namespace std;

#include "Inventory.hh"

City::City(){
	this->_stock = Inventory();
	this->_offer = Inventory();
}
City::set_stock(); 
