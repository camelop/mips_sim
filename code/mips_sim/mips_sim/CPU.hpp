#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU
#include<iostream>
#include<cstring>
#include<vector>
#include<future>
#include<map>


#include"line.hpp"
#include"program.hpp"
#include"Pack.hpp"

extern const int Memory;

extern map<string, int> idReg;

class CPU {
private:
	istream& I;
	ostream& O;

	char* ram;
	int reg[34];
	int regLock[34];
	vector<char*> memRef;

	int pc;

	int hp;
public:
	CPU(istream& I, ostream& O) :I(I), O(O) { ram = new char[Memory]; }
	~CPU() { delete[] ram; }

	int nop;
	bool JR_LOCK;
	bool IF(Pack* &p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (JR_LOCK) return false;
		if (nop > 0) {
			--nop;
			return false;
		}
		if (nw.stage > 1) return true;

		switch (nw.code) {
		case 28:{
			nw.arg[0] = pc + 1;
			JR_LOCK = true;
			break;
		}
		case 32:{
			nw.arg[0] = pc + 1;
			pc = nw.label;
			break;
		}				
		case 36:case 38:case 40:case 42:case 44:case 46:
		case 37:case 39:case 41:case 43:case 45:case 47:
		{
			nw.judge = false;
			if (nw.judge) {
				int temp = nw.label;
				nw.label = pc + 1;
				pc = temp;
			}
			else {
				++pc;
			}
			break;
		}
		case 48: {
			JR_LOCK = true;
			break;
		}
		case 49: case 50:
		{
			pc = nw.label;
			break;
		}
		case 51: {
			nop = 5;
			++pc;
			break;
		}
		default: {
			++pc;
			break;
		}
		}

		nw.stage = 2;
		return true;
	}

	bool isOn;

	bool ID(Pack* &p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 2) return true;

