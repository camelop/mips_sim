#ifndef littleround_MIPS_program
#define littleround_MIPS_program

#include <vector>
#include <iostream>
#include "line.hpp"
using namespace std;

class Program {
private:
	vector<Line*> lines;
public:
	Program(istream& fin) {
		fin.seekg(0, ios::beg);
		string line;
		while (getline(fin, line)) {
			lines.push_back(parse(line));
		}
	}
	~Program() {
		for (auto i : lines) delete i;
	}

	Line* parse(string& line) {
		int t = 0;
		getToken(line, t);

	}

	inline bool isLetter(char x) {
		return ((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z'));
	}

	inline bool isSpecial(char x) {
		return (x == '_' || x == '.' || x == ':');
	}

	string getToken(string& line, int& t) {
		while (!isLetter(line[t]) && !isSpecial(line[t]) 
			&& line[t] != ',' && line[t] != '\n') ++t;
		if (line[t] == '\n') return "";
		string ret = "";
		while (isLetter(line[t]) || isSpecial(line[t])) {
			ret = ret + line[t];
			++t;
		}
		return ret;
	}
};

#endif