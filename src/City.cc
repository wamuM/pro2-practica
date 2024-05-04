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

void City::set_product_amount(int productId, const Product& product, int stock, int demand){
	remove_product(productId, product);
	_inventory[productId] = Amount(stock,demand);
	_total_product.first  += stock*product.first;
	_total_product.second += stock*product.second;

}

int City::get_stock(int productId){
	return _inventory[productId].first;
}
int City::get_demand(int productId){
	return _inventory[productId].second;
}

bool City::has_product(int productId) const{
	return _inventory.count(productId) == 1;
}

Amount City::get_product_amount(int productId){
	return _inventory[productId];
}
Product City::get_total() const{
	return _total_product;
}

void City::remove_product(int productId, const Product& product){
	_total_product.first  -= get_stock(productId)*product.first;
	_total_product.second -= get_stock(productId)*product.second;
	_inventory[productId] = Amount(0,0);

}

void City::print_city() const{
	for(auto it = _inventory.begin(); it != _inventory.end(); ++it){
		Amount amount = it->second;
		cout<<    it->first <<' '
		    << amount.first <<' '
		    << amount.second<<endl;
	}
}
void City::print_product_amount(int productId){
	Amount amount = get_product_amount(productId);
	cout<< amount.first  <<' '
	    << amount.second <<endl;          
}

void City::print_total() const{
	cout<< _total_product.first  <<' '
	    << _total_product.second <<endl;
}
void City::read_product_amount(int productId, const Product& product){
	int stock, demand;
	cin>>stock>>demand;
	set_product_amount(productId, product, stock, demand);
}
