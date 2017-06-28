#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU

#include<iostream>
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
#include<map>
using namespace std;

extern const int Memory = 4 * 1024 * 1024;

class Brick {
public:
	enum Brick_type {
		reg, ram1, ram2, ram4, imm
	};
private:
	Brick_type type;
	char* ram;
	char* reg;
	char* data;

	int* findReg() {
		return reinterpret_cast<int *>(reg + data * 4);
	}

	friend void operator << (Brick& des, const Brick& res) {
		unsigned long long temp;
		switch (res.type) {
		case imm : {
			temp = &res.data;
			break;
		}
		case reg : {
			temp = res.findReg();
			break;
		}
		default : {
			temp = res.data;
		}
		}
		//find the pointer to the source
	}
	friend void operator >> (const Brick& res, Brick& des) {
		des << res;
	}
};

class Reg {
	friend class CPU;
	friend class Brick;
public:
	enum Reg_type {
		number,address
	};
private:
	char data[8];
	char* address;
};

class Assumption {
	Brick l;
	Brick r;
	string ins;
};

class CPU {
	Assumption assumptionFlow[5];
	char ram[Memory];
	char reg[4 * 34];

	int pc;
	int nopCounter;
	void IF() {

	}

	bool IF_ID;
	string ins_IF_ID;

	set<Brick> data_lock;
	void ID() {

	}

	bool ID_IF;
	int pc_ID_IF;

	bool ID_EX;
	string ins_ID_EX;
	vector<Brick> data_ID_EX;
	Brick des_ID_EX;

	void EX() {

	}

	bool EX_MEM;
	string ins_EX_MEM;
	Brick data_EX_MEM;
	Brick des_EX_MEM;

	bool EX_MEM_8;
	string data_EX_MEM_8;

	istream& I;
	ostream& O;
	void MEM() {

	}

	bool MEM_LAST;
	Brick location;
	string before;
	string after;

	bool MEM_WB;
	string ins_MEM_WB;
	Brick data_MEM_WB;
	Brick des_MEM_WB;

	void WB() {

	}

public:
	void run(Program& pg) {
		
	}
};

#endif