/**
* @file Ship.cc
* @brief This file contains all the code of the Ship class
*/
#include "Ship.hh"

#include <string>
#include <list>
#include <iostream>

using namespace std;

Ship::Ship(){
	_supply_amount = 0;
	_supply_id = 0;

	_demand_amount = 0;
	_demand_id = 0;

	_log = list<string>();
}

Ship::Ship(const Ship& ship){
	this->_supply_amount = ship._supply_amount;
	this->_supply_id     = ship._supply_id;

	this->_demand_amount = ship._demand_amount;
	this->_demand_id     = ship._demand_id;

	_log = list<string>();
}

int Ship::get_supply_id() const{
	return _supply_id;
}
int Ship::get_demand_id() const{
	return _demand_id;
}
int Ship::get_supply_amount() const{
	return _supply_amount;
}
int Ship::get_demand_amount() const{
	return _demand_amount;
}

void Ship::set_supply(int productId, int amount){
	_supply_amount = amount;
	_supply_id = productId;
}
void Ship::set_demand(int productId, int amount){
	_demand_amount = amount;
	_demand_id = productId;
}
void Ship::sell(int amount){
	_supply_amount -= amount;
}
void Ship::buy(int amount){
	_demand_amount -= amount; 
}

void Ship::log(const string& cityId){
	_log.push_back(cityId);
}
list<string> Ship::get_log() const{
	return _log;
}

void Ship::clear_log(){
	if(_log.begin() != _log.end())_log.erase(_log.begin(),_log.end());
}
void Ship::_print_market() const{
	cout<< _demand_id << ' ' << _demand_amount << ' ' 
	    << _supply_id << ' ' << _supply_amount << endl;
}
void Ship::_print_log() const{
	for(auto it = _log.begin(); it != _log.end(); ++it)
		cout<<*it<<endl;

}
void Ship::print() const{
	_print_market();
	_print_log();
}

void Ship::read() {
	cin>>_demand_id>>_demand_amount
	   >>_supply_id>>_supply_amount;
}
