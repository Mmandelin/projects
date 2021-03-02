#include "Utility.h"
#include "life.h"
#include <iostream>
#include <fstream>
#include "windows.h"
using namespace std;

int main() // Program to play Conway’s game of Life.
/* Pre: The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in the configuration of living cells according to the rules for the game of Life.
Uses: The class Life and its methods initialize( ), print( ), and update( ).
The functions instructions( ), user says yes( ). */
{
	Life configuration;

	instructions();

	asetaKoko();	//lisätty

	configuration.initialize();
	
	while (true) {
		configuration.print();
		configuration.update();

		Sleep(1000); //1000ms = 1s
	}
	/*
	cout << "Continue viewing new generations? " << endl;
	while (user_says_yes()) {
		configuration.update();
		configuration.print();
		cout << "Continue viewing new generations? " << endl;
	} */

	configuration.save();

}

