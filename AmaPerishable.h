#ifndef SICT_AMAPERISHABLE_H_
#define SICT_AMAPERISHABLE_H_

#include <fstream>
#include <iostream>
#include "AmaProduct.h"
#include "Date.h"
#include "ErrorMessage.h"

using namespace std;

namespace sict
{
    class AmaPerishable : public AmaProduct
    {
    private:
		Date expiry_;
    public:
		AmaPerishable();
		const Date& expiry() const;
		void expiry(const Date &value);
		fstream& store(fstream& file, bool addNewLine = true) const;
		fstream& load(fstream& file);
		ostream& write(ostream& ostr, bool linear) const;
		istream& read(istream& istr);
    };
}

#endif
