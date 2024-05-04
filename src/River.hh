/**
 * @file River.hh
 * @brief This file conains the definition of River
 */
#pragma once

#include <map>
#include <string>

#include "City.hh"

class River{
private:
	std::map<std::string,City> _cities;//!< @brief A map that links a city id to its city.
	std::string _outlet;//!< @brief The id of the city that is at the river's outlet
	
	std::string _recursive_reading();
public:
	/**
	* @brief The default constructor of River
	*/
	River();
	/**
	* @brief Checks if a city exists within the river
	* @param cityId The id of the city to check
	* @return if it has a city
	*/
	bool has_city(const std::string& cityId) const;

	/**
	* @brief Gets the specified city from the river
	* 
	* @pre	The city exists in the river	
	* @param cityId The id of the city
	* @post The specified city has been returned
	*
	* @return The specified city
	*/
	City get_city(const std::string& cityId) const; 

	void set_city(const std::string& cityId, City city); 

	void trade(Ship& ship, const std::string& cityId1, const std::string& cityId2);
	void redistribute(Ship& ship);
	void do_trip(Ship& ship);
	
	/**
	* @brief Reads the river structure from the std input
	*/
	void read();
}
