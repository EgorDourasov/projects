// Final Project Milestone 4
// File Product.cpp
// Version 1.0
// Date	03/21/2016
// Author	Egor Dourasov
// Description Product class definitions
/////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#include "Product.h"

#include <cstring>
namespace sict{


	Product::Product(){
		strcpy(sku_, "");
		name_ = nullptr;
		price_ = 0;
		taxed_ = true;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}
	Product::Product(const char * sku, const char * name, bool taxed, double price, int qtyNeeded){
		strcpy(sku_, sku);
		int len = strlen(name);
		name_ = new char[len];
		strncpy(name_, name, len);
		name_[len] = '\0';
		price_ = price;
		taxed_ = taxed;
		quantity_ = 0;
		qtyNeeded_ = qtyNeeded;
	}
	Product::Product(Product& src){
		strcpy(sku_, src.sku_);
		name_ = new char[strlen(src.name_)];
		strcpy(name_, src.name_);
		price_ = src.price_;
		taxed_ = src.taxed_;
		quantity_ = src.quantity_;
		qtyNeeded_ = src.qtyNeeded_;
	}
	Product::~Product(){ }


	//Setters
	void Product::sku(const char* sku){
		strcpy(sku_, sku);
	}
	void Product::price(double price){
		price_ = price;
	}
	void Product::name(const char* name){
		int len = strlen(name) ;
		name_ = new char[len];
		strncpy(name_, name, len);
		name_[len] = '\0';
	}
	void Product::taxed(bool taxed){
		taxed_ = taxed;
	}
	void Product::quantity(int quantity){
		quantity_ = quantity;
	}
	void Product::qtyNeeded(int qtyNeeded){
		qtyNeeded_ = qtyNeeded;
	}

	//getters
	const char* Product::sku() const{
		return sku_;
	}
	double Product::price() const{
		return price_;
	}
	const char* Product::name() const{
		return name_;
	}
	bool Product::taxed() const{
		return taxed_;
	}
	int Product::quantity() const{
		return quantity_;
	}
	int Product::qtyNeeded() const{
		return qtyNeeded_;
	}
	double Product::cost() const{
		return taxed_ == 0 ? price_ : (price_ * (1 + TAX));
	}
	bool Product::isEmpty() const{
		return (name_ == nullptr &&	price_ == 0 &&
				quantity_ == 0 && qtyNeeded_ == 0 )? true : false;
	}

	//operator overloads
	Product& Product::operator=(const Product& src){
		strcpy(sku_, src.sku_);
		delete[] name_;
		name_ = new char[strlen(src.name_)];
		strcpy(name_, src.name_);
		price_ = src.price_;
		taxed_ = src.taxed_;
		quantity_ = src.quantity_;
		qtyNeeded_ = src.qtyNeeded_;
		return *this;
	}
	bool Product::operator==(const char* src){
		return strcmp(sku_, src) == 0? true : false;
	}
	int Product::operator+=(int src){
		return quantity_ += src;
	}
	int Product::operator-=(int src){
		return quantity_ -= src;
	}



	

	std::ostream& operator<<(std::ostream& ost, const Product& prod){
		return prod.write(ost, true);
	}
	std::istream& operator>>(std::istream& ist, Product& prod){
		return prod.read(ist);
	}




}