		nw.lock = 100; //wow
		switch (nw.code) {
		case 1: {
			if (regLock[2]) return false;
			nw.arg[0] = reg[2];
			switch (nw.arg[0]) {
			case 1:
			{
				if (regLock[4]) return false;
				nw.arg[1] = reg[4];
				break;
			}
			case 4: {
				if (regLock[4]) return false;
				nw.location = (char*)reg[4];
				break;
			}
			case 5: {
				nw.lock = 2;
				break;
			}
			case 8: {
				if (regLock[4]) return false;
				if (regLock[5]) return false;
				nw.location = (char*)reg[4];
				nw.arg[1] = reg[5];
				break;
			}
			case 9:
			{
				if (regLock[4]) return false;
				nw.arg[1] = reg[4];
				nw.lock = 2;
				break;
			}
			case 10: {
				isOn = false;
				break;
			}
			case 17: {
				if (regLock[4]) return false;
				nw.arg[1] = reg[4];
				isOn = false;
				break;
			}
			}
			break;
		}
		case 2:case 3:case 4: 
		case 10:
		case 33:case 34:case 35:
		{
			if (!nw.isLabel) {
				if (regLock[nw.reg[1]]) return false;
				nw.location = (char*)reg[nw.reg[1]];
			}
			nw.lock = nw.reg[0];
			break;
		}
		case 5:case 6:case 7: 
		case 16:case 17:
		case 18:case 19:case 20:case 21:case 22:case 23:
		case 24:case 25:
		case 26:case 27:
		{
			if (regLock[nw.reg[1]]) return false;
			if (!nw.isImm && regLock[nw.reg[2]]) return false;
			nw.lock = nw.reg[0];
			nw.arg[0] = reg[nw.reg[1]];
			if (!nw.isImm) nw.arg[1] = reg[nw.reg[2]];
			break;
		}
		case 8:case 9:
		case 12:case 13:
		{
			if (nw.label == 3) {
				if (regLock[nw.reg[1]]) return false;
				if (!nw.isImm && regLock[nw.reg[2]]) return false;
				nw.lock = nw.reg[0];
				nw.arg[0] = reg[nw.reg[1]];
				if (!nw.isImm) nw.arg[1] = reg[nw.reg[2]];
			}
			else {
				if (regLock[nw.reg[0]]) return false;
				if (!nw.isImm && regLock[nw.reg[1]]) return false;
				nw.lock = 35; //special
				nw.arg[0] = reg[nw.reg[0]];
				if (!nw.isImm) nw.arg[1] = reg[nw.reg[1]];
			}
			break;
		}
		case 11:
		{
			if (regLock[nw.reg[0]]) return false;
			nw.arg[0] = reg[nw.reg[0]];
			break;
		}
		case 14:case 15:
		case 31:
		{
			if (regLock[nw.reg[1]]) return false;
			nw.lock = nw.reg[0];
			nw.arg[0] = reg[nw.reg[1]];
			break;
		}
		case 28:
		{
			if (regLock[nw.reg[0]]) return false;
			nw.label = reg[nw.reg[0]];
			nw.lock = 31;
			nw.stage = 31; //special number
			return true;
		}
		case 29:case 30: 
		{
			if (regLock[nw.reg[1]]) return false;
			nw.lock = nw.reg[0];
			break;
		}				
		case 32:
		{
			nw.lock = 31;
			break;
		}
		case 36:case 38:case 40:case 42:case 44:case 46:
		case 37:case 39:case 41:case 43:case 45:case 47:
		{
			if (regLock[nw.reg[0]]) return false;
			if (!nw.isImm && regLock[nw.reg[1]]) return false;
			nw.arg[0] = reg[nw.reg[0]];
			if (!nw.isImm) {
				nw.arg[1] = reg[nw.reg[1]];
			}
			break;
		}
		case 48:
		{
			if (regLock[nw.reg[0]]) return false;
			nw.label = reg[nw.reg[0]];
			nw.stage = 31; //special number
			return true;
		}

		}
		nw.stage = 3;
		return true;
	}

	bool EX(Pack* &p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 3) return true;
		switch (nw.code) {
		case 2:case 3:case 4:
		case 10:
		case 33:case 34:case 35:
		{
			if (nw.isLabel) {
				nw.location = memRef[nw.label];
			}
			else {
				nw.location = nw.location + nw.arg[0];
			}
			break;
		}
		case 5:case 6:case 7:
		{
			nw.arg[0] = nw.arg[0] + nw.arg[1];
			break;
		}
		case 8:
		{
			if (nw.label == 3) {
				nw.arg[0] = nw.arg[0] / nw.arg[1];
			}
			else {
				//todo
			}
			break;
		}




		}
		nw.stage = 4;
		return true;
	}

	bool MEM(Pack* &p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 4) return true;
		switch (nw.code) {

		}
		nw.stage = 5;
		return true;
	}

	bool WB(Pack* &p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 5) return true;
		switch (nw.code) {
			 
		}
		p = NULL;
		return true;
	}
 
	void dispatch(const vector<Pack>& vp) {
		Pack use[5];
		bool b_IF, b_ID, b_EX, b_MEM, b_WB;
		Pack *p_IF, *p_ID, *p_EX, *p_MEM, *p_WB;

		while (vp[pc].code == 0) {
			++pc;
			if (pc > vp.size()) {
				O << "Invalid Program!" << endl;
				return;
			}
		}
		p_IF = use; p_ID = NULL; p_EX = NULL;
		p_MEM = NULL; p_WB = NULL;
		(*p_IF) = vp[pc];

		while (true) {
			p_IF = NULL;
			p_ID = NULL;
			p_EX = NULL;
			p_MEM = NULL;
			p_WB = NULL;
#ifdef littleround_multiThread
			future<bool> f_IF = async(launch::async, &CPU::IF, this, p_IF);
			future<bool> f_ID = async(launch::async, &CPU::ID, this, p_ID);
			future<bool> f_EX = async(launch::async, &CPU::EX, this, p_EX);
			future<bool> f_MEM = async(launch::async, &CPU::MEM, this, p_MEM);
			future<bool> f_WB = async(launch::async, &CPU::WB, this, p_WB);
			b_IF = f_IF.get();
			b_ID = f_ID.get();
			b_EX = f_EX.get();
			b_MEM = f_MEM.get();
			b_WB = f_WB.get();
#else
			b_IF = IF(p_IF);
			b_ID = IF(p_ID);
			b_EX = IF(p_EX);
			b_MEM = IF(p_MEM);
			b_WB = IF(p_WB);
#endif

			//do some trick to avoid mutex
			//lock (lock 35)
			//stage31-unlock
			//isOn
			if (p_WB == NULL && b_MEM) {
				p_WB = p_MEM; p_MEM = NULL;
			}
			if (p_MEM == NULL && b_EX) {
				p_MEM = p_EX; p_EX = NULL;
			}
			if (p_EX == NULL && b_ID) {
				p_EX = p_ID; p_ID = NULL;
			}
			if (p_ID == NULL && b_IF) {
				p_ID = p_IF; p_IF = NULL;
			}
			if (p_IF == NULL) {
				if (!isOn) { continue; }
				for (int i = 0; i < 5; i++) {
					if (use + i == p_WB) continue;
					if (use + i == p_EX) continue;
					if (use + i == p_ID) continue;
					if (use + i == p_MEM) continue;
					p_IF = use + i;
					break;
				}
				while (vp[pc].code == 0) {
					++pc;
					if (pc > vp.size()) {
						O << "Invalid Program!" << endl;
						return;
					}
				}
				(*p_IF) = vp[pc];
			}
		}
	}

	void run(const Program& pg) {
		pc = pg.entry;
		memset(ram, 0, sizeof(ram));
		memset(reg, 0, sizeof(reg));
		for (int i = 0; i < 34; i++) regLock[i] = 0;
		reg[29] = (int)(ram + Memory);
		hp = 0;

		nop = 0;
		JR_LOCK = false;
		isOn = true;
		//init pg
		vector<Pack> vp; vp.clear();
		for (auto& i : pg.lines) {
			memRef.push_back(ram + hp);
			Pack toPush;
			switch (i->type) {
			case Line::Line_type::tLabel: {
				toPush.code = 0; break;
			}
			case Line::Line_type::tData: {
				toPush.code = 0;
				Data* nw = (Data*)(i);
				switch (nw->dType) {
				case Data::Data_type::ascii: {
					for (int i = 0; i < nw->length; ++i) ram[hp + i] = nw->arg[0][i];
					break;
				}
				case Data::Data_type::asciiz: {
					for (int i = 0; i < nw->length; ++i) ram[hp + i] = nw->arg[0][i];
					ram[hp + nw->length] = '\0';
					break;
				}
				case Data::Data_type::byte: {
					(*(reinterpret_cast<short*>(ram + hp))) = fromStringToNumber(nw->arg[0]);
					break;
				}
				case Data::Data_type::half: {
					(*(reinterpret_cast<char*>(ram + hp))) = fromStringToNumber(nw->arg[0]);
					break;
				}
				case Data::Data_type::word: {
					(*(reinterpret_cast<int*>(ram + hp))) = fromStringToNumber(nw->arg[0]);
					break;
				}
				}
				hp += nw->length;
			}
			case Line::Line_type::tFrame: {
				toPush.code = 0; break;
			}
			case Line::Line_type::tInstruction: {
				Instruction* nw = (Instruction*)(i);
				toPush.code = toCode[nw->ins];
				switch (toPush.code) {
				case 2:case 3:case 4:
				case 10:
				case 33:case 34:case 35:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					int pos = nw->arg[1].find('(');
					toPush.isLabel = (pos == string::npos);
					if (toPush.isLabel) {
						toPush.label = fromStringToNumber(nw->arg[1]);
					}
					else {
						toPush.reg[1] = idReg[nw->arg[1].substr(pos + 1, nw->arg[1].find(')') - pos - 1)];
						toPush.arg[0] = fromStringToNumber(nw->arg[1].substr(0, pos));
					}
					break;
				}
				case 5:case 6:case 7:
				case 16:case 17:
				case 18:case 19:case 20:case 21:case 22:case 23:
				case 24:case 25:
				case 26:case 27:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.reg[1] = idReg[nw->arg[1]];
					if (nw->arg[2][0] == '$') { toPush.reg[2] = idReg[nw->arg[2]]; toPush.isImm = false; }
					else { toPush.arg[1] = fromStringToNumber(nw->arg[2]); toPush.isImm = true; }
					break;
				}
				case 8:case 9:
				case 12:case 13:
				{
					if (nw->arg.size() == 3) {
						toPush.label = 3;
						toPush.reg[0] = idReg[nw->arg[0]];
						toPush.reg[1] = idReg[nw->arg[1]];
						if (nw->arg[2][0] == '$') { toPush.reg[2] = idReg[nw->arg[2]]; toPush.isImm = false; }
						else { toPush.arg[1] = fromStringToNumber(nw->arg[2]); toPush.isImm = true; }
					}
					else {
						toPush.label = 2;
						toPush.reg[0] = idReg[nw->arg[0]];		
						if (nw->arg[1][0] == '$') { toPush.reg[1] = idReg[nw->arg[1]]; toPush.isImm = false; }
						else { toPush.arg[1] = fromStringToNumber(nw->arg[1]); toPush.isImm = true; }

					}
					break;
				}
				case 11: {					
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.arg[1] = fromStringToNumber(nw->arg[1]);
					break;
				}
				case 14:case 15:
				case 31:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.reg[1] = idReg[nw->arg[1]];
					break;
				}
				case 28:
				case 48:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					break;
				}
				case 29: {
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.reg[1] = 33;
					break;
				}
				case 30: {
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.reg[1] = 32;
					break;
				}
				case 32:
				case 49:case 50:
				{
					toPush.label = fromStringToNumber(nw->arg[0]);
					break;
				}
				case 36:case 38:case 40:case 42:case 44:case 46:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					if (nw->arg[1][0] == '$') { toPush.reg[2] = idReg[nw->arg[1]]; toPush.isImm = false; }
					else { toPush.arg[1] = fromStringToNumber(nw->arg[1]); toPush.isImm = true; }
					toPush.label = fromStringToNumber(nw->arg[2]);
					break;
				}
				case 37:case 39:case 41:case 43:case 45:case 47:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.arg[1] = 0;
					toPush.label = fromStringToNumber(nw->arg[1]);
					break;
				}
				}
			}
			}
			vp.push_back(toPush);
		}

		dispatch(vp);
	}
};
#endif