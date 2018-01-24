#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
#include <iostream>

namespace sict
{
    class Date
    {
    private:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;
        int value()const;
		void errCode(int errorCode);
    
    public:
        Date();
		Date(int, int, int);
        int mdays()const;
		bool bad()const;
		int errCode()const;
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
    };
	std::ostream& operator<<(std::ostream& os, const Date& a);
	std::istream& operator>>(std::istream& is, Date& a);
}

#endif