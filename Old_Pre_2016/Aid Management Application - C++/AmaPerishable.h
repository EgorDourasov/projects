// Final Project Milestone 5
// Version 1.0
// Date	04/03/2016
// Author	Egor Dourasov
// Description: AmaPerishable.h - Date class definition
/////////////////////////////////////////////////////////////////

#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include "AmaProduct.h"
#include "Date.h"



namespace sict{
  class AmaPerishable: public AmaProduct{

  private:
	  Date expiry_;
  public:
	  AmaPerishable(const char tag = 'P');
	  ~AmaPerishable();
	  const Date& expiry() const;
	  void expiry(const Date& value);

	  fstream& store(fstream& file, bool addNewLine = true)const;
	  fstream& load(fstream& file);
	  ostream& write(ostream& ostr, bool linear)const;
	  istream& read(istream& istr);
  };
}
#endif
