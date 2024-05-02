/**
 * @file River.hh
 * @brief This file conains the definition of River
 */
#pragma once

#include <map>
#include <string>

#include "City.hh"

using namespace std;

class River{
private:
	map<string,City> _cities;//!< @brief A map that links a city id to its city.
	??? _structure;//!< @brief Where the river basin structure is encoded. 
public:
	/**
	* @brief The default constructor of River
	*/
	River();

	bool hasCity(string cityId) const;
	City getCity(string cityId) const; 
	void read();
}
