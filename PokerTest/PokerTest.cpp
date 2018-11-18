// PokerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Hand.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}
	
	ifstream fs = ifstream(argv[1]);


	FileToTableReader reader = FileToTableReader(fs);

	Table table = reader.readCurrentLineToTable();
	
	//TODO - do a loop to read in the lines using reader.nextLine()

	//TODO - output the results to a file

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}

