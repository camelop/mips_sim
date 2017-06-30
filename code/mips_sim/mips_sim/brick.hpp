#ifndef littleround_MIPS_brick
#define littleround_MIPS_brick

#include<iostream>
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
#include<map>
#include<cstring>
using namespace std;

extern const int Memory;
extern map<string, int> idReg;
extern set<string> type_o_i_i_sheet;
extern set<string> type_o_i_sheet;
extern set<string> type_ls_sheet;

class Brick {
	friend class Op;
	friend class CPU;
	friend class Assumption;
public:
	enum Brick_type {
		reg, ram1, ram2, ram4, imm, lohi
	};

private:
	Brick_type type;
	unsigned long long location;

	Brick() {}

	Brick(unsigned long long x) :type(imm), location(x) {};
	
	Brick(const string& nw, char* nreg) {
		fromString(nw, nreg);
	}

	int countReg(char* nreg) const {
		return (reinterpret_cast<char*>((int)location) - nreg) / 4;
	}

	void fromNumber(unsigned long long x) {
		type = imm;
		location = x;

	}

	void fromString(const string& nw, char* nreg) {
		if (nw[0] != '$') {
			type = imm;
			location = fromStringToNumber(nw);
			return;
		}
		if (nw == "$lohi") {
			type = lohi;
			location = (unsigned long long)(nreg + 4 * 32);
		}
		else {
			type = reg;
			location = (unsigned long long)(nreg + 4 * idReg[nw]);
		}
	}

	friend void operator << (Brick& des, Brick& res) {
		unsigned long long* tempp = &res.location;
		int* temp = (res.type == imm) ? temp = reinterpret_cast<int*>(tempp) : reinterpret_cast<int*>(res.location);
		switch (des.type) {
		case imm: {
			des.location = (unsigned long long) (*(reinterpret_cast<int*>(temp)));
			break;
		}
		case ram1: {
			(*(reinterpret_cast<char*>(des.location))) = (*(reinterpret_cast<char*>(temp)));
			break;
		}
		case ram2: {
			(*(reinterpret_cast<short*>(des.location))) = (*(reinterpret_cast<short*>(temp)));
			break;
		}
		case lohi: {
			(*(reinterpret_cast<long long*>(des.location))) = (*(reinterpret_cast<long long*>(temp)));
			break;
		}
		default: {
			(*(reinterpret_cast<int*>(des.location))) = (*(reinterpret_cast<int*>(temp)));
		}
		}
	}
	friend void operator >> (Brick& res, Brick& des) {
		des << res;
	}

	friend ostream& operator << (ostream& oo,const Brick& des) {
		if (des.type == Brick::Brick_type::imm) oo << "imm: " << des.location;
		if (des.type == Brick::Brick_type::lohi) oo << "lohi: " << des.location;
		if (des.type == Brick::Brick_type::ram1) oo << "ram1: " << des.location;
		if (des.type == Brick::Brick_type::ram2) oo << "ram2: " << des.location;
		if (des.type == Brick::Brick_type::ram4) oo << "ram4: " << des.location;
		if (des.type == Brick::Brick_type::reg) oo << "reg: " << des.location;
		return oo;
	}
};

#endif