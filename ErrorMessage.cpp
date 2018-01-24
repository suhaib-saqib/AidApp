#include "ErrorMessage.h"
#include <cstring>

namespace sict
{
	ErrorMessage::ErrorMessage(){
		message_ = nullptr;
	}
	
	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;
		message(errorMessage);
	}
	
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		message(errorMessage);
		return *this;
	}
	
	ErrorMessage::~ErrorMessage(){
		clear();
	}
	
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;
	}
	
	bool ErrorMessage::isClear() const{
		if(message_ == nullptr)
			return true;
		else
			return false;
	}
	
	void ErrorMessage::message(const char* value){
		clear();
		message_ = new char[strlen(value) + 1];
		strcpy(message_,value);
	}
	
	const char* ErrorMessage::message() const{
		return message_;
	}
    
	std::ostream& operator<<(std::ostream& os, ErrorMessage& a){
		if (a.isClear() == false)
			os << a.message();
		return os;
		
			
	}
}