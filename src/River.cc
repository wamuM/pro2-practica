#include "River.hh"

#include <string>
using namespace std;

#include "City.hh"

River::River(){
	this->_outlet = "#";
}

bool River::has_city(const string& cityId){
	return this->_cities.count(cityId) == 1;
}

City River::get_city(const string& cityId){
	return this->_cities[cityId];
}

void River::trade(Ship& ship, const std::string& cityId1, const std::string& cityId2){
	
}
void River::redistribute(Ship& ship){

}
void River::do_trip(Ship& ship){

}
void River::_emplace_city(const string& cityId, const string& cityLeftId, const string& cityRightId){
	this->_cities[cityId] = City(cityLeftId,cityRightId);
}
string River::_recursive_reading(){
	string cityId;
	cin>>cityId;
	if(cityId == "#")return "#";
	this->_cities[cityId].set_right( this->_recursive_reading());
	this->_cities[cityId].set_left(  this->_recursive_reading());
}
void River::read(){
	this->_outlet = this->_recursive_reading(); 
}

