#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "line.hpp"
using namespace std;

typedef vector<Line> Program;

int main(int argc, char* argv[]) {
	string inMipsLocation, inDataLocation;
	if (argc == 1) {
		++argc;
		cout << "Input the index of the mips file: ";
		cin>>inMipsLocation;
	}
	else {
		inMipsLocation = argv[1];
	}
	if (argc == 2) {
		cout << "Input the index of the in file: ";
		cin >> inDataLocation;
	}
	else {
		inDataLocation = argv[2];
	}
	ifstream mipsIn(inMipsLocation);
	ifstream dataIn(inDataLocation);
	ofstream dataOut("output.txt");
	
	Program pg;

	
}