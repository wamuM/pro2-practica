/**
 * @file Catalogue.hh
 * @brief This file contains the definition of Product and Catalogue (a product container).
 */

#pragma once
#include <vector>
#include <utility>

typedef std::pair<int,int> Product;//<! @brief Where the first value is the weight of the product and the second value is the volume
/**
* @brief The container of all products with their descriptions
*/
class Catalogue{
private:
	std::vector<Product> _container;//!< @brief A vector that contains the Products
	// A vector was chosen because of the constant look up time
	int _size;//!< @brief The number of products
public:
	/**
	* @brief The default constructor for Catalogue
	*/
	Catalogue();

	/** 
	 * @brief Returns the number of products 
	 * @return The number of products
	 */
	int size() const;
	
	/**
	 * @brief Checks if the catalogue has said product
	 * @pre True
	 *
	 * @param id The id of the product
	 * @return If the catalogue has the product
	 *
	 * @post If the catalogue has the product it returns true, false otherwise
	 */
	bool hasProduct(int id) const;

	/**
	 * @brief Gets the specified product 
	 * @pre The product exists
	 *
	 * @param id The id of the product
	 * @return The specified product. 
	 * 
	 * @post The product is returned
	 */
	Product getProduct(int id) const;

	/**
	 * @brief Modifies the specified product
	 * @pre The product exists
	 *
	 * @param id The id of the product
	 * @param weight The new weight of the product
	 * @param volume The new volume of the product 
	 * 
	 * @post The product has been modified
	 */
	void setProduct(int id, int weight, int volume);
	
	/**
	 * @brief Adds a new product to the catalogue
	 * @pre True
	 *
	 * @param weight The weight for the new product
	 * @param volume The volume for the new product 
	 *
	 * @post The product has been added to the catalogue
	 */
	void emplace(int weight, int volume);

	/**
	* @brief Reads <em>n</em> products from the <em>std input</em> and adds them to the catalogue
	* It first reads <em>n</em> from the std input. Then it reads <em>n</em> consecutive products from the <em>std input</em>. Assuming every product follows this format: <weight> <volume> (where weight is its weight, withouth the unit, and volume is its volume, without the unit)
	* The first product will be assigned <em>size()</em> as its <em>id</em>. And the next one will be assigned size()+1 and so on.
	*
	* @pre There are n product descriptions in the std input
	* @post The products have been read from the input stream and added to the catalogue
	*/
	void read();
}
