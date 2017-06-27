#ifndef littleround_MIPS_program
#define littleround_MIPS_program

#include <vector>
#include <iostream>
#include "line.hpp"
#include "RAM.hpp"
using namespace std;

extern RAM ram;
extern map<string, Line::Line_type> findType;
extern map<string, Data::Data_type> find_dType;

class Program {
private:
	vector<Line*> lines;
public:
	Program(istream& fin) {
		fin.seekg(0, ios::beg);
		string line;
		unsigned long long mem = 0;
		while (getline(fin, line)) {
			lines.push_back(parse(line, mem));
		}
		int cnt = 0;
		for (auto i : lines) {
			i->id = cnt++;
		}
	}
	~Program() {
		for (auto i : lines) delete i;
	}

	Line* parse(string& line, unsigned long long &mem) {
		int t = 0;
		string s;
		s = getToken(line, t);
		if (findType.count(s)) {
			switch (findType[s]) {
			case Line::Line_type::tInstruction : {
				Instruction* nw = new Instruction;
				nw->argc = 0;
				nw->ins = s;
				nw->argv[0] = getToken(line, t);
				if (nw->argv[0] == "") return nw;
				nw->argc++;
				eatComma(line, t);


				nw->argv[1] = getToken(line, t);
				if (nw->argv[1] == "") return nw;
				nw->argc++;
				eatComma(line, t);

				nw->argv[2] = getToken(line, t);
				if (nw->argv[2] == "") return nw;
				nw->argc++;

				return nw;
			}
			case Line::Line_type::tData : {
				Data* nw = new Data;
				nw->dType = find_dType[s];
				nw->location = mem;
				if (nw->dType == Data::Data_type::asciiz || 
					nw->dType == Data::Data_type::ascii) {
					nw->arg.push_back(getString(line, t));
				}
				else {
					s = getToken(line, t);
					while (s != "") {
						nw->arg.push_back(s);
						eatComma(line, t);
						s = getToken(line, t);
					}
				}
				nw->length = ram.distribute(mem, *nw);
				return nw;
			}
			case Line::Line_type::tFrame: {
				Frame* nw = new Frame;
				nw->isData = (s == ".data");
				return nw;
			}
			default: {
				throw (-1); //undefined
			}
			}
		}
		else {
			Label* nw = new Label;
			nw->name = s;
			return nw;
		}
	}

	inline bool isLetter(char x) {
		return ((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z') || ((x >= '0') && (x <= '9')));
	}

	inline bool isSpecial(char x) {
		return (x == '_' || x == '.');
	}

	void eatComma(string& line, int& t) {
		while (!isLetter(line[t]) && !isSpecial(line[t])
			&& line[t] != ':' && line[t] != '#' && t<line.length()) ++t;
		if (t < line.length() && line[t] == '#') t = line.length();
	}

	string getToken(string& line, int& t) {
		while (!isLetter(line[t]) && !isSpecial(line[t]) 
			&& line[t] != ',' && line[t] != ':' && line[t] != '#'
			&& t<line.length()) ++t;
		if (t == line.length()) return "";
		if (line[t] == '#') {
			t = line.length();
			return "";
		}
		string ret = "";
		while (isLetter(line[t]) || isSpecial(line[t])) {
			ret = ret + line[t];
			++t;
		}
		if (ret == "") {
			while (line[t] == ',' || line[t] == ':') {
				ret = ret + line[t];
				++t;
			}
		}
		return ret;
	}

	string getString(string& line, int& t) {
		while (line[t] != '\n' && line[t] != '\r' && line[t] != '\"' && t<line.length()) ++t;
		if (t == line.length() || line[t] == '\n' || line[t] == '\r') return "";
		bool escape = false;
		string ret = "";
		++t;
		while (line[t] != '\"' || (line[t] == '\"' && escape)) {
			if (escape) {
				escape = false;
				switch (line[t]) {
				case 'n': {
					ret += '\n';
					break;
				}
				case 'r': {
					ret += '\r';
					break;
				}
				case 't': {
					ret += '\t';
					break;
				}
				case '\\': {
					ret += '\\';
					break;
				}
				case '\'': {
					ret += '\'';
					break;
				}
				case '\"': {
					ret += '\"';
					break;
				}
				case '0': {
					ret += '\0';
					break;
				}
				default: {
					ret += "-UnknownChar-";
					break;
				}
				}
			}
			else {
				if (line[t] == '\\') {
					escape = true;
					++t;
					continue;
				}
				ret += line[t];
			}
			++t;
		}
		return ret;
	}
	friend ostream& operator <<(ostream& fout, const Program& pg) {
		string dis[4];
		dis[0] = "Label";
		dis[1] = "Instruction";
		dis[2] = "Data";
		dis[3] = "Frame";
		for (auto i : pg.lines) {
			fout << i->id<<'\t'<<dis[i->type]<<'\t';
			if (i->type == 0) {
				cout << ((Label*) i)->name << endl;
			}
			if (i->type == 1) {
				cout << ((Instruction*)i)->ins << endl;
			}
			if (i->type == 2) {
				cout << ((Data*)i)->location<< ' ' <<((Data*)i)->length << endl;
			}
			if (i->type == 3) {
				if (((Frame*)i)->isData) cout << "DATA" << endl; else cout << "TEXT" << endl;
			}
		}
		return fout;
	}
};

#endif