/**
* @file Ship.hh
* @brief This file contains the definition of Ship
*/
#pragma once

#include <string>
#include <list>

#include "River.hh"
/**
* @brief The ship that does fluvial trade
*/
class Ship{
private:
	int _buyId;//<! @brief The id of the product the ship wants to buy
	int _buyAmount;//<! @brief The amount of the product it wants to buy
	int _sellId;//<! @brief The id of the product the ship wants to sell
	int _sellAmount;//<! @brief The amount of the product the ship wants to sell
	std::list<std::string> _log;//<! @brief A log of the cities the ship has visited
public:
	void setBuy(int buyId, int buyAmount);
	void setBuyAmount(int buyAmount);

	void setSell(int sellId, int sellId);
	void setSellAmount(int sellAmount);

	void printCargo() const;
	void printLog() const;
	
	void trade(River& river, std::string cityId1, std::string cityId2);
	void redistribute(River& river);
	void travel(River& river);
}

