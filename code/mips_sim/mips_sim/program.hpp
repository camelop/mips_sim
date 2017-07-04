#ifndef littleround_MIPS_program
#define littleround_MIPS_program

#include <vector>
#include <iostream>
#include "line.hpp"
using namespace std;

extern map<string, Line::Line_type> findType;
extern map<string, Data::Data_type> find_dType;
extern set<string> label_1_sheet;
extern set<string> label_2_sheet;
extern set<string> label_2_check_sheet;
extern set<string> label_3_sheet;

int fromStringToNumber(const string& s) {
	int ten = 1;
	int f = 1;
	int ret = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == '-') {
			f = -1;
			continue;
		}
		ret += ten*(s[i] - '0');
		ten *= 10;
	}
	return (ret*f);
}

string fromNumberToString(long long x) {
	string ret = "";
	if (x == 0) {
		return "0";
	}
	bool f = 0;
	if (x < 0) {
		f = 1;
		x = -x;
	}
	while (x > 0) {
		ret = (char)(x % 10 + '0') + ret;
		x /= 10;
	}
	if (f) ret = '-' + ret;
	return ret;
}

unsigned long long distribute(unsigned long long &mem, const Data& d) {
	unsigned long long ret = 0;
	switch (d.dType) {
	case Data::Data_type::align: {
		unsigned long long two = (1 << fromStringToNumber(d.arg[0]));
		unsigned long long res = mem%two;
		if (res == 0) return 0;
		ret = two - res;
		mem += ret;
		return ret;
	}
	case Data::Data_type::ascii: {
		ret = d.arg[0].length();
		mem += ret;
		return ret;
	}
	case Data::Data_type::asciiz: {
		ret = d.arg[0].length() + 1;
		mem += ret;
		return ret;
	}
	case Data::Data_type::byte: {
		//recognize as digits
		mem += 1;
		return 1;
	}
	case Data::Data_type::half: {
		mem += 2;
		return 2;
	}
	case Data::Data_type::word: {
		mem += 4;
		return 4;
	}
	case Data::Data_type::space: {
		ret = fromStringToNumber(d.arg[0]);
		mem += ret;
		return ret;
	}
	default: {
		throw(-1); //undefined
	}
	}
}

class Program {
	friend class CPU;
private:
	vector<Line*> lines;
	int entry;
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
		prepare();
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
				nw->arg.clear();
				nw->ins = s;
				s = getToken(line, t);
				if (s == "") return nw;
				nw->arg.push_back(s);
				eatComma(line, t);

				s = getToken(line, t);
				if (s == "") return nw;
				nw->arg.push_back(s);
				eatComma(line, t);

				s = getToken(line, t);
				if (s == "") return nw;
				nw->arg.push_back(s);
				
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
				nw->length = distribute(mem, *nw);
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
		return (x == '_' || x == '.' || x == '$' || x == '(' || x == ')' || x == '-' );
	}

	void eatComma(string& line, int& t) {
		while (!isLetter(line[t]) && !isSpecial(line[t])
			&& line[t] != '#' && t<(int)line.length()) ++t;
		if (t < (int)line.length() && line[t] == '#' ) t = line.length();
	}

	string getToken(string& line, int& t) {
		while (!isLetter(line[t]) && !isSpecial(line[t]) 
			&& line[t] != ',' && line[t] != '#'
			&& t<(int)line.length()) ++t;
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
			while (line[t] == ',') {
				throw(-1); //gramma mistake
				ret = ret + line[t];
				++t;
			}
		}
		return ret;
	}

	string getString(string& line, int& t) {
		while (line[t] != '\n' && line[t] != '\r' && line[t] != '\"' && t<(int)line.length()) ++t;
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
				fout << ((Label*) i)->name << endl;
			}
			if (i->type == 1) {
				fout << ((Instruction*)i)->ins << ":";
				for (auto j : ((Instruction*)i)->arg) fout << ' ' << j;
				fout << endl;
			}
			if (i->type == 2) {
				fout << ((Data*)i)->location<< ' ' <<((Data*)i)->length << endl;
			}
			if (i->type == 3) {
				if (((Frame*)i)->isData) fout << "DATA" << endl; else fout << "TEXT" << endl;
			}
		}
		return fout;
	}

	void prepare() {
		map<string, int> labelId;
		for (auto line : lines) {
			if (line->type == Line::Line_type::tLabel) {
				Label* nw = dynamic_cast<Label*> (line);
				if (nw->name == "") continue;
				if (labelId.count(nw->name)) cerr << "Reduplicated label" << endl; //reduplicated label
				labelId[nw->name] = nw->id;
			}
		}
		entry = labelId["main"] + 1;
		for (auto line : lines) {
			if (line->type == Line::Line_type::tInstruction) {
				Instruction* nw = dynamic_cast<Instruction*> (line);
				if (label_1_sheet.count(nw->ins)) {
					if (!labelId.count(nw->arg[0])) cerr << "Undefined label" << endl; //undefined label
					nw->arg[0] = fromNumberToString(labelId[nw->arg[0]]);
				}
				if (label_2_sheet.count(nw->ins)) {
					if (!labelId.count(nw->arg[1])) cerr << "Undefined label" << endl; //undefined label
					nw->arg[1] = fromNumberToString(labelId[nw->arg[1]]);
				}
				if (label_3_sheet.count(nw->ins)) {
					if (!labelId.count(nw->arg[2])) cerr << "Undefined label" << endl; //undefined label
					nw->arg[2] = fromNumberToString(labelId[nw->arg[2]]);
				}
				if (label_2_check_sheet.count(nw->ins)) {
					if (nw->arg[1].find('(') != string::npos) continue;
					if (!labelId.count(nw->arg[1])) cerr << "Undefined label" << endl; //undefined label
					nw->arg[1] = fromNumberToString(labelId[nw->arg[1]]);
				}
			}
		}
	}
};

#endif