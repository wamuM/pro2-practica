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
	return _cities.at(cityId);
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


pair<int,int> River::_calculate_transaction(int& buyAmount, int& sellAmount, int buyId, int sellId, const string& cityId) const{
	int citySupply =  get_city(cityId).get_surplus( buyId);
	int cityDemand = -get_city(cityId).get_surplus(sellId);

	int  toBuy = 0;
	int toSell = 0;
	if(citySupply > 0)  toBuy = min( buyAmount, citySupply); 
	if(cityDemand > 0) toSell = min(sellAmount, cityDemand);

	 buyAmount -= toBuy;
	sellAmount -= toSell;
	return pair<int,int>(toBuy,toSell); 
}

River::Path River::_find_best_path(int buyAmount, int sellAmount, int buyId, int sellId, const string& cityId){
	if(cityId == "#")return River::Path();
	if(buyAmount == 0 and sellAmount == 0)return River::Path();

	pair<int,int> transaction = _calculate_transaction(buyAmount, sellAmount, buyId, sellId, cityId);
	int transactionSum = transaction.first + transaction.second;

	River::Path  leftPath = _find_best_path(buyAmount, sellAmount, buyId, sellId, get_city(cityId).get_left());
	River::Path rightPath = _find_best_path(buyAmount, sellAmount, buyId, sellId,get_city(cityId).get_right());

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
	int  buyAmount = ship.get_demand_amount();
	int sellAmount = ship.get_supply_amount();
	int  buyId = ship.get_demand_id();
	int sellId = ship.get_supply_id();
	River::Path bestPath = _find_best_path(buyAmount, sellAmount, buyId, sellId, _outlet);

	if(bestPath.totalTransaction == 0)return 0;//Do nothing if nothing could be done
	
	_travel_path(buyAmount, sellAmount, buyId, sellId, catalogue, bestPath.finalCity);

	ship.log(bestPath.finalCity); //last city
	
	return bestPath.totalTransaction;
}
void River::_travel_path(int& buyAmount, int& sellAmount, int buyId, int sellId, const Catalogue& catalogue, const string& cityId){
	if(cityId == "#")return;
	else _travel_path(buyAmount, sellAmount, buyId, sellId, catalogue, get_city(cityId).get_root());

	pair<int,int> transaction = _calculate_transaction(buyAmount, sellAmount, buyId, sellId, cityId);
	//There are more efficient ways of doing this, by storing the _calculate_transaction from before in a return value for instance. But it took me way too long to optimize the rest and now I've ran out of time. 

	if(transaction.first == 0 and transaction.second == 0)return;//This could also be avoided if instead of returning the finalCity _find_best_path returns a list/stack of the best path, but again, ran out of time.
	_cities[cityId].add_supply( buyId, catalogue.get_product( buyId), -transaction.first);
	_cities[cityId].add_supply(sellId, catalogue.get_product(sellId),  transaction.second);

}

string River::_recursive_reading(string root){
	string cityId;
	cin>>cityId;
	if(cityId == "#")return "#";
	_cities[cityId].set_right( _recursive_reading(cityId));
	_cities[cityId].set_left(  _recursive_reading(cityId));
	_cities[cityId].set_root(root);
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
