#include <iomanip>
#include <iostream>
#include "Date.h"
#include "general.h"
using namespace std;


namespace sict
{
    int Date::value()const
    {
        return year_ * 372 + mon_ * 31 + day_;
    }
    
    int Date::mdays()const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }
	
	void Date::errCode(int errorCode){
		readErrorCode_ = errorCode;
	}
	
	Date::Date(){
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	
	Date::Date(int year, int month, int day){
		year_ = year;
		mon_ = month;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}
	
	bool Date::operator==(const Date& D)const{
		if(this->value() == D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator!=(const Date& D)const{
		if(this->value() != D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator<(const Date& D)const{
		if(this->value() < D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator>(const Date& D)const{
		if(this->value() > D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator<=(const Date& D)const{
		if(this->value() <= D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator>=(const Date& D)const{
		if(this->value() >= D.value())
			return true;
		else
			return false;
	}
	
	int Date::errCode()const{
		return readErrorCode_;
	}
	
	bool Date::bad()const{
		if (readErrorCode_ != 0)
			return true;
		else
			return false;
	}
	
	
	std::ostream& Date::write(std::ostream& ostr)const{
		ostr << year_ << '/' << setw(2) << setfill('0') <<  mon_ << '/'  << setw(2) << setfill('0') << day_;
		return ostr;
	}
	
	std::ostream& operator<<(std::ostream& os, const Date& a){
		 a.write(os);
		 return os;
	}
	
	std::istream& operator>>(std::istream& is, Date& a){
		a.read(is);
		return is;
	}
	
	std::istream& Date::read(std::istream& istr){
		char eater;
		istr >> year_ >> eater >> mon_ >> eater >> day_;
			
		if(year_ == '\0' || mon_ == '\0' || day_ == '\0'){
			Date::errCode(CIN_FAILED);
		}
		else if(year_ > MAX_YEAR || year_ < MIN_YEAR){
			Date::errCode(YEAR_ERROR);
		}
		else if(mon_ > 12 || mon_ < 1){
			Date::errCode(MON_ERROR);
		}
		else if(day_ > Date::mdays() || day_ < 1){
			Date::errCode(DAY_ERROR);
		}
		else{
			Date::errCode(NO_ERROR);
		}
			
		return istr;
	}
	
	
}