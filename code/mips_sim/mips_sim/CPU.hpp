#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU

#include<iostream>
#include "RAM.hpp"
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
using namespace std;

class Brick {
public:
	enum Brick_type {
		reg, ram, imm
	};
private:
	Brick_type type;
	int data;
	int size;
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
	RAM& ram;
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
	void prepare(Program& pg) {

	}
};

#endif