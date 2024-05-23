/**
* @file Ship.hh
* @brief This file contains the definition of the Ship class
*/
#pragma once

#include <string>
#include <list>


class Ship {
private:
	int _supply_amount; //!< The amount of product the ship is suppplying
	int _supply_id;//!< The id of the product the ship is supplying

	int _demand_amount;//!< The amount of product the ship wants
	int _demand_id;//!< The id of the product the boat wants

	std::list<std::string> _log;//!< A log of all of the ship's transactions
public:
	Ship();//!< The default constructor of the Ship class

	int get_supply_id() const;
	int get_demand_id() const;

	int get_supply_amount() const;
	int get_demand_amount() const;

	/**
	* @brief It sets the product the ship is supplying and it's amount
	* 
	* @pre productId is a valid product and amount is non negative
	* @post the supply has been set
	*
	* @cplx Constant.
	*/
	void set_supply(int productId, int amount);

	/**
	* @brief It sets the product the ship wants and it's amount
	* 
	* @pre productId is a valid product and amount is non negative
	* @post the wants have been set
	*
	* @cplx Constant.
	*/
	void set_demand(int productId, int amount);

	void sell();
	void buy();

	std::list<std::string> get_log() const;

	void clear_log();

	void print_market() const;
	void print_log() const;

	void print() const;
};
