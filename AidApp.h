#ifndef SICT_AIDAPP_H_
#define SICT_AIDAPP_H_
#include "AmaPerishable.h"
#include "AmaProduct.h"
using namespace std;
namespace sict
{
    class AidApp
    {
		private:
			char filename_[256];
			Product* product_[MAX_NO_RECS];
			fstream datafile_;
			int noOfProducts_;
			void pause() const;
			int menu();
			void loadRecs();
			void saveRecs();
			void listProducts()const;
			int SearchProducts(const char* sku)const;
			void addQty(const char* sku);
			void addProduct(bool isPerishable);
        public:
			AidApp(const char* filename);
			int run();
    };
}

#endif