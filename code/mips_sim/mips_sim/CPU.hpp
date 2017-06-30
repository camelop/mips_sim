#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU

#include<iostream>
#include<iomanip>
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
#include<map>
#include<cstring>
#include "brick.hpp"
#include "op.hpp"
using namespace std;

extern const int Memory = 4 * 1024 * 1024;

extern map<string, int> idReg;
extern set<string> type_o_i_i_sheet;
extern set<string> type_o_i_sheet;
extern set<string> type_ls_sheet;
extern set<string> wb_sheet;

extern set<string> label_2_sheet; // b with z
extern set<string> label_3_sheet; // b without z

class Assumption {
	Brick l;
	Brick r;
	string ins;
public:
	Assumption() {}
};

class CPU {
	bool working;
	Assumption assumptionFlow[5];
	char* ram;
	char reg[sizeof(int) * 34];
	int* findReg(int id) {
		return reinterpret_cast<int*>(reg + 4 * id);
	}

	int pc;
	int nopCounter;
	bool isOn;
	
	bool JR_LOCK;
	bool B_LOCK;
	void IF(const Program& pg) {
		if (nopCounter > 0) {
			nopCounter--;
			return;
		}
		if (!isOn) return;
		if (IF_ID) return;
		if (B_LOCK) {
			if (EX_IF) {
				if (pc_EX_IF == -1) ++pc; else pc = pc_EX_IF;
				EX_IF = false;
				B_LOCK = false;
			}
			else return;
		}
		if (JR_LOCK) {
			if (ID_IF) {
				pc = pc_ID_IF;
				ID_IF = false;
				JR_LOCK = false;
			}
			else return;
		}
		while (pg.lines[pc]->type != Line::Line_type::tInstruction && pc<pg.lines.size()) ++pc;
		if (pc >= pg.lines.size()) return;//invalid program or sys just about to exit

		Instruction& nw = *(dynamic_cast<Instruction*>(pg.lines[pc]));
		if (nw.ins == "nop") {
			nopCounter = 4;
			++pc;
			return;
		}
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
			//other situation to-do
			if (nw.ins == "b") {
				pc = fromStringToNumber(nw.arg[0]);
				return;
			}
			else {
				B_LOCK = true;
				return;
			}
		}
		else {
			++pc;
			if (pc >= pg.lines.size()) throw (-1);//invalid program
		}
	}

	bool IF_ID;
	Instruction instruction_IF_ID;

	bool regLock[34];
	bool ID_READY;
	void ID(const Program& pg) {
		if (ID_EX || !IF_ID) return;
		Brick toJump;
		if (!ID_READY) {
			ins_ID_EX = instruction_IF_ID.ins;
			string& ins = ins_ID_EX;
			data_ID_EX.clear();

			//construct blocks

			if (type_o_i_i_sheet.count(ins) && instruction_IF_ID.arg.size() == 3) {
				des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
				data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1], reg));
				data_ID_EX.push_back(Brick(instruction_IF_ID.arg[2], reg));
			}
			else
				if (type_o_i_sheet.count(ins) && instruction_IF_ID.arg.size() == 2) {
					if (ins == "mfhi") {
						des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
						data_ID_EX.push_back(Brick("$hi", reg));
					}
					else
						if (ins == "mflo") {
							des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
							data_ID_EX.push_back(Brick("$lo", reg));
						}
						else
							if (ins == "mul" || ins == "mulu" || ins == "div" || ins == "divu") {
								des_ID_EX.fromString("$lohi", reg);
								data_ID_EX.push_back(Brick(instruction_IF_ID.arg[0], reg));
								data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1], reg));
							}
							else {
								des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
								data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1], reg));
							}
				}
				else
					if (ins[0] == 'b' && ins != "b") {
						if (ins[ins.length() - 1] == 'z') {
							des_ID_EX.fromString(instruction_IF_ID.arg[1], reg); //label
							data_ID_EX.push_back(Brick(instruction_IF_ID.arg[0], reg));
							data_ID_EX.push_back(Brick("0", reg));
						}
						else {
							des_ID_EX.fromString(instruction_IF_ID.arg[2], reg); //label
							data_ID_EX.push_back(Brick(instruction_IF_ID.arg[0], reg));
							data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1], reg));
						}
					}
					else
						if (ins == "jal" || ins == "jalr") {
							data_ID_EX.push_back(Brick(instruction_IF_ID.arg[1],reg));
							des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
						}
						else
							if (type_ls_sheet.count(ins)) {
								//somehow different, des always represent the register
								des_ID_EX.fromString(instruction_IF_ID.arg[0], reg);
								packAddress(data_ID_EX, instruction_IF_ID.arg[1]);
							}
							else
								if (ins == "syscall") {
									data_ID_EX.push_back(Brick("$v0", reg));
								}
			if (ins == "jr" || ins == "jalr") {
				toJump.fromString(instruction_IF_ID.arg[0], reg);
			}
			ID_READY = true;
			IF_ID = false;
		}

		string& ins = ins_ID_EX;
		//control
		if (ins == "jr" || ins == "jalr") {
			if (isLocked(toJump)) return;
			Brick temp(0);
			temp << toJump;
			pc_ID_IF = temp.location;
			ID_IF = true;
		}
		//fill reg 
		if (ins != "la" && ins != "lb" && ins != "lh" && ins != "lw") for (auto i : data_ID_EX) if (isLocked(i)) return;
		//add locks
		if (ins != "sb" && ins != "sh" && ins != "sw") {
			if (des_ID_EX.type == Brick::Brick_type::reg) {
				++regLock[des_ID_EX.countReg(reg)];
			}
			else {
				if (des_ID_EX.type == Brick::Brick_type::lohi) {
					++regLock[32];
					++regLock[33];
				}
			}
		}
		for (auto i : data_ID_EX) {
			if (i.type != Brick::Brick_type::reg) continue;
			Brick temp;
			temp.type = Brick::Brick_type::imm;
			temp << i;
			i = temp;
		}
		//syscall
		if (ins == "syscall") {
			int code = data_ID_EX[0].location;
			if (code == 1 || code == 4) {
				Brick reg_a0("$a0", reg);
				if (isLocked(reg_a0)) return;
				Brick temp;
				temp.type = Brick::Brick_type::imm;
				temp << reg_a0;
				data_ID_EX.push_back(temp);
			}
			if (code == 5) {
				++regLock[idReg["$v0"]];
			}
			if (code == 8) {
				Brick reg_a0("$a0", reg);
				if (isLocked(reg_a0)) return;
				Brick reg_a1("$a1", reg);
				if (isLocked(reg_a1)) return;
				Brick temp;
				temp.type = Brick::Brick_type::imm;
				temp << reg_a0;
				data_ID_EX.push_back(temp);
				temp << reg_a1;
				data_ID_EX.push_back(temp);
			}
			if (code == 9) {
				Brick reg_a0("$a0", reg);
				if (isLocked(reg_a0)) return;
				Brick temp;
				temp.type = Brick::Brick_type::imm;
				temp << reg_a0;
				data_ID_EX.push_back(temp);

				++regLock[idReg["$v0"]];
			}
			if (code == 10) isOn = false;
			if (code == 17) {
				Brick reg_a0("$a0", reg);
				if (isLocked(reg_a0)) return;
				Brick temp;
				temp.type = Brick::Brick_type::imm;
				temp << reg_a0;
				data_ID_EX.push_back(temp);

				isOn = false;
			}
		}
		ID_READY = false;
		ID_EX = true;
	}

	bool isLocked(const Brick& b) {
		if (b.type != Brick::Brick_type::reg) return false;
		return regLock[b.countReg(reg)];
	}

	void packAddress(vector<Brick>& v, string& nw) {
		if (nw.find('(') == string::npos) {
			v.push_back(Brick(nw, reg));//label->imm
			return;
		}
		v.push_back(Brick(nw.substr(nw.find('(') + 1, nw.find(')') - nw.find('(') - 1), reg)); //reg
		v.push_back(Brick(nw.substr(0, nw.find('(')), reg)); //imm
	}

	bool ID_IF;
	int pc_ID_IF;

	bool ID_EX;
	string ins_ID_EX;
	vector<Brick> data_ID_EX;
	Brick des_ID_EX;

	void EX(const Program& pg) {
		if (!ID_EX || EX_IF) return;

		//control instructions
		string& ins = ins_ID_EX;
		if (label_3_sheet.count(ins) || label_2_sheet.count(ins)) {
			int ll, rr; bool judge;
			ll = data_ID_EX[0].location;
			if (label_3_sheet.count(ins)) rr = data_ID_EX[1].location; else rr = 0;
			if (ins == "beq" || ins == "beqz") {
				judge = (ll == rr);
			}
			else {
				if (ins == "bne" || ins == "bnez") {
					judge = (ll != rr);
				}
				else
					if (ins == "bge" || ins == "bgez") {
						judge = (ll >= rr);
					}
					else
						if (ins == "ble" || ins == "blez") {
							judge = (ll <= rr);
						}
						else
							if (ins == "bgt" || ins == "bgtz") {
								judge = (ll > rr);
							}
							else {
								judge = (ll < rr);
							}
			}
			if (judge) pc_EX_IF = des_ID_EX.location; else pc_EX_IF = -1;
			EX_IF = true;
		} else 
		if (ins == "syscall") {
			int code = data_ID_EX[0].location;
			des_EX_MEM.fromNumber(code);
			if (code == 1 || code == 2 || code == 8 || code == 9 || code == 17)
				data_EX_MEM = data_ID_EX[1].location;
			if (code == 8) {
				data_EX_MEM_8 = data_ID_EX[2].location;
			}
		}
		else {
			Op op(ins_ID_EX, data_ID_EX, des_ID_EX, ins_EX_MEM, data_EX_MEM, des_EX_MEM, memRef);
		}
		
		ID_EX = false;
		EX_MEM = true;
	}

	bool EX_IF;
	bool pc_EX_IF;

	bool EX_MEM;
	string ins_EX_MEM;
	Brick data_EX_MEM;
	Brick des_EX_MEM;

	Brick data_EX_MEM_8;

	istream& I;
	ostream& O;
	void MEM(const Program& pg) {
		if (!EX_MEM || MEM_WB) return;
		ins_MEM_WB = ins_EX_MEM;
		if (data_EX_MEM.type == Brick::Brick_type::ram1
			|| data_EX_MEM.type == Brick::Brick_type::ram2
			|| data_EX_MEM.type == Brick::Brick_type::ram4
			) {
			Brick temp;
			temp.type = Brick::Brick_type::imm;
			temp << data_EX_MEM;
			data_EX_MEM.fromNumber(temp.location);
		}
		if (des_EX_MEM.type == Brick::Brick_type::ram1
			|| des_EX_MEM.type == Brick::Brick_type::ram2
			|| des_EX_MEM.type == Brick::Brick_type::ram4
		) {
			des_EX_MEM << data_EX_MEM;
		}
		if (des_EX_MEM.type == Brick::Brick_type::reg || des_EX_MEM.type == Brick::Brick_type::lohi) {
			des_MEM_WB = des_EX_MEM;
			data_MEM_WB = data_EX_MEM;
		}
		if (ins_MEM_WB == "syscall") {
			int code = des_EX_MEM.location;
			des_MEM_WB = des_EX_MEM;
			switch (code) {
			case 1: {
				O << (int)data_EX_MEM.location;
				break;
			}
			case 4: {
				char* p = (char*)data_EX_MEM.location;
				while ((*p) != '\0') {
					O << (*p);
					++p;
				}
				break;
			}
			case 5: {
				des_MEM_WB.fromString("$v0", reg);
				int temp;
				I >> temp;
				data_MEM_WB.fromNumber(temp);
				break;
			}
			case 8: {
				I.get(reinterpret_cast<char*>(data_EX_MEM.location), data_EX_MEM_8.location);
				break;
			}
			case 9: {
				des_MEM_WB.fromString("$v0", reg);
				data_MEM_WB.fromNumber((unsigned long long)(ram + hp));
				sys9_MEM(data_EX_MEM.location);
				break;
			}
			}
		}

		EX_MEM = false;
		MEM_WB = true;
	}

	unsigned long long hp;
	void sys9_MEM(unsigned long long n) {
		hp += n;
	}

	bool MEM_WB;
	string ins_MEM_WB;
	Brick data_MEM_WB;
	Brick des_MEM_WB;

	void WB(const Program& pg) {
		if (!MEM_WB) return;
		if (ins_MEM_WB == "syscall") {
			if (des_MEM_WB.location == 5 || des_MEM_WB.location == 9) {
				des_MEM_WB << data_MEM_WB;
				regLock[des_MEM_WB.countReg(reg)] -= 1;
			}
		}
		if (wb_sheet.count(ins_MEM_WB)) {
			des_MEM_WB << data_MEM_WB;
			if (des_MEM_WB.type == Brick::Brick_type::lohi) {
				regLock[32] -= 1;
				regLock[33] -= 1;
			} else 
				regLock[des_MEM_WB.countReg(reg)] -= 1;
		}
		MEM_WB = false;
	}

	vector<char*> memRef;
