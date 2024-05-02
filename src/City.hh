/**
 * @file City.hh
 * @brief This file contains the definition of City and Inventory
 */
#pragma once

#include "Inventory.hh"

struct City{
	Inventory stock;
	Inventory demand;
}
