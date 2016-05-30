// Final Project Milestone 6
// Version 1.0
// Date	04/11/2016
// Author	Egor Dourasov
// Description: AidApp.cpp - Date class definition
/////////////////////////////////////////////////////////////////

#include "AidApp.h"



namespace sict{


	//The only constructor
	AidApp::AidApp(const char* filename){
		//validate that filename is not too long, and then set the filename
		if (strlen(filename) < 256){
			strcpy(filename_, filename);
			
			//set all Product pointers to nullpointer
			for (int i = 0; i < MAX_NO_RECS; i++){
				product_[i] = nullptr;
			}
			
			//assign product counter and loads the file
			noOfProducts_ = 0;
			loadRecs();
		}
		else {
			cout << "Filename too long";
			
		}
	}

	//default destructor
	AidApp::~AidApp(){}
	
	//pause
	void AidApp::pause() const{
		
		cout << "Press Enter to continue...";
		cin.ignore(1000, '\n');
		cout << endl;
		
	}

	//private member functions

	//main menu - mostly text and an input prompt with validation
	int AidApp::menu(){
		int ret = 1;
		
		cout << "Disaster Aid Supply Management Program"<< endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> ret;
		while (getchar() != '\n');
		if (ret == 1 || ret == 2 || ret == 3 || ret == 4 || ret == 5 || ret == 0) return ret;
		else return -1;
		
	}

	//loads records from file specified in the constructor
	void AidApp::loadRecs(){
		fstream fin(filename_);
		char per;
		if (fin.is_open()){
			int i = 0;
			while (!fin.eof())
			{
				per = ' ';
				fin.get(per);
				fin.ignore(1);
				
				//Perishable
				if (per == 'P'){
					product_[i] = new AmaPerishable;
					product_[i]->load(fin);
					fin.ignore(2000, '\n');

					i++;
				}
				//Non-Perishable
				if (per == 'N'){
					product_[i] = new AmaProduct;
					product_[i]->load(fin);
					fin.ignore(2000, '\n');

					i++;
				}
				

			}
			noOfProducts_ = i;
			fin.close();
		}
		else{
			fin.clear();
			fin.close();
			fstream fout(filename_);
			fout.close();
		}

	}

	//saves the records to a file specified in the constructor
	void AidApp::saveRecs(){
		fstream fout(filename_);
		if (fout.is_open()){
			for (int i = 0; i <= noOfProducts_; i++){
				product_[i]->store(fout, true);
			}
		}
		else{
			cout << "Bad File" << endl;
		}
		fout.close();
	}

	//prints a stylized list of perishable and regular products
	void AidApp::listProducts()const{
		double totalCost = 0;
		cout << endl;
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		for (int i = 0; i < noOfProducts_; i++){
			cout << setw(4) << setfill(' ') << (i + 1) << right << " | ";
			cout << *product_[i] << endl;
			if ((i + 1) % 10 == 0) {
				pause();
				
			}
			totalCost += *product_[i];
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << fixed << setprecision(2) << totalCost << endl;
		cout << endl;

	}

	//searches the product array based on the sku value. Returns row# if found, and -1 if not
	int AidApp::searchProducts(const char* sku)const{
		int ret = -1;
		for (int i = 0; i < noOfProducts_; i++){
			if (*product_[i] == sku) ret = i;
		}
		return ret;
	}

	//Prompts for a quantity to be added and updates the product based on its sku number
	void AidApp::addQty(const char* sku){
		int b;
		//check if product exists and assign its line# to i
		int i = searchProducts(sku);
		if (i == -1){
			cout << "Not found!" << endl;
		}
		else{
			//print in non-linear format
			product_[i]->write(cout, false);
			cout << endl << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> b;
			while (getchar() != '\n');
			//validate input
			if (cin.fail()) cout << "Invalid quantity value!" << endl;
			else {
				//validate amount and either add the amount or...
				int c = (product_[i]->qtyNeeded() - product_[i]->quantity());
				if (b <= c){
					*product_[i]+=b;
				}
				//... add as much as possible and say how many over you were
				else{
					*product_[i] += c;
					cout << "Too many items; only " 
						<< (product_[i]->qtyNeeded() - product_[i]->quantity())
						<< " is needed, please return the extra "
						<< (b - c)
						<< " items." << endl ;
				}
				cout << endl << "Updated!" << endl;
			}
			
		}


	}

	//adds a product to the product array
	void AidApp::addProduct(bool isPerishable){
		
		if (isPerishable == true){
			product_[noOfProducts_] = new AmaPerishable();
		}
		else{
			product_[noOfProducts_] = new AmaProduct();
		}
		
		product_[noOfProducts_]->read(cin);
		saveRecs();
		cout << endl << "Product added" << endl;

	}


	//public member functions:
	
	//grabs the product array and calls the main menu
	//this and the constructor are the only functions available to the client
	int AidApp::run(){
		int choice;
		int row = -1;
		char sku_n[MAX_SKU_LEN + 1];
		do {
			choice = menu();
			 switch (choice){
			 //list of products
			 case 1:
				 listProducts();
				 pause();
				 break;
			 //specific product
			 case 2:
				 cout << endl;
				 cout << "Please enter the SKU: ";
				 cin >> sku_n;
				 while (getchar() != '\n');
				 cout << endl;
				 row = searchProducts(sku_n);
				 if (row == -1) cout << "Not found!" << endl;
				 else{
					 product_[row]->write(cout, false);
					 cout << endl << endl;
				 }
				 pause();
				 break;
			 //add non-perishable
			 case 3:
				 cout << endl;
				 addProduct(false);
				 loadRecs();
				 cout << endl;
				 break;
			//add perishable
			 case 4:
				 cout << endl;
				 addProduct(true);
				 loadRecs();
				 cout << endl;
				 break;
			 //add quantity
			 case 5:
				 cout << endl;
				 cout << "Please enter the SKU: ";
				 cin >> sku_n;
				 cout << endl;
				 row = searchProducts(sku_n);
				 if (row == -1) cout << "Not found!" << endl << endl;
				 else {
					 addQty(sku_n);
					 cout << endl;
				 }
				 
				 break;
			 //exit
			 case 0:
				 cout << endl << "Goodbye!!" << endl;
				 break;
			 //bad selection
			 default:
				 cout << "===Invalid Selection, try again.===" << endl;
				 pause();
			 }
			 
		} while (choice != 0);
		
		return 0;
	}





}