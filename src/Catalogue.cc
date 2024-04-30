#include "Catalogue.hh"

Catalogue::Catalogue(){
	this->_container = vector<Product>(0);
	this->_size = 0;
}
Catalogue::Catalogue(int allocate_size ){
	this->_container = vector<Product>(allocate_size);
	this->_size = 0;
}
