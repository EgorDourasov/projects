// Final Project Milestone 4
// File Product.h
// Version 1.0
// Date	03/21/2016
// Author	Egor Dourasov
// Description Product class declarations
/////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_

#include <cstring>

#include "Streamable.h"
#include "general.h"
using namespace std;

namespace sict{

	class Product : public Streamable {
	private:
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;


	public:
		//constructos, destructors, operator overrides
		Product();
		Product(const char * sku, const char * name, bool taxed = true, double price = 0, int qtyNeeded = 0);
		Product(Product& src);
		virtual ~Product();
		

		//Setters
		void sku(const char* sku);
		void price(double price);
		void name(const char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);

		//getters
		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;
		bool isEmpty() const;

		

		//operator overloads
		Product& operator=(const Product& src);
		bool operator==(const char* src);
		int operator+=(int src);
		int operator-=(int src);
		operator double() { return cost()*quantity(); }
		double operator+=(const Product& prod);
		


	};

	
	std::ostream& operator<<(std::ostream& ost, const Product& prod);
	std::istream& operator>>(std::istream& ist, Product& prod);














}
#endif