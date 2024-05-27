#include "City.hh"

#include <string>
#include <iostream>
using namespace std;

#include "Catalogue.hh"

City::City(){
	_total_product = Product(0,0);

	_city_left  = "#";
	_city_right = "#";
}

int City::inventory_size() const{
	return _inventory.size();
}

void City::clear_inventory(){
	_inventory.erase(_inventory.begin(), _inventory.end());
	_total_product.first  = 0;
	_total_product.second = 0;
}

void City::set_right(const string& cityId){
	_city_right = cityId;	
}
void City::set_left( const string& cityId){
	_city_left = cityId;
}

string City::get_right() const{
	return _city_right;	
}
string City::get_left() const{
	return _city_left;
}

void City::set_product_market(int productId, const Product& product, int supply, int demand){
	if(has_product(productId))remove_product(productId, product);
	_inventory[productId] = Market(supply,demand);
	_total_product.first  += supply*product.first;
	_total_product.second += supply*product.second;

}

void City::add_supply(int productId, const Product& product, int amount){
	_inventory[productId].first += amount;
	_total_product.first  += amount*product.first;
	_total_product.second += amount*product.second;
}
int City::get_supply(int productId) const{
	return get_product_market(productId).first;
}
int City::get_demand(int productId) const{
	return get_product_market(productId).second;
}
int City::get_surplus(int productId) const{
	if(has_product(productId))return get_supply(productId) - get_demand(productId);
	else return 0;
}

bool City::has_product(int productId) const{
	return _inventory.count(productId) == 1;
}

Market City::get_product_market(int productId) const{
	return _inventory.find(productId)->second;
}
Product City::get_total() const{
	return _total_product;
}

Inventory::iterator City::inventory_begin(){
	return _inventory.begin();
}
Inventory::iterator City::inventory_end(){
	return _inventory.end();
}

void City::remove_product(int productId, const Product& product){
	auto iterator = _inventory.find(productId);
	_total_product.first  -= iterator->second.first*product.first;
	_total_product.second -= iterator->second.first*product.second;
	_inventory.erase(iterator);
}

void City::print_inventory() const{
	for(auto it = _inventory.begin(); it != _inventory.end(); ++it){
		Market market = it->second;
		if(market.second != 0)
			cout<<    it->first <<' '
			    << market.first <<' '
			    << market.second<<endl;
	}
}
void City::print_product_market(int productId) const{
	Market market = get_product_market(productId);
	cout<< market.first  <<' '
	    << market.second <<endl;          
}

void City::print_total() const{
	cout<< _total_product.first  <<' '
	    << _total_product.second <<endl;
}
void City::print() const{
	print_inventory();
	print_total();
}
void City::_read_product_market(int productId, const Product& product){
	int supply, demand;
	cin>>supply>>demand;
	set_product_market(productId, product, supply, demand);
}

bool City::read_inventory(int& productCount, const Catalogue& catalogue){
	if(inventory_size() != 0)clear_inventory();
	while(productCount--){
		int productId;
		cin>>productId;
		if(not catalogue.has_product(productId))return false;
		_read_product_market(productId,catalogue.get_product(productId));
	}
	return true;
}
