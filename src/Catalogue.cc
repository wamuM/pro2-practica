#include "Catalogue.hh"

#include <iostream>
using namespace std;

Catalogue::Catalogue(){
	this->_container = vector<Product>(0);
}
int Catalogue::size(){
	return this->_container.size();
}

int Catalogue::hasProduct(int id){
	return id < this->size() and id >= 0;
}

Product Catalogue::getProduct(int id){
	return this->_container[id];
}

void Catalogue::setProduct(int id, int weight, int volume){
	this->_container[id].weight = weight;
	this->_container[id].volume = volume		
}

void Catalogue::emplace(int weight, int volume){
	this->_container.emplace_back(weight, volume);
}

void Catalogue::read(){
	int n;
	cin>>n;
	while(n--){
		int weight, volume;
		cin>>weight>>volume;
		this->emplace(weight,volume);		
	}	
}
