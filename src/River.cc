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

void River::trade(const Catalogue& catalogue, const string& cityId1, const string& cityId2){
	auto inv1It = _cities[cityId1].inventory_begin();	
	auto inv2It = _cities[cityId2].inventory_begin();	

	const auto inv1ItEnd = _cities[cityId1].inventory_end();	
	const auto inv2ItEnd = _cities[cityId2].inventory_end();	

	while(inv1It != inv1ItEnd and inv2It != inv2ItEnd){
		if(inv1It->first == inv2It->first){
			int productId = inv1It->first;
			int city1Surplus = inv1It->second.first - inv1It->second.second; 
			int city2Surplus = inv2It->second.first - inv1It->second.second;

			if(city1Surplus > 0 and city2Surplus < 0){// 1 gives to 2
				_cities[cityId2].add_supply(productId, catalogue.get_product(productId), city1Surplus);
			}else if(city1Surplus < 0 and city2Surplus > 0){// 2 gives to 1
				_cities[cityId1].add_supply(productId, catalogue.get_product(productId), city2Surplus);
			}
			++inv1It;
			++inv2It;
		} else if(inv1It->first < inv2It->first)++inv1It;
		  else if(inv1It->first > inv2It->first)++inv2It;
	}
}
void Rivver::redistribute(const Catalogue& catalogue, const string& cityId){
	if(cityId == '#')return;

	string rightId = _cities[cityId].get_right();
	string leftId  = _cities[cityId].get_left();

	if(rightId != '#')trade(catalogue, cityId, rightId);
	if( leftId != '#')trade(catalogue, cityId, leftId);

	redistribute(catalogue, rightId);
	redistribute(catalogue, leftId);
}
void River::redistribute(const Catalogue& catalogue){
	redistribute(catalogue,_outlet);
}
void River::do_trip(Ship& ship, const Catalogue& catalogue){
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

