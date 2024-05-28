/**
 * @file River.hh
 * @brief This file conains the definition of River
 */
#pragma once

#include <map>
#include <string>
#include <stack>
#include <utility>

#include "City.hh"
#include "Ship.hh"

class River{
private:
	//! @brief A type that represents a path within the river and its associated value
	struct Path {
		int totalTransaction = 0;
		int length = 0;
		std::string finalCity;
	};

	std::map<std::string,City> _cities;//!< @brief A map that links a city id to its city.
	std::string _outlet;//!< @brief The id of the city that is at the river's outlet
	
	/**
	 * @brief Utility function that gives the minimun value between a and b
	 *
	 * @pre True
	 * @post The minimum value between a and b has been returned
	 *
	 * @cplx Constant
	 */
	static int min(int a, int b);
	
	/*
	 * @brief Recursively reads cities from the std input
	 *
	 * @pre There are cities properly described in the std input
	 * @post The cities have been, preserving the structure, added to the river
	 *
	 * @cplx Linear in the number of cities to read
	 */
	std::string _recursive_reading(std::string cityId);

	void _travel_path(int& buyAmount, int& sellAmount, int buyId, int sellId, const Catalogue& catalogue, const std::string& cityId);

	/**
	 * @brief Makes all the cities after cityId trade
	 *
	 * @pre cityId is a valid city
	 * @post All the cities after cityId have traded
	 *
	 * @cplx n·m where n is the number of cities and m the number of products in the catalogue
	 */
	void redistribute(const Catalogue& catalogue, const std::string& cityId);

	/**
	 * @brief Calculates the best possible transaction between a ship and a city of the river
	 * @pre cityId is a city of the river
	 * @post ship has done the transaction and the amount bought by the ship and the amount sold by the ship are returned in that order.
	 *
	 * @cplx Constant
	 */
	std::pair<int,int> _calculate_transaction(int& buyAmount, int& sellAmount, int buyId, int sellId, const std::string& cityId) const;

	/**
	 * @brief Finds the best path for the ship starting at cityId
	 *
	 * @pre cityId is a valid city
	 * @post The best path for the ship has been returned
	 *
	 * @cplx Linear in the number of cities after cityId
	 */
	Path _find_best_path(int buyAmount, int sellAmount, int buyId, int sellId, const std::string& cityId);
public:
	/** 
	* @brief The default constructor of River
	*/
	River();
	/**
	* @brief Checks if a city exists within the river
	*
	* @pre True
	* @post True has been returned if it has a city, false otherwise
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
	 * @brief Updates a City withing the river. 
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
	 * @brief Makes the ship do a trip
	 *
	 * @pre True
	 * @post The ship has done a trip and it returns the total number of items bought and sold
	 *
	 * @cplx Binomial in the number of cities
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
	*Note: This method is a wraper of the City::read_inventory method
	*@pre The city must be in the river and the pre of City::read_inventory must be true
	*@post That of City::read_inventory
	*
	*@cplx That of City::read_inventory
	*@see City::read_inventory
	*/
	bool apply_read_inventory(const std::string& cityId, int& productCount, const Catalogue& catalogue);
	void apply_set_product_market(const std::string& cityId, int productId, const Product& product, int supply, int demand);
	void apply_remove_product(const std::string& cityId, int productId, const Product& product);
};
