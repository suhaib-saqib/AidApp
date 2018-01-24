#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"

using namespace std;

namespace sict
{
	AidApp::AidApp(const char* filename){
		strcpy(filename_,filename);
		int i;
		for (i=0; i < MAX_NO_RECS; i++){
			product_[i] = nullptr;
		}
		noOfProducts_ = 0;
		loadRecs();
	}
	
	void AidApp::pause() const{
		cout << "Press Enter to continue..." << endl;
        cin.ignore(2000, '\n');
	}
	
	int AidApp::menu(){
		int select = -1;
        cout << "Disaster Aid Supply Management Program" << endl;
        cout << "1- List products" << endl;
        cout << "2- Display product" << endl;
        cout << "3- Add non-perishable product" << endl;
        cout << "4- Add perishable product" << endl;
        cout << "5- Add to quantity of purchased products" << endl;
        cout << "0- Exit program" << endl;
        cout << "> ";
        cin >> select;
        if(cin.fail()){
            cin.clear();
        }
        cin.ignore(2000, '\n');
        if(select < 0 || select > 5){
            select = -1;
        }
        cout << endl;
        return select;
    }
	
	void AidApp::loadRecs(){
		noOfProducts_ = 0;
		datafile_.open(filename_, ios::in);
		if (datafile_.fail()){
			datafile_.clear();
            datafile_.close();
            datafile_.open(filename_, ios::out);
            datafile_.close();
		}
		else{
			char prodType;
			while(datafile_.fail() == false)
				delete product_[noOfProducts_];
                prodType = datafile_.get();
				if(prodType == 'P'){
                    product_[noOfProducts_] = new AmaPerishable();
                }
                else if(prodType == 'N'){
                    product_[noOfProducts_] = new AmaProduct();
                }
                if(prodType == 'P' || prodType == 'N'){
                    datafile_.ignore();
                    product_[noOfProducts_]->load(datafile_);
                    noOfProducts_ = noOfProducts_ + 1;
                }
        }
        datafile_.close();
    }

	void AidApp::saveRecs(){
		datafile_.open(filename_, ios::out);
		int i;
		for (i=0; i < noOfProducts_; i++){
			product_[i]->store(datafile_);
		}
		datafile_.close();
	}
	
	void AidApp::listProducts()const{
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		int i, lines = 0;
		double cost = 0;
		for (i = 0; i < noOfProducts_; i++){
			int r= i+1;
			lines++;
			cout.fill(' ');
			cout << setw(4) << right <<  r << " | " << *product_[i] << endl;
			if (lines == DISPLAY_LINES){
				lines = 0;
				pause();
			}
			cost += *product_[i];
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << setprecision(2) << cost << endl;
	}
	
	int AidApp::SearchProducts(const char* sku)const{
		int i, f;
		bool found = false;
		for (i = 0; i < noOfProducts_; i++){
			if (*product_[i] == sku){
				found = true;
				f = i;
			}
		}
		if (found == true){
			return f;
		}
		else{
			return -1;
		}
	}
	
	void AidApp::addQty(const char* sku){
		int search = SearchProducts(sku);
		if (search == -1){
			cout << "Not found!" << endl;
		}
		else{
			int quant;
			product_[search]->write(cout,false);
			cout<< "Please enter the number of purchased items: ";
			cin >> quant;
			if (cin.fail()){
				cin.clear();
				cout << "Invalid quantity value! " << endl;
			}
			else{
				int req = product_[search]->qtyNeeded() - product_[search]->quantity();
				if (quant <= req){
					*product_[search] += quant;
				}
				else{
					cout << "Too many items; only " << req << " is needed, please return the extra " << quant - req << " items." << endl;
                    *product_[search] += req;
				}
				saveRecs();
                cout << "Updated!" << endl;
			}
			 cin.ignore(2000, '\n');
		}
	}
	
	void AidApp::addProduct(bool isPerishable){
		Product* P;
		if (isPerishable){
			P = new AmaPerishable;
		}
		else{
			P = new AmaProduct;
		}
		cin >> *P;
		if (cin.fail()){
			cin.clear();
            cin.ignore(2000, '\n');
            cout << *P << endl;
		}
		else{
				product_[noOfProducts_++] = P;
				saveRecs();
				cout << "Product added" << endl;
				product_[noOfProducts_];
		}
		cout << endl;
	}
	
	int AidApp::run(){
		int choice;
		do{
			choice = menu();
			if (choice == 1){
				listProducts();
			}
			else if(choice == 2){
				cout << "Please enter the SKU: ";
				char sku[MAX_SKU_LEN];
				cin >> sku;
				int search;
				search = SearchProducts(sku);
				if (search >= 0){
					product_[search]->write(cout, false) << endl;
					pause();
				}
				else{
					cout << "Not found!" << endl;
				}
			}
			else if(choice == 3){
				addProduct(false);
                loadRecs();
			}
			else if(choice == 4){
				addProduct(true);
                loadRecs();
			}
			else if(choice == 5){
				char sku[MAX_SKU_LEN];
				cin >> sku;
				addQty(sku);
			}
			else if(choice == 0){
				cout << "Goodbye!!";
			}
			else{
				cout << "===Invalid Selection, try again.===";
				pause();
			}
				
		}while (choice != 0);
		return 0;
	}
}