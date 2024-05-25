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
void River::redistribute(const Catalogue& catalogue, const string& cityId){
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
River::Path River::_find_best_trip(const Ship ship, const string&_cityId){
	if(cityId == '#')return River::Path(list(),0);

	int citySupply = _cities[cityId].get_surplus(ship.get_demand_id());
	int cityDemand = _cities[cityId].get_surplus(ship.get_supply_id());

	int  buyAmount = 0;
	int sellAmount = 0;
	if(citySupply > 0)  buyAmount = ship.get_demand_amount() > citySupply ? citySupply : ship.get_demand_amount();
	if(cityDemand > 0) sellAmount = ship.get_supply_amount() > cityDemand ? cityDemand : ship.get_supply_amount();
	
	ship.buy(buyAmount);
	ship.sell(sellAmount);
	int totalTransaction = buyAmount + sellAmount; 

	River::Path leftPath  = _find_best_trip(ship, _cities[cityId].get_left())
	River::Path rightPath = _find_best_trip(ship, _cities[cityId].get_right())

	bool chooseLeft = false;
	if(leftPath.second == rightPath.second) chooseLeft = leftPath.first.size() < leftPath.first.size();
	else chooseLeft = leftPath.second > rightPath.second; 

	if(chooseLeft){
		leftPath.first.push_front(cityId);
		leftPath.second += totalTransaction;
		return leftPath;	
	} else {
		rightPath.first.push_front(cityId);
		rightPath.second += totalTransaction;
		return rightPath;	
	}
}
int River::do_trip(Ship& ship, const Catalogue& catalogue){
	River::Path bestPath = _find_best_trip(ship, _outlet);

	for(auto it = bestPath.first.begin(); it != bestPath.first.end(); ++it){
		int citySupply = _cities[it*].get_surplus(ship.get_demand_id());
		int cityDemand = _cities[it*].get_surplus(ship.get_supply_id());

		int  buyAmount = 0;
		int sellAmount = 0;
		if(citySupply > 0)  buyAmount = ship.get_demand_amount() > citySupply ? citySupply : ship.get_demand_amount();
		if(cityDemand > 0) sellAmount = ship.get_supply_amount() > cityDemand ? cityDemand : ship.get_supply_amount();

		ship.buy(buyAmount);
		ship.sell(sellAmount);
		
		_cities[it*].add_supply(ship.get_demand_id(), catalogue.get_product(ship.get_demand_id()), -buyAmount);
		_cities[it*].add_supply(ship.get_supply_id(), catalogue.get_product(ship.get_supply_id()), sellAmount);
	}
	return bestPath.second; 
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

