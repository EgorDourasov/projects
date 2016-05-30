// Final Project Milestone 2
// File ErrorMessage.h
// Version 1.0
// Date	03/13/2016
// Author	Egor Dourasov
// Description ErrorMessage class declarations
/////////////////////////////////////////////////////////////////

#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>
namespace sict{

class ErrorMessage{
	private:
		char* message_;
	public:
		ErrorMessage();
		ErrorMessage(const char* errorMessage);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const char* errorMessage);
		virtual ~ErrorMessage();
		void clear();
		bool isClear() const;
		void message(const char* value);
		const char* message() const;
};
		std::ostream& operator<<(std::ostream&, const ErrorMessage&);
}
#endif

