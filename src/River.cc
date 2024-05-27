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


int River::min(int a, int b){
	if(a < b)return a;
	else return b;
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


pair<int,int> River::_calculate_transaction(Ship& ship, const string& cityId) const{
	int citySupply =  get_city(cityId).get_surplus(ship.get_demand_id());
	int cityDemand = -get_city(cityId).get_surplus(ship.get_supply_id());

	int  buyAmount = 0;
	int sellAmount = 0;
	if(citySupply > 0)  buyAmount = min(ship.get_demand_amount(), citySupply); 
	if(cityDemand > 0) sellAmount = min(ship.get_supply_amount(), cityDemand);
	
	ship.buy(buyAmount);
	ship.sell(sellAmount);
	return pair<int,int>(buyAmount,sellAmount); 
}

River::Path River::_find_best_path(Ship ship, const string& cityId){
	if(cityId == "#")return River::Path();
	if(ship.get_demand_amount() == 0 and ship.get_supply_amount() == 0)return River::Path();

	pair<int,int> transaction = _calculate_transaction(ship, cityId);
	int totalTransaction = transaction.first + transaction.second;

	River::Path  leftPath = _find_best_path(ship, get_city(cityId).get_left());
	River::Path rightPath = _find_best_path(ship, get_city(cityId).get_right());

	bool chooseLeft;
	if(leftPath.totalTransaction == rightPath.totalTransaction) 
	     chooseLeft = leftPath.length           < rightPath.length;
	else chooseLeft = leftPath.totalTransaction > rightPath.totalTransaction;

	if(chooseLeft){
		if(totalTransaction == 0){
			if(leftPath.totalTransaction == 0){
				return leftPath;
			}else{
				leftPath.length += 1;
				return leftPath;
			}	
		}else{
			leftPath.affectedCities.push(Ship::SignedTransaction(cityId,transaction));
			leftPath.totalTransaction += totalTransaction;
			leftPath.length += 1;
			return leftPath;
		}
	}else{
		if(totalTransaction == 0){
			if(rightPath.totalTransaction == 0){
				return rightPath;
			}else{
				rightPath.length += 1;
				return rightPath;
			}	
		}else{
			rightPath.affectedCities.push(Ship::SignedTransaction(cityId,transaction));
			rightPath.totalTransaction += totalTransaction;
			rightPath.length += 1;
			return rightPath;
		}
	}
}

int River::do_trip(Ship& ship, const Catalogue& catalogue){
	River::Path bestPath = _find_best_path(ship, _outlet);

	if(bestPath.totalTransaction == 0)return 0;//Do nothing if nothing could be done
	
	string cityId = "";
	while(not bestPath.affectedCities.empty()){
		cityId = bestPath.affectedCities.top().first;

		pair<int,int> transaction = bestPath.affectedCities.top().second;

		_cities[cityId].add_supply(ship.get_demand_id(), catalogue.get_product(ship.get_demand_id()), -transaction.first);
		_cities[cityId].add_supply(ship.get_supply_id(), catalogue.get_product(ship.get_supply_id()),  transaction.second);

		bestPath.affectedCities.pop();
	}

	ship.log(cityId); //last city
	
	return bestPath.totalTransaction;
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

bool River::apply_read_inventory(const std::string& cityId, int& productCount, const Catalogue& catalogue){
	return	_cities[cityId].read_inventory(productCount,catalogue);
}
void River::apply_set_product_market(const std::string& cityId, int productId, const Product& product, int supply, int demand){
	_cities[cityId].set_product_market(productId, product, supply, demand);
}
void River::apply_remove_product(const std::string& cityId, int productId, const Product& product){
	_cities[cityId].remove_product(productId, product);
}
