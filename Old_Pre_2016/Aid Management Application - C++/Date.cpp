// Final Project Milestone 1
// Version 1.0
// Date	03/11/2016
// Author	Egor Dourasov
// Description: Date.cpp - Date class definition
/////////////////////////////////////////////////////////////////


#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict{

	int Date::value()const{
		return year_ * 372 + mon_ * 31 + day_;
	}
	void Date::errCode(int errorCode){
		readErrorCode_ = errorCode;
	}
	Date::Date(){
		year_ = 0;
		mon_ = 00;
		day_ = 00;
		readErrorCode_ = NO_ERROR;
	}
	Date::Date(int year, int mon, int day){
		year_ = year;
		mon_ = mon;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}
	Date::~Date(){}

	bool Date::operator==(const Date& D)const{
		if (this->value() == D.value()) return true;
		else return false;
	}
	bool Date::operator!=(const Date& D)const{
		if (this->value() != D.value()) return true;
		else return false;
	}
	bool Date::operator<(const Date& D)const{
		if (this->value() < D.value()) return true;
		else return false;
	}
	bool Date::operator>(const Date& D)const{
		if (this->value() > D.value()) return true;
		else return false;
	}
	bool Date::operator<=(const Date& D)const{
		if (this->value() <= D.value()) return true;
		else return false;
	}
	bool Date::operator>=(const Date& D)const{
		if (this->value() >= D.value()) return true;
		else return false;
	}
	int Date::mdays()const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}
	int Date::errCode()const{
		return readErrorCode_;
	}
	bool Date::bad()const{
		return readErrorCode_ == NO_ERROR ? false : true;
	}
	std::istream& Date::read(std::istream& istr){
			istr >> year_;
			istr.ignore(1);
			istr >> mon_;
			istr.ignore(1);
			istr >> day_;
			if (istr.fail()){
				errCode(CIN_FAILED);
			} else{
				if (year_ >= MIN_YEAR && year_ <= MAX_YEAR){
					if (mon_ >= 1 && mon_ <= 12){
						if (day_ >= 1 && day_ <= mdays()){
							errCode(NO_ERROR);
						}
						else errCode(DAY_ERROR);
					}
					else errCode(MON_ERROR);
				}
			else errCode(YEAR_ERROR);
			
		}
		
		return istr;

	}
	std::ostream& Date::write(std::ostream& ostr)const{
		return ostr << year_ << '/' << 
			setw(2) << right << setfill('0') << mon_ << '/' <<
			setw(2) << right << setfill('0') << day_;
		
	}

	std::istream& operator>>(std::istream& is, Date& date){
		date.read(is);
		return is;
		

	}
	std::ostream& operator<<(std::ostream& os, const Date& date){
		date.write(os);
		return os;

	}


}
