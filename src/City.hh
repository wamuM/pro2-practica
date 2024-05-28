/**
* @file City.hh
* @brief This file contains the headers of the City class, the Market type and the Inventory type.
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

	std::string _city_north;//!< @brief The city directly north of this one
	std::string _city_left;//!< @brief The city, looking south, at the left of this one
	std::string _city_right;//!< @brief The city, looking south, at the right of this one
	
	/**
	* @brief Reads the market (supply and demand) of a product from the std input
	*
	* @pre  The new supply and demand of \em product  are in the std input and \em productId is the id of \em product.
	* @post The supply and demand have been read and consumed from the std input and the city now has that supply and that demand of \em product. 
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
	 * @brief It returns the number of products the city has or wants
	 * 
	 * @pre True
	 * @post The number of products in the city has been returned 
	 *
	 * @cplx Constant.
	 */
	int inventory_size() const;

	/**
	 * @brief It clears the city of any product supply or demand
	 *
	 * @pre True
	 * @post The city now has no products and wants no products
	 *
	 * @cplx Linear in the number of products
	 */
	void clear_inventory();
	/**
	* @brief It sets the provided city at the left, looking south, of this one
	*
	* @pre \em cityId refers to a valid city or "#", to indicate that there is no city
	* @post The provided city is now at the left of this one
	*
	* @cplx Constant
	*/
	void set_left( const std::string& cityId);

	/**
	* @brief It sets the provided city at the right, looking south, of this one
	*
	* @pre \em cityId refers to a valid city or "#", to indicate that there is no city
	* @post The provided city is now at the right of this one
	*
	* @cplx Constant
	*/
	void set_right(const std::string& cityId);
	
	/**
	 * @brief It sets the provided city at the north of this one.
	 *
	 * @pre \em cityId refers to a valid city or "#", to indicate that there is no city
	 * @post The provided city is now directly north of this one
	 *
	 * @cplx Constant
	 */
	void set_north(const std::string& cityId);

	/**
	 * @brief It returns the city at the north of this one.
	 *
	 * @pre True
	 * @post If the city has a city directly north of itself its id is returned, "#" otherwise
	 *
	 * @cplx Constant
	 */
	std::string get_north() const;

	

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
	* @brief It checks if the city has or wants a product
	* 
	* @pre True
	* @post True has been returned if the city has or wants the specified product, false otherwise. 
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	bool has_product(int productId) const;

	/**
	* @brief it sets the supply and demand of a product
	*
	* @pre \em product is a valid product and \em productId its id and \em supply and \em demand the new supply and demand of that product in the city respectively.
	* @post The product supply and demand has been set 
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void set_product_market(int productId, const Product& product, int supply, int demand);

	/**
	* @brief Returns the supply of a product in the city
	*
	* @pre The city has or wants the \em productId product
	* @post The supply of that product has been returned
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_supply(int productId) const;

	/**
	 * @brief Adds\em amount to the number of \em productId products the city can supply.
	 * 
	 * @pre  \em product is a valid product and \em productId is its id
	 * @post The city now has \m amount more of product (or less if amount < 0).
	 *
	 * @cplx Constant
	 */
	void add_supply(int productId, const Product& product, int amount);

	/**
	* @brief Returns the demand of a product in the city
	*
	* @pre The city wants \em productId
	* @post The demand of the product has been returned
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	int get_demand(int productId) const;

	/**
	 * @brief Returns the amount of \em productId product the city doesn't want (supply - demand)
	 *
	 * @pre True
	 * @post If the city has the product, the amount of product the city diesn't want. 0 otherwise.
	 *
	 * @cplx Constant
	 */

	int get_surplus(int productId) const;
	/**
	* @brief Returns the market(supply and demand) of a product in the city
	*
	* @pre The city has or wants the product
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
	* @pre The city has or wants the product
	* @post The product has been removed from the city and there is no more demand for it
	*
	* @cplx Logarithmic in the number of products in the city
	*/
	void remove_product(int productId, const Product& product); 


	/**
	 * @brief Makes this city trade with another city
	 * @pre \em catalogue is the catalogue of both cities
	 * @post The two cities have traded
	 *
	 * @cplx Linear in the biggest number of different products in the two cities
	 */
	void trade(const Catalogue& catalogue, City& city);
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
	* @brief Prints the market(supply and demand) of product in the city into the std output
	*
	* @pre The city has or wants \em productId
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
	* @pre \em productCount is the number of products in the std input and \em catalogue is the catalogue of the city
	* @post If no errors happened the inventory has been consumed from the std input and added to the city and true is returned, otherwise false is returned and \em productCount has been modified to the number of products there are left. 
	*
	* @cplx Linear in the amount of products
	*/
	bool read_inventory(int& productCount, const Catalogue& catalogue);
};
