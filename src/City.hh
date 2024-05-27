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
	* @pre productId and product are valid products
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
	 * @brief It returns the number of products the city has
	 * 
	 * @pre True
	 * @post The number of products in the city has been returned 
	 *
	 * @cplx Constant.
	 */
	int inventory_size() const;

	/**
	 * @brief It clears the city of any product
	 *
	 * @pre True
	 * @post The city now has no products
	 *
	 * @cplx Linear in the number of products
	 */
	void clear_inventory();
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
	 * @brief Returns the city at the top left of this one, looking south.
	 *
	 * @pre True
	 * @post if the city has a top left city, its id is returned, "#" otherwise
	 *
	 * @cplx Constant
	 */
	std::string get_left() const;
	/**
	 * @brief Returns the city at the top right of this one, looking south.
	 *
	 * @pre True
	 * @post if the city has a top right city, its id is returned, "#" otherwise
	 *
	 * @cplx Constant
	 */
	std::string get_right() const;

	/**
	* @brief It checks if the city has a product
	* 
	* @pre True
	* @post True has been returned if the city has the specified product, false otherwise. 
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
	* @pre The city has that product
	* @post The supply of that product has been returned
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_supply(int productId) const;

	/**
	 * @brief Adds amount to the number of productId products the city can supply.
	 * 
	 * @pre product is a valid product and productId is its id
	 * @post The city now has amount more(or less if <0) product
	 *
	 * @cplx Constant
	 */
	void add_supply(int productId, const Product& product, int amount);

	/**
	* @brief Returns the demand of a product in the city
	*
	* @pre The city has that product
	* @post The demand of the product has been returned
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_demand(int productId) const;

	/**
	 * @brief Returns the amount of product the city doesn't want (supply - demand)
	 *
	 * @pre True
	 * @post If the city has the product, the amount of product the city wants. 0 otherwise
	 *
	 * @cplx Constant
	 */

	int get_surplus(int productId) const;
	/**
	* @brief Returns the market(supply and demand) of a product in the city
	*
	* @pre The city has the product
	* @post The market of the city has been returned
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	Market get_product_market(int productId) const;

	/**
	* @brief Returns the total weight and volume of products in the city
	*
	* @pre True
	* @post The total weight and volume of products in the city have been returned
	*
	* @cplx Constant 
	*/
	Product get_total() const;

	/**
	* @brief Removes a product from the city (more efficient than set_product_amount(productId,product,0,0) )
	*
	* @pre The city has the product
	* @post The product has been removed from the city and there is no more demand for it
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void remove_product(int productId, const Product& product); 

	/**
	 * @brief Returns an iterator to the begining of the inventory (collection of products) of the city (points to the first element of the collection)
	 * @pre True
	 * @post the begining iterator has been returned
	 */
	Inventory::iterator inventory_begin();

	/**
	 * @brief Returns an iterator to the end of the inventory (collection of products) of the city (points to outside the collection)
	 * @pre True
	 * @post the end iterator has been returned
	 */
	Inventory::iterator inventory_end();

	/**
	* @brief Prints the inventory of the city into the std output
	*
	* @pre True
	*
	* @post The inventory of the city has been printed into the std output
	*
	* @cplx Linear in the number of products in the city
	*/
	void print_inventory() const;

	/**
	* @brief Prints the amount(supply and demand) of product in the city into the std output
	*
	* @pre The city has productId
	*
	* @post The amount of product and its demand in the city has been printed into the std output
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void print_product_market(int productId)const;

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

	/**
	* @brief Prints the city into the std output
	*
	* @pre True
	*
	* @post The city has been printed into the std output
	*
	* @cplx Linear in the number of products in the city
	*/
	void print() const;

	/**
	* @brief Reads an inventory from the std input and adds it to the city
	*
	* @pre productCount is the number of products in the std input
	* @post If no errors happened the inventory has been consumed from the std input and added to the city and true is returned, otherwise false is returned and productCount is the number of products there are left. 
	*
	* @cplx Linear in the amount of products
	*/
	bool read_inventory(int& productCount, const Catalogue& catalogue);
};
