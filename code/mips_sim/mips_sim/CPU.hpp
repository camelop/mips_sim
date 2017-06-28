#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU

#include<iostream>
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
#include<map>
#include<cstring>
using namespace std;

extern set<string> type_o_i_i_sheet;
extern const int Memory = 4 * 1024 * 1024;
extern map<string, int> idReg;

class Brick {
	friend class CPU;
public:
	enum Brick_type {
		reg, ram1, ram2, ram4, imm, lohi
	};
private:
	Brick_type type;
	unsigned long long location;

	Brick() {}

	Brick(string& nw, char* nreg) {
		if (nw[0] != '$') {
			type = imm;
			location = fromStringToNumber(nw);
			return;
		}
		type = reg;
		location = (unsigned long long)(nreg + 4 * idReg[nw]);
	}

	void fromString(string& nw, char* nreg) {
		if (nw[0] != '$') {
			type = imm;
			location = fromStringToNumber(nw);
			return;
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

class Assumption {
	Brick l;
	Brick r;
	string ins;
};

class CPU {
	bool working;
	Assumption assumptionFlow[5];
	char ram[Memory];
	char reg[4 * 34];
	int* findReg(int id) {
		return reinterpret_cast<int*>(reg + 4 * id);
	}

	int pc;
	int nopCounter;
	bool isOn;
	
	bool JR_LOCK;
	void IF(const Program& pg) {
		if (!isOn) return;
		if (IF_ID) return;
		if (JR_LOCK) {
			if (ID_IF) {
				pc = pc_ID_IF;
				ID_IF = false;
				JR_LOCK = false;
			}
			else {
				return;
			}
		}
		while (pg.lines[pc]->type != Line::Line_type::tInstruction) ++pc;
		Instruction& nw = *(dynamic_cast<Instruction*>(pg.lines[pc]));
		instruction_IF_ID = nw;
		if (nw.ins == "jal" || nw.ins == "jalr") instruction_IF_ID.arg.push_back(fromNumberToString(pc + 1));
		IF_ID = true;

		//next step
		if (nw.ins[0] == 'b' || nw.ins[0] == 'j') {
			if (nw.ins == "j" || nw.ins == "jal") {
				pc = fromStringToNumber(nw.arg[0]);
				return;
			}
			if (nw.ins == "jr" || nw.ins == "jalr") {
				JR_LOCK = true;
				return;
			}
		}
		else {
			++pc;
			if (pc > pg.lines.size()) throw (-1);//invalid program
		}
		if (nw.ins == "syscall") {
			if ((*(findReg(idReg["$v0"]))) == 10) sys10_IF();
			if ((*(findReg(idReg["$v0"]))) == 10) sys17_IF();
		}
	}

	void sys10_IF() { isOn = false; }
	void sys17_IF() { isOn = false; }

	bool IF_ID;
	Instruction instruction_IF_ID;

	set<Brick> data_lock;
	void ID(const Program& pg) {
		if (ID_EX || !IF_ID) return;
		string& ins = instruction_IF_ID.ins;
		ins_ID_EX = ins;
		data_ID_EX.clear();
		if (type_o_i_i_sheet.count(ins)) {
			des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
			data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1], reg));
			data_ID_EX.push_back(Brick(instruction_IF_ID.arg[2], reg));
		}
		else {
			//other kinds of instructions
			//to-do here
		}
		ID_EX = true;

	}

	bool ID_IF;
	int pc_ID_IF;

	bool ID_EX;
	string ins_ID_EX;
	vector<Brick> data_ID_EX;
	Brick des_ID_EX;

	void EX(const Program& pg) {

	}

	bool EX_MEM;
	string ins_EX_MEM;
	Brick data_EX_MEM;
	Brick des_EX_MEM;

	bool EX_MEM_8;
	string data_EX_MEM_8;

	istream& I;
	ostream& O;
	void MEM(const Program& pg) {

	}

	unsigned long long hp;
	void sys9_MEM(unsigned long long n) {
		hp += n;
	}

	bool MEM_LAST;
	Brick location;
	string before;
	string after;

	bool MEM_WB;
	string ins_MEM_WB;
	Brick data_MEM_WB;
	Brick des_MEM_WB;

	void WB(const Program& pg) {

	}

	void sys10_WB() {
		(*findReg(idReg["$a0"])) = 0;
	}
	void sys17_WB() {
		//do nothing but keep $a0
	}

	vector<char*> memRef;
public:
	CPU(istream& I, ostream& O) :I(I), O(O) {}
	int run(const Program& pg) {
		pc = pg.entry;
		memset(ram, 0, sizeof(ram));
		memset(reg, 0, sizeof(reg));
		(*(findReg(29))) = Memory;

		hp = 0;
		for (auto i : pg.lines) {
			memRef.push_back(ram + hp);
			if (i->type == Line::Line_type::tData) {
				sys9_MEM((reinterpret_cast<Data*>(i))->length);
			}
		}

		JR_LOCK = false;
		IF_ID = false;
		ID_EX = false;
		ID_IF = false;
		EX_MEM = false;
		EX_MEM_8 = false;
		MEM_LAST = false;
		MEM_WB = false;

		isOn = true;
		working = true;
		while (working) {
			//reverse later
			IF(pg);
			ID(pg);
			EX(pg);
			MEM(pg);
			WB(pg);
		}

		return (*findReg(idReg["$a0"]));
	}
};

#endif