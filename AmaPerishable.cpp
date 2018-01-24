#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaPerishable.h"

using namespace std;

namespace sict
{
    AmaPerishable::AmaPerishable() : AmaProduct('P'){}
	
	const Date& AmaPerishable::expiry() const{
		return expiry_;
	}
	
	void AmaPerishable::expiry(const Date &value){
		expiry_ = value;
	}
	
	fstream& AmaPerishable::store(fstream& file, bool addNewLine) const{
        AmaProduct::store(file, false);
        file << ',' << expiry();
        if(addNewLine == true){
            file << endl;
        }
        return file;
    }

    fstream& AmaPerishable::load(fstream& file){
        AmaProduct::load(file);
        expiry_.read(file);
        file.ignore();
        return file;
    }

    ostream& AmaPerishable::write(ostream& ostr, bool linear) const{
        AmaProduct::write(ostr,linear);
        if(err_.isClear() && (!isEmpty())){
            if(linear){
                expiry_.write(ostr);
            }
            else{
                cout << endl << "Expiry date: ";
                expiry_.write(ostr);
            }
        }
        return ostr;
    }

    istream& AmaPerishable::read(istream& istr){
        AmaProduct::read(istr);
        Date theDate;
            if(err_.isClear()){
                cout << "Expiry date (YYYY/MM/DD): ";
                istr >> theDate;
            }
        if(theDate.errCode() != 0){
            if(theDate.errCode() == 1){
                err_.message("Invalid Year in Date Entry");
            }
            else if(theDate.errCode() == 2){
                err_.message("Invalid Year in Date Entry");
            }
            else if(theDate.errCode() == 3){
                err_.message("Invalid Month in Date Entry");
            }
            else if(theDate.errCode() == 4){
                err_.message("Invalid Day in Date Entry");
            }
            istr.setstate(ios::failbit);
        }
        else{
            expiry_ = theDate;
        }
        return istr;
    }
}