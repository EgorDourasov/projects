// Final Project Milestone 5
// Version 1.0
// Date	04/11/2016
// Author	Egor Dourasov
// Description: AmaProduct.cpp - Date class definition
/////////////////////////////////////////////////////////////////

#include "AmaProduct.h"


namespace sict{

	//constructor
	AmaProduct::AmaProduct(char fileTag):Product(){
		fileTag_ = fileTag;

	}
	//default destructor
	AmaProduct::~AmaProduct(){}

	//unit getter
	const char* AmaProduct::unit() const{
		return unit_;  
	}
	//unit setter
	void AmaProduct::unit(const char* value){
		int i = strlen(value);
		i > 10 ? i = 10 : i;
		strncpy(unit_,value,i);
		unit_[i] = '\0';
	}
	
	//store values, delimiting them with a comma
	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const{
		file << fileTag_ << ",";
		file << sku() << ",";
		file << name()	<< ",";
		file << price() << ",";
		file << taxed() << ",";
		file << quantity() << ",";
		file << unit() << ",";
		file << qtyNeeded();
		if (addNewLine == true) file << std::endl;
		return file;
	}

	std::fstream& AmaProduct::load(std::fstream& file){
		//create temporary variables for reading from the file and type conversions
		char sku[MAX_SKU_LEN + 1];
		char name[50];
		double price; 
		bool taxed; char taxed_char;
		int quantity; 
		int qtyNeeded; 
		char unit[11];
		
		
		//first 2 are char arrays, so they are easy to get
		file.get(sku,11,',');		file.ignore();	Product::sku(sku);
		file.get(name, 20, ',');		file.ignore();	Product::name(name);
		
		//grab and assign price 
		file >> price;
		file.ignore();	

		
		//get the char for taxed and change cost based on taxed being true or false
		file.get(taxed_char);		
		file.ignore();	
		(taxed_char == '1') ? taxed = true : taxed = false;
		Product::taxed(taxed);
		Product::price(price);
		
		//grab and assign quantity 
		
		file >> quantity;
		file.ignore();


		Product::quantity(quantity);
		
		//unit is a char array so it's easy to get
		file.getline(unit, 11, ',');
		AmaProduct::unit(unit);

	
		
		//grab and assign  qtyNeeded 
		file >> qtyNeeded;

		Product::qtyNeeded(qtyNeeded);
		
		return file;
	}

	std::ostream& AmaProduct::write(std::ostream& os, bool linear)const{
		if (err_.isClear()){
			if (linear == true){
				//truncating name down to 20 characters
				int len = strlen(name());
				len > 20 ? len = 20 : len;
				char* trunc_name = nullptr;
				trunc_name = new char[len+1];
				strncpy(trunc_name, name(), len);
				trunc_name[len] = '\0';
				

				//linear output in a specific format
				os << left << setw(MAX_SKU_LEN) << setfill(' ') << sku() << "|" 
					<< left << setw(20) << setfill(' ') << trunc_name << "|"
					<< right << fixed << setfill(' ') << setprecision(2) << setw(7) << cost() << "|"
					<< right << setw(4) << setfill(' ') << quantity() << "|"
					<< left << setw(10) << setfill(' ') << unit() << "|"
					<< right << setw(4) << setfill(' ') << qtyNeeded() << "|";
			}
			//if linear == false, output as a wall of text
			else {
				os << "Sku: " << sku() << std::endl;
				os << "Name: ";
				os << name();
				os << std::endl;
				os << "Price: ";
				os << price();
				os << std::endl;
				os << "Price after tax: ";
				if (taxed() == true){
					os << (price()*1.13);
					os << std::endl;
				}
				else{
					os << "N/A";
					os << std::endl;
				}
				os << "Quantity On Hand: ";
				os << quantity();
				os << " ";
				os << unit();
				os << std::endl;
				os << "Quantity Needed: ";
				os << qtyNeeded();
			}
		}
		else {
			os << err_;
		}
		return os;

	}
	std::istream& AmaProduct::read(std::istream& is){
		//temporary values to be used in the product setter methods
		char sku[MAX_SKU_LEN + 1];
		char name[50];
		double price;
		char taxed;
		bool taxed_bool = true;
		int quantity;
		int qtyNeeded;
		char unit[11];

		//first 3 are char arrays, so validation wouldnt fail
		cout << "Sku: ";
		is >> sku;		
		cout << "Name: ";
		is >> name;		
		cout << "Unit: ";
		is >> unit;		
		
		//if taxed is not y Y n N chars, get an error
		cout << "Taxed? (y/n): ";
		is >> taxed;	

		if (taxed == 'y' || taxed == 'Y' || taxed == 'n' || taxed == 'N'){
			(taxed == 'y' || taxed == 'Y')? taxed_bool = true : taxed_bool = false;
			while (getchar() != '\n');
			//get and validate the price
			cout << "Price: ";
			is >> price;	
			if (is.fail()){
				err_.message("Invalid Price Entry");
			} 
			else{
				//get and validate quantity
				cout << "Quantity On hand: ";
				is >> quantity;
				if (is.fail()){
					err_.message("Invalid Quantity Entry");
				}

				else {
					//get and validate quantity needed
					cout << "Quantity Needed: ";
					is >> qtyNeeded; 
					if (is.fail()){
						err_.message("Invalid Quantity Needed Entry");
					}
					else{
						//if all is good, assign the values and clear the error
						Product::sku(sku);
						Product::name(name);
						Product::price(price);
						Product::taxed(taxed_bool);
						Product::quantity(quantity);
						AmaProduct::unit(unit);
						Product::qtyNeeded(qtyNeeded);
						err_.clear();
					}
				}
			}
		}
		//error if the taxed value is not one of: y Y n N
		else {
			err_.message("Only (Y)es or (N)o are acceptable");
			is.setstate(ios::failbit);
		}

		return is;
		
	}

}