public:
	CPU(istream& I, ostream& O) :I(I), O(O) {
		ram = new char[Memory];
	}
	~CPU() {
		delete[] ram;
	}

	int run(const Program& pg) {
		pc = pg.entry;
		memset(ram, 0, sizeof(ram));
		memset(reg, 0, sizeof(reg));
		memset(regLock, 0, sizeof(regLock));
		(*(findReg(29))) = reinterpret_cast<int>(ram + Memory);

		hp = 0;
		for (auto i : pg.lines) {
			memRef.push_back(ram + hp);
			if (i->type == Line::Line_type::tData) {
				sys9_MEM((reinterpret_cast<Data*>(i))->length);
			}
		}

		JR_LOCK = false;
		B_LOCK = false;
		IF_ID = false;
		ID_READY = false;
		ID_EX = false;
		ID_IF = false;
		EX_MEM = false;
		EX_IF = false;
		MEM_WB = false;
		nopCounter = 0;

		isOn = true;
		working = true;
		while (working) {
			//reverse later
			IF(pg);
			report();
			ID(pg);
			report();
			EX(pg);
			report();
			MEM(pg);
			report();
			WB(pg);
			report();
		}

		return (*findReg(idReg["$a0"]));
	}

	void report() {
		system("cls");
		cerr << "\n--------------------CPU STATE---------------------\n";
		cerr << "\n--------------------  IF-ID  ---------------------\n";
		cerr << "instruction:\t" << instruction_IF_ID.ins << '\n';
		for (int i = 0; i < instruction_IF_ID.arg.size(); i++) {
			cerr << "arg " << i << "\t" << instruction_IF_ID.arg[i] << '\n';
		}
		cerr << "-------  ID-EX  -------     ------  ID-IF  -------\n\n";
		cerr << "ins: " << setw(18) << ins_ID_EX; cerr << "     "; cerr << "new pc = " << pc_ID_IF << '\n';
		cerr << "data_send:\n";
		for (auto i : data_ID_EX) {
			cerr << "    " << i << '\n';
		}
		cerr << "destination:\t" << des_ID_EX << '\n';
		cerr << "\n--------------------  EX-MEM ---------------------\n";
		cerr << "ins: " << ins_EX_MEM << '\n';
		cerr << "data_send:\t" << data_EX_MEM << '\n';
		cerr << "destination:\t" << des_EX_MEM << '\n';
		cerr << "\n--------------------  MEM-WB ---------------------\n";
		cerr << "ins: " << ins_MEM_WB << '\n';
		cerr << "data_send:\t" << data_MEM_WB << '\n';
		cerr << "destination:\t" << des_MEM_WB << '\n';
		cerr << "\n--------------------   END   ---------------------\n";
	}
};

#endif