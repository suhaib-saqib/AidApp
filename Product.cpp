#include <cstring>
#include "Product.h"
#include "general.h"

using namespace std;

namespace sict
{
	Product::Product(){
	   sku_[0] = '\0';
	   name_ = nullptr;
	   price_ = 0;
	   quantity_ = 0;
	   qtyNeeded_ = 0;
   }
   
	Product::Product::Product(const char* sku, const char* name, bool taxed, double price, int qtyNeeded){
	   strcpy(sku_, sku);
	   name_ = new char[strlen(name) + 1];
	   strcpy(name_,name);
	   price_ = price;
	   quantity_ = 0;
	   qtyNeeded_ = qtyNeeded;
	   taxed_ = taxed;
   }
   
    Product::~Product(){
	   delete[] name_;
	   name_ = nullptr;
   }
   
    Product::Product(const Product &p){
	   price_ = p.price_;
	   taxed_ = p.taxed_;
	   qtyNeeded_ = p.qtyNeeded_;
	   strcpy(sku_,p.sku_);
	   name_ = nullptr;
	   name_ = new char[strlen(p.name_) + 1];
	   strcpy(name_,p.name_);
	   quantity_ = p.quantity_;
   }
   
    Product& Product::operator=(const Product &p){
	   if (this != &p){
		   price_ = p.price_;
		   taxed_ = p.taxed_;
		   qtyNeeded_ = p.qtyNeeded_;
		   strcpy(sku_,p.sku_);
		   quantity_ = p.quantity_;
		   
		   if (p.name_ != nullptr){
			   name_ = new char[strlen(p.name_) +1];
			   strcpy(name_, p.name_);
		   }
		   else{
			   name_ = nullptr;
		   }
	   }
	   return *this;
   }
   
	void Product::sku(const char* sk){
		strncpy(sku_, sk, MAX_SKU_LEN + 1);
	}
	
	void Product::price(double pr){
		price_ = pr;
	}
	
	void Product::name(const char* nm){
		delete [] name_;
		name_ = new char[strlen(nm) +1 ];
		strcpy(name_,nm);
	}
		
	void Product::taxed(bool tx){
		taxed_ = tx;
	}
	
	void Product::quantity(int qt){
		quantity_ = qt;
	}	
	
	void Product::qtyNeeded(int qtn){
		qtyNeeded_ = qtn;
	}
   
	const char* Product::sku() const{
	   return sku_;
	}
		
	double Product::price() const{
		return price_;
	}
		
	const char* Product::name() const{
		return name_;
	}
		
	bool Product::taxed() const{
		return taxed_;
	}
		
	int Product::quantity() const{
		return quantity_;
	}
		
	int Product::qtyNeeded() const{
		return qtyNeeded_;
	}
   
	double Product::cost() const{
		if (taxed() == true){
			return price_ + price_ * TAX;
		}
		else{
			return price_;
		}
	}
	
	bool Product::isEmpty() const{
		if (sku_[0] == '\0' && name_ == nullptr && price_ == 0 && quantity_ == 0 && qtyNeeded_ == 0){
			return true;
		}
		else
			return false;
	}
	
	bool Product::operator==(const char* sku)const{
        if(strcmp(sku_,sku))
            return false;
		else
			return true;
    }
	
	int Product::operator+=(int b){
        quantity_ += b;
        return quantity_;
    }
		
	int Product::operator-=(int c){
        quantity_ -= c;
        return quantity_;
    }
	
	double operator+=(double &o, const Product& p){
        o += p.cost() * p.quantity();
        return o;
    }
		
	std::ostream& operator<<(std::ostream& ostr, const Product& p){
        p.write(ostr, true);
		return ostr;
    }
    
    std::istream& operator>>(std::istream& istr, Product& p){
        p.read(istr);
		return istr;
    }
}