/**
* @file Catalogue.hh
* @brief This file contains the headers of the Catalogue class and the product type.
*/
#pragma once 

#include <vector>
#include <utility>

typedef std::pair<int,int> Product;//!< @brief A type that abstacts products 

/**
 * @brief A class that contains all products
*/
class Catalogue{
private:
	std::vector<Product> _products;//!< @brief Where the products are contained
public:
	/**
	* @brief The default constructor of the class
	*/
	Catalogue();

	/**
	* @brief Returns the number of products in the catalogue
	*
	* @pre True
	*
	* @post The number of products in the catalogue has been returned
	*
	* @cplx Constant
	*/
	int size() const;

	/**
	* @brief Checks if the product exists within the catalogue
	*
	* @pre True
	*
	* @post The return value is true if it the catalogue has the product, false otherwise
	*
	* @cplx Constant
	*/
	bool has_product(int productId) const;

	/**
	* @brief It creates a new products and efficiently adds it to the Catalogue
	*
	* @pre \em weight and \em volume are both positive integers
	*
	* @post A new product with \em weight weight and \em volume volume has been created and addded to the catalogue, and its id has been returned
	*
	* @cplx Amortized constant
	*/
	int emplace_product(int weight, int volume);

	/**
	* @brief It returns the specified product
	* 
	* @pre The product exists and \em productId is its id
	*
	* @post The specified product has been returned
	*
	* @cplx Constant
	*/
	Product get_product(int productId) const;

	/**
	* @brief It prints in the std output the specified product
	*
	* @pre The product exists and \em productId is its id
	*
	* @post The product has been printed
	*
	* @cplx Constant
	*/
	void print_product(int productId) const;

	/**
	* @brief It reads \em productCount products from the std input and adds them to the catalogue
	*
	* @pre There are \em productCount products in the std input
	*
	* @post The products have been consumed from the std input and added to the catalogue
	* 
	* @cplx Linear in \em productCount (As long as emplace_product() remains constant)
	*/
	void read(int productCount);

	/**
	* @brief It reads n from the std input and adds n producst to the catalogue
	* @pre There is n, and n products in the std input
	* @post n and the products have been consumed from the std input and added to the catalogue
	*
	* @cplx Linear in n (As long as emplace_product() remains constant)
	*/
	void read();

};

