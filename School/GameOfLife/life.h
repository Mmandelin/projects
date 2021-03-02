#pragma once

const int maxrow = 20, maxcol = 60; // grid dimensions


class Life {
public:
	void save();
	void initialize();
	void print();
	void update();
private:
	char grid[maxrow + 2][maxcol + 2] = { 0 };
	// allows for two extra rows and columns
	int neighbor_count(int row, int col);
};

void instructions();
void asetaKoko();