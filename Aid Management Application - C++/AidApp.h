// Final Project Milestone 6
// Version 1.0
// Date	04/11/2016
// Author	Egor Dourasov
// Description: AidApp.h - Date class definition
/////////////////////////////////////////////////////////////////

#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "AmaPerishable.h"


namespace sict{
	class AidApp{
	private:
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		fstream datafile_; 
		int noOfProducts_;
		
		//Private Member Functions
		void pause() const;
		AidApp(const AidApp& ap) = delete;
		AidApp& operator=(const AidApp& ap) = delete;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts()const;
		int searchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
		

	protected:
	
	public:
		AidApp(const char* filename);
		~AidApp();
		int run();





	};
}
#endif
