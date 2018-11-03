// Final Project Milestone 2
// File ErrorMessage.cpp
// Version 1.0
// Date	03/13/2016
// Author	Egor Dourasov
// Description ErrorMessage class definitions
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include "ErrorMessage.h"
#include <cstring>
namespace sict{

	ErrorMessage::ErrorMessage(){
		message_ = nullptr;
	}
	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;
		message(errorMessage);
	}
	ErrorMessage::~ErrorMessage(){}
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		clear();
		message(errorMessage);
		return *this;
	}
	
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;
	}
	bool ErrorMessage::isClear() const{
		return message_ == nullptr ? true : false;
	}
	void ErrorMessage::message(const char* value){
		message_ = new char[strlen(value) + 1];
		strcpy(message_, value);
	}

	const char* ErrorMessage::message() const{
		return message_;
	}

	std::ostream& operator<<(std::ostream& os, const ErrorMessage& errMsg){
		if (!errMsg.isClear()) os << errMsg.message();
		return os;
	}
}