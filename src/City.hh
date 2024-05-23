/**
* @file City.hh
* This file contains the definitions of the City class, the Amount type and the Inventory type.
*/
#pragma once

#include <string>
#include <utility>
#include <map>

#include "Catalogue.hh"

typedef std::pair<int,int> Market;//!< @brief A type that describes the amount of supply and demand of something
typedef std::map<int,Market> Inventory;//!< @brief A type that links an product id to an Amount

/**
* @brief A class that represents a city
*/
class City {
private:
	Inventory _inventory;//!< @brief Where the products the city has and wants are contained

	Product _total_product;//!< @brief The total weight and volume of products within the city

	std::string _city_left;//!< @brief The city, looking south, at the left of this one
	std::string _city_right;//!< @brief The city, looking south, at the right of this one
	/**
	* @brief Reads the amount (supply and demand) of a product from the std input
	*
	* @pre True
	* @param productId The id of the product
	* @param product The product object
	* 
	* @post The supply and demand have been read and consumed from the std input and are now in the city
	*
	* @cplx Logarithmic in the number of products in the city 
	*/
	void _read_product_market(int productId, const Product& product);

public:
	/**
	* @brief The default constructor of the City class
	*/
	City();

	/**
	* @brief It sets the provided city at the left, looking south, of this one
	*
	* @pre cityId refers to a valid city
	* @param cityId The id of the city at the left
	*
	* @post The provided city is now at the left of this one
	*
	* @cplx Constant
	*/
	void set_left( const std::string& cityId);

	/**
	* @brief It sets the provided city at the right, looking south, of this one
	*
	* @pre True
	* @param cityId The id of the city at the right 
	* @post The provided city is now at the right of this one
	*
	* @cplx Constant
	*/
	void set_right(const std::string& cityId);

	/**
	* @brief It checks if the city has a product
	* 
	* @pre True
	* @param productId The id of the product 
	* 
	* @return True if the city has the specified product, false otherwise. 
	* @post True
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	bool has_product(int productId) const;

	/**
	* @brief it sets the supply and demand of a product
	*
	* @pre True
	* @param productId The id of the product
	* @param product The product object 
	* @param supply The new supply of that product in the city
	* @param demand The new demand of that product in the city
	*
	* @post The product supply and demand has been set 
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void set_product_market(int productId, const Product& product, int supply, int demand);

	/**
	* @brief Returns the supply of a product in the city
	*
	* @pre True
	* @param productId The id of the product  
	*
	* @return The supply of product in the city
	* @post True
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_supply(int productId);

	/**
	* @brief Returns the demand of a product in the city
	*
	* @pre True
	* @param productId The id of the product  
	*
	* @return The demand of product in the city
	* @post True
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_demand(int productId);

	/**
	* @brief Returns the market(supply and demand) of a product in the city
	*
	* @pre True
	* @param productId The id of the product  
	*
	* @return The amount of product in the city
	* @post True
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	Amount get_product_market(int productId);

	/**
	* @brief Returns the total weight and volume of products in the city
	*
	* @pre True
	*
	* @return The total weight and volume of products in the city
	* @post True
	*
	* @cplx Constant 
	*/
	Product get_total() const;

	/**
	* @brief Removes a product from the city (more efficient than set_product_amount(productId,product,0,0) )
	* @pre True
	* @param productId The id of the product
	* @param product The product object
	*
	* @post The product has been removed from the city and there is no more demand for it
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void remove_product(int productId, const Product& product); 

	/**
	* @brief Prints the city into the std output
	*
	* @pre True
	*
	* @post The city has been printed into the std output
	*
	* @cplx Linear in the number of products in the city
	*/
	void print_city() const;

	/**
	* @brief Prints the amount(supply and demand) of product in the city into the std output
	*
	* @pre True
	*
	* @post The amount of product and its demand in the city has been printed into the std output
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void print_inventory(int productId);

	/**
	* @brief Prints the total weight and volume of products in the city into the std output
	*
	* @pre True
	*
	* @post The total weight and volume of products in the city has been printed into the std output
	*
	* @cplx Constant 
	*/
	void print_total() const;

	void print() const;

	bool read_inventory(const Catalogue& catalogue);
};
