#include "pch.h"
#include "Hand.h"


Board::Board()
{
	
}

Board::Board(list<Card>& cards)
{
	_cards = cards;
}


Hand::Hand()
{
}

Hand::Hand(string name, list<Card>& cards)
{
	_name = name;
	_cards = cards;
}



// << overload
//std::ostream& operator<<(std::ostream& os, const Board& ip) {
//	ip.display(os);
//	return os;
//}

//Reads in one line of file data and passes back a product pointer
//Table* readTable(std::ifstream& ifs) {
//	//initialize variables
//	vector<string> columnData;
//	string name;
//	string card;
//	string field;
//	string line;
//	//read in the line and make sure there is no carriage return
//	getline(ifs, line);
//	auto cr = line.find('\r');
//	if (cr != string::npos) {
//		line.erase(cr);
//	}
//	//initialize more variables
//	char delimiter = ' ';
//	int column = 0;
//	int fieldCount = 0;
//	//read in characters from the line 1 by one until there is a space
//	while (column < line.size()) {
//		//if there is a space, skip it and push the word into the vector
//		if (line[column] == delimiter) {
//			column++; //skip delimiter
//			fieldCount++;
//			columnData.push_back(field);
//			field.clear();
//
//		}
//		//add letters to the field
//		field += line[column];
//		column++;
//	}
//	//last field
//	fieldCount++;
//	columnData.push_back(field);
//	field.clear();
//
//	//convert string data to int and double
//	int num = stoi(columnData[0]);
//	double price = stod(columnData[1]);
//
//	//create a return iProduct pointer and chose its type
//	Table* prod = nullptr;
//	//if (columnData.size() > 2) {
//	//	prod = new TaxableProduct(num, price, columnData[2]);
//
//	//}
//	//else {
//	//	prod = new Product(num, price);
//	//}
//	return prod;
//}

FileToTableReader::FileToTableReader(std::ifstream & ifs)
{
	
	_ifs = &ifs;
	_currentLine = "";
	_lineCount = 0;

	nextLine();

}

bool FileToTableReader::nextLine() {
	//read in the line and make sure there is no carriage return
	getline(*_ifs, _currentLine);
	auto cr = _currentLine.find('\r');
	if (cr != string::npos) {
		_currentLine.erase(cr);
	}
	_lineCount++;
}

Table& FileToTableReader::readCurrentLineToTable()
{
	
	vector<string> columnData;
	string field;
	int fieldCount = 0;

	//Step 1: This part parses the line and puts the Hands and the Board into a vector of strings
	//read in characters from the line 1 by one until there is a space
	int column = 0;
	while (column < _currentLine.size()) {
		//if there is a space, skip it and push the word into the vector
		if (_currentLine[column] == _stackDelimiter) {
			column++; //skip delimiter
			fieldCount++;
			columnData.push_back(field);
			field.clear();

		}
		//add letters to the field
		field += _currentLine[column];
		column++;
	}
	//last field
	fieldCount++;
	columnData.push_back(field);
	field.clear();

	//Step 2: This part parses the strings in the vector into their custom class objects (Card, Board, Hand)
	column = 0;
	string name = "";
	string cardString = "";
	list<Card> cards = list<Card>{};
	Board board{};
	list<Hand> hands = list<Hand>{};
	char suit = ' ';
	char rank = ' ';

	//go through the vector
	for (int stackNum = 0; stackNum < fieldCount; stackNum++)
	{
		int placeOfNameDelimiter = columnData[stackNum].find(_endOfNameDelimiter);
		int fieldLength = columnData[stackNum].length();
		name = columnData[stackNum].substr(0, placeOfNameDelimiter - 1);
		cardString = columnData[stackNum].substr(placeOfNameDelimiter + 1, fieldLength - 1);
		
		//parse the cards
		size_t pos = 0;
		string token;
		while ((pos = cardString.find(_cardDelimiter)) != string::npos) {
			token = cardString.substr(0, pos);
			cards.emplace_front(Card(token[0], token[1]));
			cardString.erase(0, pos + 1);
		}

		//Now that we have all of the objects to create a Board or a Hand, do it
		if (name == "Board") {
			board = Board(cards);
		}
		else{
			hands.emplace_front(Hand(name, cards));
		}
		

	}
	
	//Step 3: Create the table and return it
	Table table = Table(board, hands);

	return table;
}

Table::Table()
{
	_tableIsReady = false;
	_anyLowHandsExist = false;
	_board = {};
	_hands = {};
	_combinations = {};
}

Table::Table(Board & board, list<Hand>& hands)
{
	_board = board;
	_hands = hands;
	for (auto &hand : hands) {
		_combinations.emplace_front(Combination(hand, board));
	}
	_tableIsReady = true;
	for (auto &combination : _combinations) {
		if (combination.hasLowHand()) {
			_anyLowHandsExist = true;
		}
	}

}

Combination::Combination(Hand & hand, Board & board)
{
	_hand = hand;
	_board = board;

}

void Card::setRank(char rank)
{
	switch (rank)
	{
	case '2':
		_rank = 2;
		break;
	case '3':
		_rank = 3;
		break;
	case '4':
		_rank = 4;
		break;
	case '5':
		_rank = 5;
		break;
	case '6':
		_rank = 6;
		break;
	case '7':
		_rank = 7;
		break;
	case '8':
		_rank = 8;
		break;
	case '9':
		_rank = 9;
		break;
	case 'T':
		_rank = 10;
		break;
	case 'J':
		_rank = 11;
		break;
	case 'Q':
		_rank = 12;
		break;
	case 'K':
		_rank = 13;
		break;
	case 'A':
		_rank = 14;
		_isAce = true;
		break;
	default:
		throw "Uknown Rank";
		break;

	}
}

void Card::setSuit(char suit)
{
	switch (suit)
	{
	case 'c':
	case 'C':
		_suit = c;
		break;
	case 'd':
	case 'D':
		_suit = d;
		break;
	case 's':
	case 'S':
		_suit = s;
		break;
	case 'h':
	case 'H':
		_suit = h;
		break;
	default:
		throw "Uknown Suit";
		break;
	}
}

Card::Card(char rank, char suit)
{
	_rankName = rank;
	setSuit(suit);
	setRank(rank);
}
