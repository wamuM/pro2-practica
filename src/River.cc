#include "River.hh"

#include <string>
#include <iostream>
using namespace std;

#include "City.hh"

River::River(){
	_outlet = "#";
}

bool River::has_city(const string& cityId) const{
	return _cities.count(cityId) == 1;
}

City River::get_city(const string& cityId){
	return _cities[cityId];
}

void River::trade(Ship& ship, const std::string& cityId1, const std::string& cityId2){
	if(cityId1 == cityId2)ship.get_stock_id();

}
void River::redistribute(Ship& ship){
	ship.get_stock_id();

}
void River::do_trip(Ship& ship){
	ship.get_stock_id();
}
string River::_recursive_reading(){
	string cityId;
	cin>>cityId;
	if(cityId == "#")return "#";
	_cities[cityId].set_right( _recursive_reading());
	_cities[cityId].set_left(  _recursive_reading());
	return cityId;
}
void River::read(){
	_outlet = _recursive_reading(); 
}

