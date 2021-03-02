#include <iostream>
#include "life.h"
#include "Utility.h"
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

static int uusiMAXrow;
static int uusiMAXcol;

void Life::save() {
	cout << "Save current game situation to file?" << endl;
	if (user_says_yes()) {
		ofstream SavedGame("SavedGame.txt");

		if (SavedGame.is_open()) {

			for (int i = 1; i <= uusiMAXrow; i++) {
				for (int j = 1; j <= uusiMAXcol + 1; j++) {

					//SavedGame << grid[i][j];
					if (grid[i][j] == '*' || grid[i][j] == ' ' || grid[i][j] == '\n') {
						SavedGame << grid[i][j];
					}
					
				}
			}
		}
		else {
			cout << "Failed to open the file for saving. Exiting." << endl;
			exit(1);
		}

		SavedGame.close();
	}
}

void asetaKoko() {
	
	cout << "Give grid size(max size 20 by 60): " << endl;
	cin >> uusiMAXrow >> uusiMAXcol;
	while (uusiMAXrow > maxrow && uusiMAXcol > maxcol && uusiMAXrow < 1 && uusiMAXcol < 1) {
		if (uusiMAXrow > maxrow || uusiMAXrow < 1)
			cout << "Row " << uusiMAXrow << " is out of range." << endl;
		else
			cout << "Column " << uusiMAXcol << " is out of range." << endl;
		cin >> uusiMAXrow >> uusiMAXcol;
	}
}

int Life::neighbor_count(int row, int col)
/* Pre: The Life object contains a configuration, and the coordinates row and col
define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned. */
{
	int sisaan1 = row;
	int sisaan2 = col;
	int i, j;
	int count = 0;
	for (i = row - 1; i <= row + 1; i++)
		for (j = col - 1; j <= col + 1; j++)
			if (grid[i][j] == '*') { //lisätty
				count += 1;
			}

	if (grid[sisaan1][sisaan2] == '*') { //lisätty
		count -= 1;
	}
	// Reduce count, since cell is not its own neighbor.
	return count;
}

void Life::update()
/* Pre: The Life object contains a configuration.
Post: The Life object contains the next generation of configuration. */
{

		int row, col;
		char new_grid[maxrow + 2][maxcol + 2];
		for (row = 1; row <= uusiMAXrow; row++)
			for (col = 1; col <= uusiMAXcol; col++)
				switch (neighbor_count(row, col)) {
				case 2:		//oli 2
					new_grid[row][col] = grid[row][col];
					// Status stays the same.
					break;
				case 3:		//oli 3, säädä näitä tai naapurin laskentaa sellaiseksi, että sopiva numero palaa(nyt tulee -1, 0, 1, 2) kopioi numeroilla toimiva peli toiseen projuun ja katso paluu arvot!
					new_grid[row][col] = '*'; // Cell is now alive.
					break;
				default:
					new_grid[row][col] = ' '; // Cell is now dead.
				}
		for (row = 1; row <= uusiMAXrow + 1; row++)
			for (col = 1; col <= uusiMAXcol + 1; col++)
				if (new_grid[row][col] == '*' || new_grid[row][col] == ' ') {
					grid[row][col] = new_grid[row][col];
				}


	
}

void instructions()
/* Pre: None.
Post: Instructions for using the Life program have been printed. */
{
	cout << "Welcome to Conway's game of Life." << endl;
	cout << "This game uses a grid of max size " << maxrow << " by " << maxcol << " in which each" << endl;
	cout << "cell can either be occupied by an organism or not." << endl;
	cout << "The occupied cells change from generation to generation" << endl;
	cout << "according to how many neighboring cells are alive." << endl;
}

void Life::print()
/* Pre: The Life object contains a configuration.
Post: The configuration is written for the user. */
{
	int row, col;
	cout << "\nThe current Life configuration is:" << endl;
	for (row = 1; row <= uusiMAXrow+1; row++) {
		for (col = 1; col <= uusiMAXcol+1; col++)
			if (grid[row][col] == '*') cout << '*';
			else cout << ' ';
		cout << endl;
	}
	cout << endl;
}

void Life::initialize()
{
	char sisaan;
	char row, col;
	string myfile;

	ifstream filein;
	cout << "Enter the name od the file: " << endl;
	cin >> myfile;
	//filein.open("tiedosto.txt"); //voi käyttää jos poistetaan käyttäjältä tiedoston nimen kysyminen
	filein.open(myfile);
	
	
	if (filein.is_open()) {

		cout << "File opened successfully!" << endl;

		while (!filein.eof()) {

			for (int i = 1; i <= uusiMAXrow; i++) {
				for (int j = 1; j <= uusiMAXcol+1; j++) {

					//filein >> grid[i][j];
					grid[i][j] = filein.get();
				}
			}
		}
	}

	filein.close();
}


