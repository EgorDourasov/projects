#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <iomanip>
using namespace std;

class FileToTableReader {
	std::ifstream* _ifs;
	
	int _lineCount;
	
	string _currentLine;
	char _stackDelimiter = ' ';
	char _endOfNameDelimiter = ':';
	char _cardDelimiter = '-';
	
public:
	FileToTableReader(std::ifstream& ifs);
	~FileToTableReader() {}
	void display();
	
	bool nextLine();
	Table& readCurrentLineToTable();

};

//Represents the table that the session is being played on
class Table {
	Board _board;
	list<Hand> _hands;
	list<Combination> _combinations;
	bool _anyLowHandsExist;
	bool _tableIsReady;

public:
	Table();
	Table(Board& board, list<Hand>& hands);
	~Table() {}

	void setBoard(Board& board);
	void addHand(Hand& hand);
	void addHands(list<Hand>& hands);

	Combination& determineHighWinner(list<Combination>& combinations);
	Combination& determineLowWinner(list<Combination>& combinations);

	bool anyLowHandsExist() { return _anyLowHandsExist; }

};


class Board {
	list<Card> _cards = {};
public:
	Board();
	Board(list<Card>& cards);
	~Board() {}

	list<Card>& getCards() { return _cards; }
};

//Base Hand Class
class Hand {
	string _name = "";
	list<Card> _cards = {};
public:
	Hand();
	Hand(string name, list<Card>& cards);
	~Hand() {}

	string& getName() { return _name; }
	list<Card>& getCards() { return _cards; }
};




class Combination  {
	list<Card> _highHand;
	list<Card> _lowHand;
	bool _hasLowHand;
	Hand _hand;
	Board _board;
	HighHandRank _highRank;

public: 
	Combination(Hand& hand, Board& board);
	~Combination() {}

	list<Card> getHighHand() { return _highHand; }
	list<Card> getLowHand() { return _lowHand; }
	bool hasLowHand() { return _hasLowHand; }

	string& getStringifiedHighRank();
	string& getStgringifiedLowSequence();

};

class Card {
	Suit _suit;
	char _rankName;
	int _rank;
	bool _isAce;

	void setRank(char rank);
	void setSuit(char suit);

public:
	Card(char rank, char suit);
	~Card() {}

	int getRank() { return _rank; }
	Suit& getSuit() { return _suit; }
	bool isAce() { return _isAce; }
};


enum Suit {
	c,
	d,
	s,
	h
};

enum HighHandRank {
	HighCard,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush

};

//helpers
//std::ostream& operator<<(std::ostream& os, const Board& ip);
//Table* readTable(std::ifstream& ifs);