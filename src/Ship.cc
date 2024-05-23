#include "Ship.hh"

#include <string>
#include <list>
#include <iostream>

using namespace std;

Ship::Ship(){
	_stock_amount = 0;
	_stock_id = 0;

	_demand_amount = 0;
	_demand_id = 0;

	_log = list<string>();
}

int Ship::get_stock_id() const{
	return _stock_id;
}
int Ship::get_demand_id() const{
	return _demand_id;
}
int Ship::get_stock_amount() const{
	return _stock_amount;
}
int Ship::get_demand_amount() const{
	return _demand_amount;
}

list<string> Ship::get_log() const{
	return _log;
}

void Ship::clear_log(){
	if(_log.begin() != _log.end())_log.erase(_log.begin(),_log.end());
}

void Ship:print() const{
	_print_market();
	_print_log();
}
