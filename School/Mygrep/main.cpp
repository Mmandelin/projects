#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

char* strcasestr(const char* bigStr, const char* searchStr);

int main(int argc, char* argv[]) {

	if (argc == 1) {
		//1. inkrementti, otetaan hakulause ja hakusana sisaan
		string sisaan;
		string haku;
		cout << "Give a string from which to search for: ";
		getline(cin, sisaan);
		cout << "Give search string: ";
		getline(cin, haku);
		//1. inkrementti annetut stringit hakuohjelmalle
		const char* bigStr = sisaan.c_str();
		const char* searchStr = haku.c_str();
		char* p = strcasestr(bigStr, searchStr); //p sisältää osoittimen siihen kohtaan mistä hakusana alkaa, jos sana löytyi
		int laskuri1 = 0;
		int laskuri2 = 0;
		if (p) {
			int i = 0;
			for (i = 0; i < strlen(p); i++) {
				laskuri1++;
			}
			for (i = 0; i < strlen(bigStr); i++) {
				laskuri2++;
			}
		}
		int positio = laskuri2 - laskuri1;
		if (p) {
			cout << "''" << haku << "'' found in ''" << sisaan << "'' in position " << positio << endl;
		}
		else {
			cout << "''" << haku << "'' NOT found in ''" << sisaan << "''" << endl;
		}
		bigStr = NULL;
		delete bigStr;
		searchStr = NULL;
		delete searchStr;
		p = NULL;
		delete p;
	}


	else if (argc == 3) {
		//2. inkrementti
		// argv[0]=ohjelman käynnistys, argv[1]=hakusana, argv[2]=avattava tiedosto
		string haku2 = argv[1];
		ifstream filein;
		filein.open(argv[2]);
		string line;
		if (filein.is_open()) {
			//cout << "File opened succesfully!" << endl;
			while (getline(filein, line)) {
				size_t pos2 = line.find(haku2);
				if (pos2 != string::npos) {
					cout << line << endl;
				}
			}
		}
		else {
			cout << "Failed to open the file. Exiting program" << endl;
			return 0;
		}
		filein.close();		
	}


	else if (argc == 4) {
		//3. inkrementti
		// argv[0]=ohjelman käynnistys, argv[1]=flags, argv[2]=hakusana, argv[3]=avattava tiedosto
		string flags = argv[1];
		string haku3 = argv[2];
		string hakutulostus = argv[2];
		string line2;
		bool lineflag = false;
		bool occurancesflag = false;
		bool insensitiveflag = false;
		bool reverseflag = false;
		int counter = 0;
		int linecounter = 0;

		size_t foundflag = flags.find("-o");
		if (foundflag != string::npos) {
			if (flags.size() > 2) {
				for (int i = 2; i < flags.size(); i++) {
					if (flags[i] == 'o') {
						occurancesflag = true;
					}
					else if (flags[i] == 'l') {
						lineflag = true;
					}
					else if (flags[i] == 'i') {
						insensitiveflag = true;
					}
					else if (flags[i] == 'r') {
						reverseflag = true;
					}
				}
			}
		}		
		ifstream filein2;
		filein2.open(argv[3]);
		if (filein2.is_open()) {
			
			if (lineflag && insensitiveflag && reverseflag) {
				//hakusana lowercaseksi
				transform(haku3.begin(), haku3.end(), haku3.begin(), ::tolower);
				while (getline(filein2, line2)) {
					linecounter++;
					//tiedostosta luetaan rivi kerrallaan ja ne muutetaan lowercaseksi ennen hakusanan etsintää
					transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
					size_t pos2 = line2.find(haku3);
					if (pos2 == string::npos) {
						cout << linecounter << ":" << line2 << endl;
						counter++;
					}
				}
			}
			else if (lineflag && insensitiveflag) {
				//hakusana lowercaseksi
				transform(haku3.begin(), haku3.end(), haku3.begin(), ::tolower);
				while (getline(filein2, line2)) {
					linecounter++;
					//tiedostosta luetaan rivi kerrallaan ja ne muutetaan lowercaseksi ennen hakusanan etsintää
					transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
					size_t pos2 = line2.find(haku3);
					if (pos2 != string::npos) {
						cout << linecounter << ":" << line2 << endl;
						counter++;
					}
				}
			}
			else if (lineflag && reverseflag) {
				while (getline(filein2, line2)) {
					linecounter++;
					size_t pos2 = line2.find(haku3);
					if (pos2 == string::npos) {
						cout << linecounter << ":" << line2 << endl;
						counter++;
					}
				}
			}
			else if (insensitiveflag && reverseflag) {
				//hakusana lowercaseksi
				transform(haku3.begin(), haku3.end(), haku3.begin(), ::tolower);
				while (getline(filein2, line2)) {
					//tiedostosta luetaan rivi kerrallaan ja ne muutetaan lowercaseksi ennen hakusanan etsintää
					transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
					size_t pos2 = line2.find(haku3);
					if (pos2 == string::npos) {
						cout << line2 << endl;
						counter++;
					}
				}
			}
			else if (lineflag) {
				while (getline(filein2, line2)) {
					linecounter++;
					size_t pos2 = line2.find(haku3);
					if (pos2 != string::npos) {
						cout << linecounter << ":" << line2 << endl;
						counter++;
					}
				}
			}
			else if (insensitiveflag) {
				//hakusana lowercaseksi
				transform(haku3.begin(), haku3.end(), haku3.begin(), ::tolower);
				while (getline(filein2, line2)) {
					//tiedostosta luetaan rivi kerrallaan ja ne muutetaan lowercaseksi ennen hakusanan etsintää
					transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
					size_t pos2 = line2.find(haku3);
					if (pos2 != string::npos) {
						cout << line2 << endl;
						counter++;
					}
				}
			}
			else if (reverseflag) {
				while (getline(filein2, line2)) {
					size_t pos2 = line2.find(haku3);
					if (pos2 == string::npos) {
						cout << line2 << endl;
						counter++;
					}
				}
			}
			else {
				while (getline(filein2, line2)) {
					size_t pos2 = line2.find(haku3);
					if (pos2 != string::npos) {
						cout << line2 << endl;
						counter++;
					}
				}
			}
		}
		else {
			cout << "Failed to open the file. Exiting program" << endl;
			return 0;
		}
		filein2.close();

		if (occurancesflag) {
			if (reverseflag && occurancesflag) {
				cout << "Occurances of lines NOT containing ''" << hakutulostus << "'': " << counter << endl;
			}
			else {
				cout << "Occurances of lines containing ''" << hakutulostus << "'': " << counter << endl;
			}
		}
	}

	return 0;
}

char* strcasestr(const char* bigStr, const char* searchStr) {

	const char* a;
	const char* b;

	b = searchStr;

	if (*b == 0) {
		return (char*)bigStr;
	}

	for (; *bigStr != 0; bigStr += 1) {
		if (*bigStr != *b) {
			continue;
		}

		a = bigStr;
		while (1) {
			if (*b == 0) {
				return (char*)bigStr;
			}
			if (*a++ != *b++) {
				break;
			}
		}
		b = searchStr;
	}

	a = NULL;
	delete a;
	b = NULL;
	delete b;
	return NULL;
}