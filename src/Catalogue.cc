#include "Catalogue.hh"

#include <vector>
#include <iostream>

using namespace std;

Catalogue::Catalogue(){
	_products = vector<Product>(0);
}

int Catalogue::size() const{
	return _products.size();
}

bool Catalogue::has_product(int productId) const{
	return _products.size() >= productId and productId > 0;
}

int Catalogue::emplace_product(int weight, int volume){
	_products.emplace_back(weight, volume);
	return _products.size();
};

Product Catalogue::get_product(int productId) const{
	return _products[productId-1];
}

void Catalogue::print_product(int productId) const{
	cout<<_products[productId-1].first<<' '
	    <<_products[productId-1].second<<endl;
}

void Catalogue::read(){
	int n;
	cin>>n;
	while(n--){
		int weight, volume;
		cin>>weight>>volume;
		emplace_product(weight,volume);
	}
};
