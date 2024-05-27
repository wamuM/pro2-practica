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
	if(_inventory[productId].second != 0){
		_total_product.first  -= _inventory[productId].first * product.first;
		_total_product.second -= _inventory[productId].first * product.second;
	}
	_inventory[productId].first  = supply;
	_inventory[productId].second = demand;
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

void City::remove_product(int productId, const Product& product){
	auto iterator = _inventory.find(productId);
	_total_product.first  -= iterator->second.first*product.first;
	_total_product.second -= iterator->second.first*product.second;
	_inventory.erase(iterator);
}

int City::min(int a, int b){
	if(a < b)return a;
	else return b;
}
void City::trade(const Catalogue& catalogue, City& city){
	auto inv1It = this->_inventory.begin();	
	auto inv2It =  city._inventory.begin();	

	const auto inv1ItEnd = this->_inventory.end();	
	const auto inv2ItEnd =  city._inventory.end();	

	while(inv1It != inv1ItEnd and inv2It != inv2ItEnd){
		if(inv1It->first == inv2It->first){
			int productId = inv1It->first;
			int thisSurplus = inv1It->second.first - inv1It->second.second; 
			int citySurplus = inv2It->second.first - inv2It->second.second;

			if(thisSurplus > 0 and citySurplus < 0){// 1 gives to 2
				int given = City::min(thisSurplus,-citySurplus);
				inv2It->second.first += given;
				inv1It->second.first -= given;
				 city._total_product.first  += given*catalogue.get_product(productId).first;
				this->_total_product.first  -= given*catalogue.get_product(productId).first;
				 city._total_product.second += given*catalogue.get_product(productId).second;
				this->_total_product.second -= given*catalogue.get_product(productId).second;
				
			}else if(thisSurplus < 0 and citySurplus > 0){// 2 gives to 1
				int given = City::min(-thisSurplus,citySurplus);
				inv1It->second.first += given;
				inv2It->second.first -= given;
				this->_total_product.first  += given*catalogue.get_product(productId).first;
				 city._total_product.first  -= given*catalogue.get_product(productId).first;
				this->_total_product.second += given*catalogue.get_product(productId).second;
				 city._total_product.second -= given*catalogue.get_product(productId).second;
				
			}
			++inv1It;
			++inv2It;
		} else  if(inv1It->first < inv2It->first)++inv1It;
		  else/*if(inv1It->first > inv2It->first)*/++inv2It;
	}


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
