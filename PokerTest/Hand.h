#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
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
	vector<Card> _cards = {};
public:
	Board();
	Board(vector<Card> cards);
	~Board() {}

	vector<Card>& getCards() { return _cards; }
};

//Base Hand Class
class Hand {
	string _name = "";
	vector<Card> _cards = {};
public:
	Hand();
	Hand(string name, vector<Card> cards);
	~Hand() {}

	string& getName() { return _name; }
	vector<Card> getCards() { return _cards; }
};




class Combination  {
	vector<Card> _highHand = {};
	vector<Card> _lowHand = {};
	bool _hasLowHand = false;
	Hand _hand = {};
	Board _board = {};
	HighHandRank _highRank = HighCard;


	void compareAndSet(vector<Card> newHand);


public: 
	Combination(Hand& hand, Board& board);
	~Combination() {}

	vector<Card> getHighHand() { return _highHand; }
	vector<Card> getLowHand() { return _lowHand; }
	bool hasLowHand() { return _hasLowHand; }

	string& getStringifiedHighRank();
	string& getStgringifiedLowSequence();

	Comparison isTheHighBetterThan(vector<Card> opponentHand, HighHandRank opponentRank);
	Comparison isTheLowBetterThan(vector<Card> opponentHand);

	Comparison straightTieBreaker(vector<Card> opponentHand);
	Comparison fourOfAKindTieBreaker(vector<Card> opponentHand);
	Comparison fullHouseTieBreaker(vector<Card> opponentHand);
	Comparison flushTieBreaker(vector<Card> opponentHand);
	Comparison threeOfAKindTieBreaker(vector<Card> opponentHand);
	Comparison twoPairTieBreaker(vector<Card> opponentHand);
	Comparison onePairTieBreaker(vector<Card> opponentHand);
	Comparison highCardTieBreaker(vector<Card> opponentHand);

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

enum Comparison {
	Win,
	Lose,
	Tie
};

//helpers
//std::ostream& operator<<(std::ostream& os, const Board& ip);
//Table* readTable(std::ifstream& ifs);


bool isFlush(vector<Card> hand);
bool isStraight(vector<Card> hand);
bool isStraightFlush(vector<Card> hand);
bool isFourOfAKind(vector<Card> hand);
bool isFullHouse(vector<Card> hand);
bool isThreeOfAKind(vector<Card> hand);
bool isTwoPair(vector<Card> hand);
bool isOnePair(vector<Card> hand);
bool isHighCard(vector<Card> hand);
bool isLowHand(vector<Card> hand);


