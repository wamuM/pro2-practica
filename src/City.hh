#pragma once

#include <string>
#include <utility>
#include <map>

#include "Catalogue.hh"

typedef std::pair<int,int> Amount;
typedef std::map<int,Amount> Inventory;

class City {
private:
	Inventory _inventory;

	Product _total_product;

	std::string _city_left;
	std::string _city_right;

public:
	City();
	
	void set_right(const std::string& cityId);
	void set_left( const std::string& cityId);

	bool has_product(int productId) const;

	void set_product_amount(int productId, const Product& product, int stock, int demand);

	int get_stock(int productId);
	int get_demand(int productId);

	Amount get_product_amount(int productId);

	Product get_total() const;

	void remove_product(int productId, const Product& product); 

	void print_city() const;
	void print_product_amount(int productId);
	void print_total() const;

	void read_product_amount(int productId, const Product& product);
};
