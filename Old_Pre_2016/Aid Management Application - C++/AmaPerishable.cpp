// Final Project Milestone 5
// Version 1.0
// Date	04/03/2016
// Author	Egor Dourasov
// Description: AmaPerishable.cpp - Date class definition
/////////////////////////////////////////////////////////////////

#include "AmaPerishable.h"

namespace sict{

	//constructor
	AmaPerishable::AmaPerishable(const char tag) :AmaProduct(tag){	}

	//default destructor
	AmaPerishable::~AmaPerishable(){}

	//expiry getter
	const Date& AmaPerishable::expiry() const{
		return expiry_;
	}
	//expiry setter
	void AmaPerishable::expiry(const Date& value){
		expiry_ = value;
	}

	//store() overload implementation
	fstream& AmaPerishable::store(fstream& file, bool addNewLine)const{
		AmaProduct::store(file, false);
		file << "," << expiry_;
		if (addNewLine == true) file << std::endl;
		return file;
	}
	//load() overload implementation
	fstream& AmaPerishable::load(fstream& file){
		AmaProduct::load(file);
		file.ignore(1);
		file >> expiry_;
		return file;
	}
	//write() overload implementation
	ostream& AmaPerishable::write(ostream& ostr, bool linear)const{
		
		AmaProduct::write(ostr, linear);
		if (AmaPerishable::err_.isClear()){  
			if (linear == true){
				expiry_.Date::write(ostr);
			}
			else {
				ostr << std::endl << "Expiry date: " << expiry_;
			}
		}
		return ostr;
	}
	//read() overload implementation
	istream& AmaPerishable::read(istream& istr){
		err_.clear();
		AmaProduct::read(istr);
		if (AmaPerishable::err_.isClear()){
			cout << "Expiry date (YYYY/MM/DD): ";
			Date date;

			cin >> date;
			//get the date error code and assign an error message based on that
			switch(date.errCode()){
			case 0:
				expiry_ = date;
				break;
			case 1:
				err_.message("Invalid Date Entry");
				istr.setstate(ios::failbit);
				break;
			case 2:
				err_.message("Invalid Year in Date Entry");
				istr.setstate(ios::failbit);
				break;
			case 3:
				err_.message("Invalid Month in Date Entry");
				istr.setstate(ios::failbit);
				break;
			case 4:
				err_.message("Invalid Day in Date Entry");
				istr.setstate(ios::failbit);
				break;
			}

		}
		return istr;
	}
}
