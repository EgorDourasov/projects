// Final Project Milestone 1
// Version 1.0
// Date	03/11/2016
// Author	Egor Dourasov
// Description: Date.h - Date class and variable declaration
/////////////////////////////////////////////////////////////////

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>

#define NO_ERROR 0 //--No error the date is valid 
#define CIN_FAILED 1 //--istream failed when entering information 
#define YEAR_ERROR 2 //--Year value is invalid 
#define MON_ERROR 3 //--Month value is invalid 
#define DAY_ERROR 4 //--Day value is invalid

namespace sict{



  class Date{
  private:
	  int year_, mon_, day_, readErrorCode_;
	  void errCode(int errorCode);

	  //pre-defined
	  int value()const;
  public:
	  // con & de - structors
	  Date();
	  Date(int year, int mon, int day);
	  ~Date();

	  //member operator overloads
	  bool operator==(const Date& D)const; 
	  bool operator!=(const Date& D)const; 
	  bool operator<(const Date& D)const; 
	  bool operator>(const Date& D)const; 
	  bool operator<=(const Date& D)const; 
	  bool operator>=(const Date& D)const;

	  //Accessors & Getters:
	  int errCode() const;
	  bool bad() const;

	  //IO member functions
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr)const;

	  //pre-defined
	  int mdays()const;
  };

		//Need an overload for >> and <<
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);

}
#endif