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

extern const int Memory = 4 * 1024 * 1024;
extern map<string, int> idReg;
extern set<string> type_o_i_i_sheet;
extern set<string> type_o_i_sheet;
extern set<string> type_ls_sheet;

class Brick {
	friend class Op;
	friend class CPU;
public:
	enum Brick_type {
		reg, ram1, ram2, ram4, imm, lohi
	};

	int countReg(char* nreg) const {
		return (reinterpret_cast<char*>((int)location) - nreg) / 4;
	}
private:
	Brick_type type;
	unsigned long long location;

	Brick() {}

	Brick(unsigned long long x) :type(imm), location(x) {};
	
	Brick(const string& nw, char* nreg) {
		if (nw[0] != '$') {
			type = imm;
			location = fromStringToNumber(nw);
			return;
		}
		type = reg;
		location = (unsigned long long)(nreg + 4 * idReg[nw]);
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
		if (nw == "$lohi" || nw == "$hilo") {
			type = lohi;
			location = (unsigned long long)(nreg + 4 * 32);
		}
		type = reg;
		location = (unsigned long long)(nreg + 4 * idReg[nw]);
	}

	friend void operator << (Brick& des, const Brick& res) {
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
	friend void operator >> (const Brick& res, Brick& des) {
		des << res;
	}
};

#endif