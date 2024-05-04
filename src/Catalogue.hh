/**
* @file Catalogue.hh
* @brief A file that has all the definitions of the Catalogue class and the Product type.
*/
#pragma once 

#include <vector>
#include <utility>

typedef std::pair<int,int> Product;//! @brief A type that abstacts products 

class Catalogue{
private:
	std::vector<Product> _products;
public:
	Catalogue();

	int size() const;

	bool has_product(int productId) const;

	int emplace_product(int weight, int volume);

	Product get_product(int productId) const;

	void print_product_amount(int productId);

	void read();
};

