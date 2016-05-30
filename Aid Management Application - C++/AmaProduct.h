// Final Project Milestone 5
// Version 1.0
// Date	04/03/2016
// Author	Egor Dourasov
// Description: AmaProduct.h - Date class definition
/////////////////////////////////////////////////////////////////

#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include "Product.h"
#include "ErrorMessage.h"
#include <sstream>
#include <string>
#include <iomanip>

namespace sict{
  class AmaProduct : public Product{
  private:
	  char fileTag_;
	  char unit_[11];
  protected:
	  ErrorMessage err_;
  public:
	  //constructors
	  AmaProduct(char fileTag = 'N');
	  ~AmaProduct();
	  //public member functions
	  const char* unit() const;
	  void unit(const char* value);
	  std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	  std::fstream& load(std::fstream& file);
	  std::ostream& write(std::ostream& os, bool linear)const;
	  std::istream& read(std::istream& is);
  };
}
#endif


