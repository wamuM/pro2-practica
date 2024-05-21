/**
 * @file River.hh
 * @brief This file conains the definition of River
 */
#pragma once

#include <map>
#include <string>

#include "City.hh"
#include "Ship.hh"

class River{
private:
	std::map<std::string,City> _cities;//!< @brief A map that links a city id to its city.
	std::string _outlet;//!< @brief The id of the city that is at the river's outlet
	
	/*
	 * @brief Recursively reads cities from the std input
	 *
	 * @pre There are cities properly described in the std input
	 *
	 * @post The cities have been, preserving the structure, added to the river
	 *
	 * @cplx Linear in the number of cities to read
	 */
	std::string _recursive_reading();
public:
	/**
	* @brief The default constructor of River
	*/
	River();
	/**
	* @brief Checks if a city exists within the river
	*
	* @pre True
	* @param cityId The id of the city to check
	*
	* @return if it has a city
	* @post True
	*
	* @cplx Logarithmic in the number of cities in the river
	*/
	bool has_city(const std::string& cityId) const;

	/**
	* @brief Gets the specified city from the river
	* 
	* @pre	The city exists in the river	
	* @param cityId The id of the city
	*
	* @return The specified city
	* @post The specified city has been returned
	*
	* @cplx Logarithmic in the number of cities in the river
	*/
	City get_city(const std::string& cityId); 

	/**
	 * @brief Updates a City withing the river. 
	 *
	 * @pre True
	 * @param cityId The id of the city 
	 * @param city The city to be updated
	 *
	 * @post The city has been updated in the River. 
	 *
	 * @cplx [CAN BE OPTIMIZED] Linear to the number of products in the city plus logarithmic in the number of cities in the river
	 */
	void update_city(const std::string& cityId, City city); 

	void trade(Ship& ship, const std::string& cityId1, const std::string& cityId2);
	void redistribute(Ship& ship);
	void do_trip(Ship& ship);
	
	/**
	* @brief Reads the river structure from the std input
	*
	* @pre There is a valid river described in the std input
	*
	* @post The river has been read and consumed from the std input
	*
	* @cplx n·log(n) where n is the number of cities in the std input
	*/
	void read();
};
