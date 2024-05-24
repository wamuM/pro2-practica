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
	remove_product(productId, product);
	_inventory[productId] = Market(supply,demand);
	_total_product.first  += supply*product.first;
	_total_product.second += supply*product.second;

}

void City::add_supply(int productId, const Product& product, int amount){
	_inventory[productId].first += amount;
	_total_product.first  += amount*product.first;
	_total_product.second += amount*product.second;
}
int City::get_supply(int productId){
	return _inventory[productId].first;
}
int City::get_demand(int productId){
	return _inventory[productId].second;
}
int City::get_surplus(int productId){
	return get_supply(productId) - get_demand(productId);
}

bool City::has_product(int productId) const{
	return _inventory.count(productId) == 1;
}

market City::get_product_market(int productId){
	return _inventory[productId];
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
	_total_product.first  -= get_supply(productId)*product.first;
	_total_product.second -= get_supply(productId)*product.second;
	_inventory[productId] = market(0,0);

}

void City::print_city() const{
	for(auto it = _inventory.begin(); it != _inventory.end(); ++it){
		Market market = it->second;
		if(market.second != 0)
			cout<<    it->first <<' '
			    << market.first <<' '
			    << market.second<<endl;
	}
}
void City::print_product_market(int productId){
	Market market = get_product_market(productId);
	cout<< market.first  <<' '
	    << market.second <<endl;          
}

void City::print_total() const{
	cout<< _total_product.first  <<' '
	    << _total_product.second <<endl;
}
void City::_read_product_market(int productId, const Product& product){
	int supply, demand;
	cin>>supply>>demand;
	set_product_market(productId, product, supply, demand);
}

bool City::read_inventory(const Catalogue& catalogue){
	while(productmarket--){
		int productId;
		cin>>productId;
		if(not catalogue.has_product(productId))return false;
		city.read_product_market(productId,catalogue.get_product(productId));
	}
	return true;
}
