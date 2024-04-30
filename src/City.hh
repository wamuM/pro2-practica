/**
 * @file City.hh
 * @brief This file contains the definition of City and Inventory
 */
#pragma once

typedef map<int,int> Inventory;//!< @brief A way to describe amounts of products

class City{
private:
	Inventory _stock; //!< @brief The amount the city has of each product
	Inventory _demand;//!< @brief The amount the city needs of each product
public:
	/**
	* @brief The default constructor of City
	*/
	City();	
}
