#include "pch.h"
#include "Hand.h"


Board::Board()
{
	
}

Board::Board(vector<Card> cards)
{
	_cards = cards;
}


Hand::Hand()
{
}

Hand::Hand(string name, vector<Card> cards)
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
	vector<Card> cards = vector<Card>{};
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
			cards.push_back(Card(token[0], token[1]));
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

//Hard to unit test - need to refactor
void Combination::compareAndSet(vector<Card> newHand)
{
	bool cont = true;
	HighHandRank newRank;

	//First - figure out the highest rank
	if (cont && isStraightFlush(newHand) ){
		newRank = StraightFlush;
		cont = false;
	}
	if (cont && isFourOfAKind(newHand)) {
		newRank = FourOfAKind;
		cont = false;
	}
	if (cont && isFullHouse(newHand)) {
		newRank = FullHouse;
		cont = false;
	}
	if (cont && isFlush(newHand)) {
		newRank = Flush;
		cont = false;
	}
	if (cont && isStraight(newHand)) {
		newRank = Straight;
		cont = false;
	}
	if (cont && isThreeOfAKind(newHand)) {
		newRank = ThreeOfAKind;
		cont = false;
	}
	if (cont && isTwoPair(newHand)) {
		newRank = TwoPair;
		cont = false;
	}
	if (cont && isOnePair(newHand) ){
		newRank = OnePair;
		cont = false;
	}
	if (cont && isHighCard(newHand)) {
		newRank = HighCard;
		cont = false;
	}
	
	//Second - compare to existing
	if (isTheHighBetterThan(newHand, newRank) == Lose) {
		_highHand = newHand;
		_highRank = newRank;
	}
	
	//Check if this is a low hand, and if it's better than existing
	if (isLowHand(newHand)) {
		if (isTheLowBetterThan(newHand) == Lose) {
			_lowHand = newHand;
			_hasLowHand = true;
		}
	}
}

Combination::Combination(Hand & hand, Board & board)
{
	_hand = hand;
	_board = board;
	vector<Card> currentCombo = {};

	//Board has 10 possible combinations of 3 cards
	//Hand has 6 possible combinations of 2 cards
	//Making a loop to iterate through all 60 possible combination

	//The ugly loop-in-a-loop-in-a-loop-in-a-loop-in-a-loop :)
	for (int i = 0; i <= 2; i++) { //Board card 1
		for (int j = i + 1; j <= 3; j++) { //Board card 2
			for (int k = j + 1; k <= 4; k++) { //Board card 3
				for (int m = 0; m <= 2; m++) { //Hand card 1
					for (int z = m + 1; z <= 3; z++) { //Hand card 2
						currentCombo.clear();
						currentCombo.push_back(hand.getCards()[z]);
						currentCombo.push_back(hand.getCards()[m]);
						currentCombo.push_back(hand.getCards()[k]);
						currentCombo.push_back(hand.getCards()[j]);
						currentCombo.push_back(hand.getCards()[i]);

						compareAndSet(currentCombo);

					}
				}
			}
		}
	}

}

Comparison Combination::isTheHighBetterThan(vector<Card> opponentHand, HighHandRank opponentRank)
{
	Comparison result = Tie;

	if (_highRank > opponentRank) {
		result = Win;
	}
	else if (_highRank < opponentRank){
		result = Lose;
	}
	else if (_highRank == opponentRank) {

	}
	
	return result;
}

Comparison Combination::isTheLowBetterThan(vector<Card> opponentHand)
{
	Comparison result = Tie;
	int highestOpponentRank = 0;
	int highestOwnRank = 0;

	for (auto &card : _lowHand) {
		if (card.getRank() > highestOwnRank) {
			highestOwnRank = card.getRank();
		}
	}
	for (auto &card : opponentHand) {
		if (card.getRank() > highestOpponentRank) {
			highestOpponentRank = card.getRank();
		}
	}

	if (highestOpponentRank <= 8 && highestOpponentRank < highestOwnRank) {
		result = Lose;
	}
	else if (highestOwnRank <= 8 && highestOwnRank < highestOpponentRank) {
		result = Win;
	}
	else if (highestOwnRank <= 8 && highestOwnRank == highestOpponentRank) {
		result = Tie;
	}


	return result;
}

