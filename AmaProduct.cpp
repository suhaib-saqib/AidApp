#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaProduct.h"

using namespace std;

namespace sict
{
	AmaProduct::AmaProduct(char ft){
		fileTag_ = ft;
	}
	const char* AmaProduct::unit() const{
		return unit_;
	}
	
	void AmaProduct::unit(const char* value){
		strncpy(unit_,value,11);
	}
	
	std::fstream& AmaProduct::store(fstream& file, bool addNewLine) const{
		file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();
		
		if(addNewLine == true){
			file << endl;
		}
		
		return file;
	}	
	
	fstream& AmaProduct::load(fstream& file){
        char buffer[2000];
        double doublebuffer;
        int intbuffer;
        file.getline(buffer,2000,',');
        sku(buffer);
        file.getline(buffer,2000,',');
        name(buffer);
        file >> doublebuffer;
        price(doublebuffer);
        file.ignore();
        file >> intbuffer;
        taxed(bool(intbuffer));
        file.ignore();
        file >> intbuffer;
        quantity(intbuffer);
        file.ignore();
        file.getline(buffer,2000,',');
        unit(buffer);
        file >> intbuffer;
        qtyNeeded(intbuffer);
        file.ignore();
        file.clear();
        return file;
    }
	 
	ostream& AmaProduct::write(ostream& os, bool linear) const{
        if(err_.isClear() == false){
            os << err_.message();
            return os;
        }
        else{
			os.fill(' ');
            if(linear == true){
                os << left << setw(MAX_SKU_LEN) << sku() << "|" << left << setw(20) << name() << "|" << right << setprecision(2) << fixed << setw(7)  << cost() << "|" << right << setw(4) << quantity() << "|" << setw(10) << left << unit() << "|" << right << setw(4) << qtyNeeded() << "|";
            }
            else{
                os << "Sku: " << sku() << endl << "Name: " << name() << endl << "Price: " << price() << endl << "Price after tax: ";
				if (price() == cost()){
					os << "N/A";
				}
				else{
					os << cost();
				}
				os << endl << "Quantity On Hand: " << quantity() << " " << unit() << endl << "Quantity Needed: " << qtyNeeded();
            }
        }
        return os;
    }
	
	istream& AmaProduct::read(istream& istr){
		char buff;
		char buffer[2000];
		double doublebuffer;
		int intbuffer;
		cout << "Sku: ";
		istr >> buffer;
		sku(buffer);
		cout << "Name: ";
		istr >> buffer;
		name(buffer);
		cout << "Unit: ";
		istr >> buffer;
		unit(buffer);
		cout << "Taxed? (y/n): ";
		istr >> buff;
		if (buff == 'y' || buff == 'Y' || buff == 'n' || buff == 'N'){
			if (buff == 'y' || buff == 'Y'){
				taxed(true);
			}
			else{
				taxed(false);
			}
            istr.clear();
            cout << "Price: ";
            istr >> doublebuffer;
            if (istr.fail()){
                err_.message("Invalid Price Entry");
            }
            else{
                err_.clear();
                price(doublebuffer);
                cout << "Quantity On hand: ";
                istr >> intbuffer;
                if(istr.fail()){
                    err_.message("Invalid Quantity Entry");
                }
                else{
                    err_.clear();
                    quantity(intbuffer);
                    cout << "Quantity Needed: ";
                    istr >> intbuffer;
                    if (istr.fail()){
                        err_.message("Invalid Quantity Needed Entry");
                    }
                    else{
                        err_.clear();
                        qtyNeeded(intbuffer);
                    }
                }
            }
		}

		else{
		    istr.setstate(ios::failbit);
            err_.message("Only (Y)es or (N)o are acceptable");
		}
		return istr;
	}

}