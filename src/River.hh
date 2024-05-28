/**
 * @file River.hh
 * @brief This file conains the headers of River class and the River::Path struct.
 */
#pragma once

#include <map>
#include <string>
#include <stack>
#include <utility>

#include "City.hh"
#include "Ship.hh"

/**
 * @brief A class that represents the River Basin
 */
class River{
private:
	/**
	 * @brief A struct that represents a path into the river and its associated value
	 * The path goes from the \em _outlet to the \em finalCity
	 *
	 * Since the River Basin is organized as a binary tree, by definition for any two cities there is only one path between them. 
	 */
	struct Path {
		int totalTransaction = 0;//!< The total amount of products exchanged in transactions on the path 
		int length = 0;//!< The number of cities on the path
		std::string finalCity;//!< The final city this path goes to
	};

	std::map<std::string,City> _cities;//!< @brief A map that links a city id to its city.
	std::string _outlet;//!< @brief The id of the city that is at the river's outlet
	
	/**
	 * @brief Recursively reads cities from the std input
	 *
	 * @pre There are cities properly described in the std input
	 * @post The cities have been, preserving the structure, added to the river
	 *
	 * @cplx Linear in the number of cities to read
	 */
	std::string _recursive_reading(std::string cityId);

	/**
	 * @brief The ship travels until \em cityId is reached, selling and buying the maximum amount of products it can at each city. 
	 * @pre \em catalogue is the catalogue of the river and the ship
	 * @post The path has been travelled and the cities and the ship have been updated accordingly
	 */
	void _travel_path(Ship& ship, const Catalogue& catalogue, const std::string& cityId);

	/**
	 * @brief Makes all the cities from cityId southwards trade.
	 *
	 * @pre cityId is a valid city
	 * @post All the cities from cityId southwards have traded
	 *
	 * @cplx n·m where n is the number of cities and m the number of products in the catalogue
	 */
	void redistribute(const Catalogue& catalogue, const std::string& cityId);

	/**
	 * @brief Calculates the best possible transaction between a ship and a city of the river
	 *
	 * @pre \em cityId is a city of the river and \em catalogue the catalogue of both the \em ship and the city
	 * @post \em ship has done the transaction and the amount bought by the ship and the amount sold by the ship are returned in that order \n(if \em modifyCity was set to false the city was not modified, likewise if \em modifyShip was set to false the ship was not modified)
	 *
	 * @cplx Constant
	 */
	int _transaction(Ship& ship, const Catalogue& catalogue, const std::string& cityId, bool modifyCity, bool modifyShip);

	/**
	 * @brief Finds the best Path for the ship to commerce starting at \em cityId
	 *
	 * @pre \em cityId is a valid city
	 * @post The best path for the \em ship has been returned
	 *
	 * @cplx Linear in the number of cities after \em cityId
	 */
	Path _find_best_path( Ship ship, const Catalogue& catalogue, const std::string& cityId);
public:
	/** 
	* @brief The default constructor of River
	*/
	River();
	/**
	* @brief Checks if a city exists within the river
	*
	* @pre True
	* @post True has been returned if the river has a city, false otherwise
	*
	* @cplx Logarithmic in the number of cities in the river
	*/
	bool has_city(const std::string& cityId) const;

	/**
	* @brief Gets the specified city from the river
	* 
	* @pre	The city exists in the river	
	* @post The specified city has been returned
	*
	* @cplx Logarithmic in the number of cities in the river
	*/
	City get_city(const std::string& cityId) const; 

	/**
	 * @brief Updates or adds a City withing the river. 
	 *
	 * @pre True
	 * @post The city has been updated in the River. 
	 *
	 * @cplx Linear to the number of products in the city plus logarithmic in the number of cities in the river
	 */
	void set_city(const std::string& cityId, const City& city); 

	/**
	* @brief It does a trade between the cities
	*
	* @pre True
	* @post The cities have traded
	*
	* @cplx Linear in the number of different products the city two cities have combined
	*/
	void trade(const Catalogue& catalogue, City& city1, City& city2);
	/**
	* @brief It does a trade between the cities
	*
	* @pre True
	* @post The cities have traded
	*
	* @cplx Linear in the number of different products the city two cities have combined
	*/
	void trade(const Catalogue& catalogue, const std::string& cityId1, const std::string& cityId2);

	/**
	 * @brief Makes all the river trade
	 *
	 * @pre True
	 * @post All the river has traded
	 *
	 * @cplx n·m where n is the number of cities and m the number of products in the catalogue
	 */
	void redistribute(const Catalogue& catalogue);

	/**
	 * @brief Makes the ship do a trip ("hacer viaje")
	 *
	 * @pre True
	 * @post The ship has done a trip and it returns the total number of items bought and sold
	 *
	 * @cplx Linear in the number of cities
	 */
	int do_trip(Ship& ship, const Catalogue& catalogue);
	
	/**
	* @brief Reads the river structure from the std input
	*
	* @pre There is a valid river described in the std input
	* @post The river has been read and consumed from the std input
	*
	* @cplx n·log(n) where n is the number of cities in the std input
	*/
	void read();

	/**
	*@brief Reads the inventory of the city 
	*\n Note: This method is a wraper of the City::read_inventory method
	*@pre The city must be in the river and the pre of City::read_inventory must be true
	*@post That of City::read_inventory
	*
	*@cplx That of City::read_inventory
	*@see City::read_inventory
	*/
	bool apply_read_inventory(const std::string& cityId, int& productCount, const Catalogue& catalogue);
	/**
	*@brief Sets the market of the city 
	*\n Note: This method is a wraper of the City::set_product_market method
	*@pre The city must be in the river and the pre of City::set_product_market must be true
	*@post That of City::set_product_market
	*
	*@cplx That of City::set_product_market
	*@see City::set_product_market
	*/
	void apply_set_product_market(const std::string& cityId, int productId, const Product& product, int supply, int demand);

	/**
	*@brief Removes a product from the city 
	*\n Note: This method is a wraper of the City::remove_product method
	*@pre The city must be in the river and the pre of City::remove_product must be true
	*@post That of City::remove_product
	*
	*@cplx That of City::remove_product
	*@see City::remove_product
	*/
	void apply_remove_product(const std::string& cityId, int productId, const Product& product);
};
