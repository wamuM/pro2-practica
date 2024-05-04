/**
 * @file City.hh
 * @brief This file contains the definition of City and Inventory
 */
#pragma once

#include <pair>
#include <string>

#include "Inventory.hh"

class City {
private:
	Inventory _stock;
	Inventory _offer; 
		
public:
	City();
	Inventory get_stock() const;
	Inventory get_offer() const;
	
	void set_stock();
	void set_offer();

	void set_right();
	void set_left();

	
	std::pair<int,int> get_totals() const;		

	void print() const;
}
