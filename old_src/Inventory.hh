/**
* @file Inventory.hh
* @brief This file defines the inventory class
*/

#pragma once

/**
* @brief A way to describe amounts of products
*/
class Inventory{
private:
	map<int,int> _amounts;//<! Where the amounts are stored
public:
	void setAmount(int idProduct, int newAmount);
	void modifyAmount(int idProduct, int amountToAdd);
	int getAmount(int idProduct);
	int hasProduct(int idProduct);
	void print() const;
}
