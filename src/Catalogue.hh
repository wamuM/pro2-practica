/**
* @file Catalogue.hh
* @brief A file that has all the definitions of the Catalogue class and the Product type.
*/
#pragma once 

#include <vector>
#include <utility>

typedef std::pair<int,int> Product;//<! @brief A type that abstacts products 

/**
 * @brief A class that contains all products
*/
class Catalogue{
private:
	std::vector<Product> _products;//<! @brief Where the products are contained
public:
	/**
	* @brief The default constructor of the class
	*/
	Catalogue();

	/**
	* @brief Returns the number of products
	*
	* @pre True
	*
	* @post The number of elements has been returned
	*
	* @cplx Constant
	*/
	int size() const;

	/**
	* @brief Checks if the product exists within the catalogue
	*
	* @pre True
	*
	* @post The return value is true if it the catalogue has the value, false otherwise
	*
	* @cplx Constant
	*/
	bool has_product(int productId) const;

	/**
	* @brief It creates a new products and efficiently adds it to the Catalogue
	*
	* @pre weight and volume are both positive integers
	*
	* @post A new product with weight weight and volume volume has been created and addded to the catalogue, and its id has been returned
	*
	* @cplx Amortized constant
	*/
	int emplace_product(int weight, int volume);

	/**
	* @brief It returns the specified product
	* 
	* @pre The product exists
	*
	* @post The specified product has been returned
	*
	* @cplx Constant
	*/
	Product get_product(int productId) const;

	/**
	* @brief It prints in the std output the specified product
	*
	* @pre The product exists and productid is its id
	*
	* @post The product has been printed
	*
	* @cplx Constant
	*/
	void print_product(int productId) const;

	/**
	* @brief It reads and adds productCount products to the catalogue
	*
	* @pre There are productCount products in the std input
	*
	* @post The products have been consumed from the std input and added to the catalogue
	* 
	* @cplx Linear in productCount (As long as emplace_product remains constant)
	*/
	void read(int productCount);

	/**
	* @brief It reads n from the std input and adds n producst to the catalogue
	* @pre There is n, and n products in the std input
	* @post n and the products have been consumed from the std input and added to the catalogue
	*
	* @cplx Linear in n (As long as emplace_product remains constant)
	*/
	void read();

};

