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
		unsigned long long temp = 0;
		//import
		switch (res.type) {
		case imm: {
			temp = res.location;
			break;
		}
		case ram1: {
			temp = (*(reinterpret_cast<unsigned char*>(res.location)));
			break;	
		}
		case ram2: {
			temp = (*(reinterpret_cast<unsigned short*>(res.location)));
			break;
		}
		case lohi: {
			temp = (*(reinterpret_cast<unsigned long long*>(res.location)));
			break;
		}
		default: {
			temp = (*(reinterpret_cast<unsigned int*>(res.location)));
		}
		}
		//export
		switch (des.type) {
		case imm: {
			des.location = temp;
			break;
		}
		case ram1: {
			(*(reinterpret_cast<char*>(des.location))) = (char)temp;
			break;
		}
		case ram2: {
			(*(reinterpret_cast<short*>(des.location))) = (short)temp;
			break;
		}
		case lohi: {
			(*(reinterpret_cast<unsigned long long*>(des.location))) = temp;
			break;
		}
		default: {
			(*(reinterpret_cast<int*>(des.location))) = (int)temp;
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