Comparison Combination::straightTieBreaker(vector<Card> opponentHand)
{
	Comparison result = Tie;
	int highestHighAceOpponentRank = 0;
	int highestLowAceOpponentRank = 0;

	int highestHighAceOwnRank = 0;
	int highestLowAceOwnRank = 0;

	for (auto &card : _lowHand) {
		if (card.getRank() > highestHighAceOwnRank) {
			highestHighAceOwnRank = card.getRank();
			if (!card.isAce()) {
				highestLowAceOwnRank = card.getRank();
			}
		}
	}
	for (auto &card : opponentHand) {
		if (card.getRank() > highestHighAceOpponentRank) {
			highestHighAceOpponentRank = card.getRank();
			if (!card.isAce()) {
				highestLowAceOpponentRank = card.getRank();
			}
		}
	}

	if (highestLowAceOwnRank < highestLowAceOpponentRank) {
		result = Lose;
	}
	else if (highestLowAceOwnRank > highestLowAceOpponentRank) {
		result = Win;
	}
	else if (highestLowAceOwnRank == highestLowAceOpponentRank) {
		result = Tie;
	}

	
	return Comparison();
}

Comparison Combination::fourOfAKindTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::fullHouseTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::flushTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::threeOfAKindTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::twoPairTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::onePairTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
}

Comparison Combination::highCardTieBreaker(vector<Card> opponentHand)
{
	return Comparison();
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

bool isFlush(vector<Card> cards)
{
	bool result = true;
	Suit suit = cards[0].getSuit();
	for (auto &card : cards) {
		if (card.getSuit() != suit) {
			result = false;
		}
	}
	return result;
}

bool isStraight(vector<Card> cards)
{
	bool highAceResult = true;
	bool lowAceResult = true;
	bool finalResult = false;
	vector<int> highRankAceRow = {};
	vector<int> lowRankAceRow = {};
	int vectorSize = 0;

	//if there is no ace, or it's the highest rank
	for (auto &card : cards) {
		if (card.isAce()) {
			lowRankAceRow.push_back(1);
		}
		else {
			highRankAceRow.push_back(card.getRank());
		}
		vectorSize++;
	}
	sort(highRankAceRow.rbegin(), highRankAceRow.rend());
	sort(lowRankAceRow.rbegin(), lowRankAceRow.rend());
	for (int i = 0; i < vectorSize - 1; i++) {
		if (abs(highRankAceRow[i] - highRankAceRow[i + 1]) != 1) {
			highAceResult = false;
		}
		if (abs(lowRankAceRow[i] - lowRankAceRow[i + 1]) != 1) {
			lowAceResult = false;
		}
	}

	if (highAceResult || lowAceResult) {
		finalResult = true;
	}

	return finalResult;
}

bool isStraightFlush(vector<Card> hand)
{
	bool result = false;
	if (isFlush(hand) && isStraight(hand)) {
		result = true;
	}
	return result;
}

bool isFourOfAKind(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	for (auto &card : hand) {
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if (mapOfCardCounts[card.getRank()] == 4) {
			result = true;
		}
	}
	return result;
}

bool isFullHouse(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	int cardNumber = 0;
	for (auto &card : hand) {
		cardNumber++;
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if ((mapOfCardCounts[card.getRank()] == 3 || mapOfCardCounts[card.getRank()] == 2) 
			&& mapOfCardCounts.count == 2 && cardNumber == 5) {
			result = true;
		}
		
	}
	return result;
}

bool isTwoPair(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	int cardNumber = 0;
	for (auto &card : hand) {
		cardNumber++;
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if ((mapOfCardCounts[card.getRank()] == 2 )
			&& mapOfCardCounts.count == 3 && cardNumber == 5) {
			result = true;
		}

	}
	return result;
}

bool isThreeOfAKind(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	for (auto &card : hand) {
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if (mapOfCardCounts[card.getRank()] == 3 && mapOfCardCounts.count == 3) {
			result = true;
		}
	}
	return result;
}

bool isOnePair(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	for (auto &card : hand) {
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if (mapOfCardCounts[card.getRank()] == 2 && mapOfCardCounts.count == 4) {
			result = true;
		}
	}
	return result;
}

bool isHighCard(vector<Card> hand)
{
	bool result = false;
	map<int, int> mapOfCardCounts;
	for (auto &card : hand) {
		if (mapOfCardCounts.find(card.getRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(card.getRank(), 1);
		}
		else
		{
			mapOfCardCounts[card.getRank()]++;

		}
		if (mapOfCardCounts[card.getRank()] == 1 && mapOfCardCounts.count == 5) {
			result = true;
		}
	}
	return result;
}

bool isLowHand(vector<Card> hand)
{
	bool result = true;

	map<int, int> mapOfCardCounts;
	for (auto &card : hand) {
		int cardRank = card.getRank();
		if (card.isAce()) {
			cardRank = 1;
		}
		
		if (mapOfCardCounts.find(cardRank) == mapOfCardCounts.end()) {
			mapOfCardCounts.insert(cardRank, 1);
		}
		else
		{
			mapOfCardCounts[cardRank]++;

		}

		if (cardRank > 8) {
			result = false;
		}

	}

	if (mapOfCardCounts.count != 5) {
		result = false;
	}




	return result;
}








