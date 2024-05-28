/**
* @file Ship.hh
* @brief This file contains the headers of the Ship class
*/
#pragma once

#include <string>
#include <list>


class Ship {
private:
	int _supply_amount; //!< The amount of product the ship is suppplying (selling)
	int _supply_id;//!< The id of the product the ship is supplying (selling)

	int _demand_amount;//!< The amount of product the ship wants (buys)
	int _demand_id;//!< The id of the product the ship wants (buys)

	std::list<std::string> _log;//!< A log of all of the ship's trips
	
	/**
	* @brief Prints the market (supply and demand) of the boat
	*
	* @pre True
	* @post The market has been printed in the std output
	*
	* @cplx Constant
	*/
	void _print_market() const;
	
	/**
	* @brief Prints the travel log of the boat
	*
	* @pre True
	* @post The log has been printed in the std output
	*
	* @cplx Linear in the size of the log
	*/
	void _print_log() const;
public:
	Ship();//!< @brief The default constructor of the Ship class
	
	/**
	 * @brief Constructor of the ship class
	 *
	 * @pre True
	 * @post The implicit parameter has now the same demand and supply as \em ship but a new \em _log
	 *
	 * @cplx Constant
	 */
	Ship(const Ship& ship);
	/**
	 * @brief It returns the id of the product the ship has a supply off
	 *
	 * @pre True
	 * 
	 * @post The id of the product the ship has a supply off has been returned
	 *
	 * @cplx Constant
	 */
	int get_supply_id() const;
	/**
	 * @brief It returns the id of the product the ship wants to buy
	 *
	 * @pre True
	 * 
	 * @post The id of the product the ship wants to buy
	 *
	 * @cplx Constant
	 */
	int get_demand_id() const;

	/**
	 * @brief It returns the amount of the product the ship has a supply off
	 *
	 * @pre True
	 * 
	 * @post The amount of products the ship has a supply off has been returned
	 *
	 * @cplx Constant
	 */
	int get_supply_amount() const;

	/**
	 * @brief It returns the amount of the product the ship wants to buy 
	 *
	 * @pre True
	 * 
	 * @post The amount of products the ship wants to buy has been returned
	 *
	 * @cplx Constant
	 */
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

	/**
	* @brief The ship sells \em amount of its stock
	*
	* @pre The ship has more products than what he wants to sell
	* @pro The ship has sold amount of products
	*
	* @cplx Constant
	*/
	void sell(int amount);
	/**
	* @brief The ship buys \em amount products
	*
	* @pre The ship wants amount of products.
	* @post The ship has sold amount of products
	*
	* @cplx Constant
	*/
	void buy(int amount);

	/**
	* @brief Returns the travel log of the ship 
	*
	* @pre True
	* @post The travel log has been returned
	*
	* @cplx Linear in the size of the log (list copy cost)
	*/
	std::list<std::string> get_log() const;

	/**
	 * @brief Logs the city
	 *
	 * @pre cityId is a valid id 
	 * @post the city has been logged into the ship
	 *
	 * @cplx Constant
	 */
	void log(const std::string& cityId);
	/**
	* @brief Clears the travel log
	*
	* @pre True
	* @post The log has been cleared
	*
	* @cplx Linear in the size of the log
	*/
	void clear_log();


	/**
	* @brief Prints the ship
	*
	* @pre True
	* @post The ship has been printed in the std output
	*
	* @cplx Linear in the size of the log
	*/
	void print() const;

	/**
	* @brief Reads the ship
	*
	* @pre There is a ship in the std input
	* @post The ship has been consumed from the std input and read into this one
	*
	* @cplx Constant
	*/
	void read();

};
