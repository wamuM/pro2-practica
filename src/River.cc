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

City River::get_city(const string& cityId) const{
	return _cities.find(cityId)->second;
}
void River::set_city(const string& cityId, const City& city){
	_cities[cityId] = city;
}

//util function, no need to explain it
int min(int a, int b){
	if(a < b)return a;
	else return b;
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
			int city2Surplus = inv2It->second.first - inv2It->second.second;

			if(city1Surplus > 0 and city2Surplus < 0){// 1 gives to 2
				int given = min(city1Surplus,-city2Surplus);
				_cities[cityId2].add_supply(productId, catalogue.get_product(productId),  given);
				_cities[cityId1].add_supply(productId, catalogue.get_product(productId), -given);
				
			}else if(city1Surplus < 0 and city2Surplus > 0){// 2 gives to 1
				int given = min(-city1Surplus,city2Surplus);
				_cities[cityId1].add_supply(productId, catalogue.get_product(productId),  given);
				_cities[cityId2].add_supply(productId, catalogue.get_product(productId), -given);
			}
			++inv1It;
			++inv2It;
		} else  if(inv1It->first < inv2It->first)++inv1It;
		  else/*if(inv1It->first > inv2It->first)*/++inv2It;
	}
}

void River::redistribute(const Catalogue& catalogue, const string& cityId){
	if(cityId == "#")return;

	string rightId = _cities[cityId].get_right();
	string leftId  = _cities[cityId].get_left();

	if(rightId != "#")trade(catalogue, cityId, rightId);
	if( leftId != "#")trade(catalogue, cityId, leftId);

	redistribute(catalogue, rightId);
	redistribute(catalogue, leftId);
}
void River::redistribute(const Catalogue& catalogue){
	redistribute(catalogue,_outlet);
}

River::Path River::_find_best_trip(Ship ship, const string& cityId){
	if(cityId == "#")return River::Path(stack<string>(),0);

	int citySupply =  get_city(cityId).get_surplus(ship.get_demand_id());
	int cityDemand = -get_city(cityId).get_surplus(ship.get_supply_id());

	int  buyAmount = 0;
	int sellAmount = 0;
	if(citySupply > 0)  buyAmount = min(ship.get_demand_amount(), citySupply); 
	if(cityDemand > 0) sellAmount = min(ship.get_supply_amount(), cityDemand);
	
	ship.buy(buyAmount);
	ship.sell(sellAmount);
	int totalTransaction = buyAmount + sellAmount; 

	if( (ship.get_demand_amount() + ship.get_supply_amount()) == 0){ //The ship can't trade anymore 
		stack<string> ls;
		ls.push(cityId);
		return River::Path(ls,totalTransaction);
	}

	River::Path leftPath  = _find_best_trip(ship, get_city(cityId).get_left());
	River::Path rightPath = _find_best_trip(ship, get_city(cityId).get_right());

	bool chooseLeft;
	if(leftPath.second == rightPath.second) chooseLeft = leftPath.first.size() < rightPath.first.size();
	else chooseLeft = leftPath.second > rightPath.second; 

	if(chooseLeft){
		if(totalTransaction != 0){ // If no transaction was done to the city no need to record it
			leftPath.first.push(cityId);
			leftPath.second += totalTransaction;
		}else leftPath.first.push("#");
		return leftPath;	
	} else {
		if(totalTransaction != 0){// if no transaction was done to the city no need to record it
			rightPath.first.push(cityId);
			rightPath.second += totalTransaction;
		}else rightPath.first.push("#");
		return rightPath;	
	}
}
int River::do_trip(Ship& ship, const Catalogue& catalogue){
	River::Path bestPath = _find_best_trip(ship, _outlet);

	string cityId = "";
	while(not bestPath.first.empty()){
		if(bestPath.first.top() != "#"){
			cityId = bestPath.first.top();	
	
			int citySupply =  get_city(cityId).get_surplus(ship.get_demand_id());
			int cityDemand = -get_city(cityId).get_surplus(ship.get_supply_id());

			int  buyAmount = 0;
			int sellAmount = 0;
			if(citySupply > 0)  buyAmount = min(ship.get_demand_amount(), citySupply);
			if(cityDemand > 0) sellAmount = min(ship.get_supply_amount(), cityDemand);

			//for some fucked up reason the ship doesn't get modified here
		
			_cities[cityId].add_supply(ship.get_demand_id(), catalogue.get_product(ship.get_demand_id()), -buyAmount);
			_cities[cityId].add_supply(ship.get_supply_id(), catalogue.get_product(ship.get_supply_id()), sellAmount);
		}
		bestPath.first.pop();
	}
	if(bestPath.second != 0)ship.log(cityId);
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
	if(not _cities.empty()) _cities.erase(_cities.begin(),_cities.end());
	_outlet = _recursive_reading();
}

