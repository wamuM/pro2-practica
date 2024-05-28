/**
* @file River.cc
* @brief This file contains all the code of the River class
*/
#include "River.hh"

#include <string>
#include <iostream>
using namespace std;

#include "City.hh"
#include "useful.hh"

River::River(){
	_outlet = "#";
}

bool River::has_city(const string& cityId) const{
	return _cities.count(cityId) == 1;
}

City River::get_city(const string& cityId) const{
	return _cities.at(cityId);
}
void River::set_city(const string& cityId, const City& city){
	_cities[cityId] = city;
}

void River::trade(const Catalogue& catalogue, City& city1, City& city2){
	city1.trade(catalogue,city2);
}

void River::trade(const Catalogue& catalogue, const string& cityId1, const string& cityId2){
	trade(catalogue, _cities[cityId1], _cities[cityId2]);
};
void River::redistribute(const Catalogue& catalogue, const string& cityId){
	if(cityId == "#")return;

	string rightId = _cities[cityId].get_right();
	string leftId  = _cities[cityId].get_left();

	if(rightId != "#")trade(catalogue, _cities[cityId], _cities[rightId]);
	if( leftId != "#")trade(catalogue, _cities[cityId], _cities[leftId]);

	redistribute(catalogue, rightId);
	redistribute(catalogue, leftId);
}
void River::redistribute(const Catalogue& catalogue){
	redistribute(catalogue,_outlet);
}


int River::_transaction(Ship& ship, const Catalogue& catalogue, const string& cityId, bool modifyCity, bool modifyShip){
	int citySupply =  get_city(cityId).get_surplus(ship.get_demand_id());
	int cityDemand = -get_city(cityId).get_surplus(ship.get_supply_id());

	int  buyAmount = 0;
	int sellAmount = 0;
	if(citySupply > 0)  buyAmount = min(ship.get_demand_amount(), citySupply); 
	if(cityDemand > 0) sellAmount = min(ship.get_supply_amount(), cityDemand);

	int transaction = buyAmount + sellAmount;
	if(modifyCity and transaction != 0){
		_cities[cityId].add_supply(ship.get_demand_id(), catalogue.get_product(ship.get_demand_id()), -buyAmount);
		_cities[cityId].add_supply(ship.get_supply_id(), catalogue.get_product(ship.get_supply_id()), sellAmount);
	}
	if(modifyShip){
		ship.buy(buyAmount);
		ship.sell(sellAmount);
	}
	return transaction; 
}

River::Path River::_find_best_path(Ship ship, const Catalogue& catalogue, const string& cityId){
	if(cityId == "#")return River::Path();
	if(ship.get_supply_amount() == 0 and ship.get_demand_amount() == 0)return River::Path();

	int transactionSum = _transaction(ship, catalogue, cityId, false, true);

	River::Path  leftPath = _find_best_path(ship, catalogue, get_city(cityId).get_left());
	River::Path rightPath = _find_best_path(ship, catalogue, get_city(cityId).get_right());

	bool chooseLeft;
	if(leftPath.totalTransaction == rightPath.totalTransaction) 
	     chooseLeft = leftPath.length           < rightPath.length;
	else chooseLeft = leftPath.totalTransaction > rightPath.totalTransaction;

	if(chooseLeft){
		if(transactionSum == 0){//This city does nothing
			if(leftPath.totalTransaction == 0){//This city does nothing and neither
				//does this branch
				return River::Path();
			}else{
				leftPath.length += 1;
				return leftPath;
			}	
		}else{//This city does something
			if(leftPath.totalTransaction == 0){//It's the first one to do so
				River::Path path;
				path.totalTransaction = transactionSum;
				path.finalCity = cityId;
				path.length = 1;
				return path;
			}
			leftPath.totalTransaction += transactionSum; 
			leftPath.length += 1;
			return leftPath;
		}
	}else{
		if(transactionSum == 0){//This city does nothing
			if(rightPath.totalTransaction == 0){//This city does nothing and neither
				//does this branch
				return River::Path();
			}else{
				rightPath.length += 1;
				return rightPath;
			}	
		}else{//This city does something
			if(rightPath.totalTransaction == 0){//It's the first one to do so
				River::Path path;
				path.totalTransaction = transactionSum;
				path.finalCity = cityId;
				path.length = 1;
				return path;
			}
			rightPath.totalTransaction += transactionSum; 
			rightPath.length += 1;
			return rightPath;
		}
	}
}

int River::do_trip(Ship& ship, const Catalogue& catalogue){
	Ship explorerShip = Ship(ship);
	
	River::Path bestPath = _find_best_path(explorerShip, catalogue, _outlet);

	if(bestPath.totalTransaction == 0)return 0;//Do nothing if nothing could be done
	
	_travel_path(explorerShip, catalogue, bestPath.finalCity);

	ship.log(bestPath.finalCity); //last city
	
	return bestPath.totalTransaction;
}
void River::_travel_path(Ship& ship, const Catalogue& catalogue, const string& cityId){
	if(cityId == "#")return;
	
	_travel_path(ship, catalogue, get_city(cityId).get_north());

	_transaction(ship, catalogue, cityId, true, true);
}

string River::_recursive_reading(string root){
	string cityId;
	cin>>cityId;
	if(cityId == "#")return "#";
	_cities[cityId].set_right( _recursive_reading(cityId));
	_cities[cityId].set_left(  _recursive_reading(cityId));
	_cities[cityId].set_north(root);
	return cityId;
}
void River::read(){
	if(not _cities.empty()) _cities.clear();
	_outlet = _recursive_reading("#");
}

bool River::apply_read_inventory(const std::string& cityId, int& productCount, const Catalogue& catalogue){
	return	_cities[cityId].read_inventory(productCount,catalogue);
}
void River::apply_set_product_market(const std::string& cityId, int productId, const Product& product, int supply, int demand){
	_cities[cityId].set_product_market(productId, product, supply, demand);
}
void River::apply_remove_product(const std::string& cityId, int productId, const Product& product){
	_cities[cityId].remove_product(productId, product);
}
