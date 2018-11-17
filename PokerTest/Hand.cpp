#include "pch.h"
#include "Hand.h"
#include <list>


Board::Board(list<Card>& cards) 
{
}
Board::~Board() {}

Hand::Hand(string name, list<Card>& cards)
{
}


Hand::~Hand()
{
}

// << overload
//std::ostream& operator<<(std::ostream& os, const Board& ip) {
//	ip.display(os);
//	return os;
//}

//Reads in one line of file data and passes back a product pointer
Table* readTable(std::ifstream& ifs) {
	//initialize variables
	vector<string> columnData;
	string field;
	string line;
	//read in the line and make sure there is no carriage return
	getline(ifs, line);
	auto cr = line.find('\r');
	if (cr != string::npos) {
		line.erase(cr);
	}
	//initialize more variables
	char delimiter = ' ';
	int column = 0;
	int fieldCount = 0;
	//read in characters from the line 1 by one until there is a space
	while (column < line.size()) {
		//if there is a space, skip it and push the word into the vector
		if (line[column] == delimiter) {
			column++; //skip delimiter
			fieldCount++;
			columnData.push_back(field);
			field.clear();

		}
		//add letters to the field
		field += line[column];
		column++;
	}
	//last field
	fieldCount++;
	columnData.push_back(field);
	field.clear();

	//convert string data to int and double
	int num = stoi(columnData[0]);
	double price = stod(columnData[1]);

	//create a return iProduct pointer and chose its type
	Table* prod = nullptr;
	if (columnData.size() > 2) {
		prod = new TaxableProduct(num, price, columnData[2]);

	}
	else {
		prod = new Product(num, price);
	}
	return prod;
}