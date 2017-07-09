#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU
#include<iostream>
#include<cstring>
#include<vector>
#ifdef littleround_multithread
#include<future>
#include<mutex>
#include<thread>
#include<atomic>
#endif
#include<map>


#include"line.hpp"
#include"program.hpp"
#include"Pack.hpp"
#include"oracle.hpp"

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

	Oracle oracle;

	bool IF(Pack* p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (JR_LOCK) return (nw.stage > 1);
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
			nw.judge = oracle.consult(pc);
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

	bool ID(Pack* p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		nw.lock = 100; //wow
		if (nw.stage > 2) return true;

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
			nw.lock = nw.reg[0];
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
			nw.arg[0] = reg[nw.reg[1]];
			nw.lock = nw.reg[0];
			break;
		}				
		case 32:
		{
			nw.lock = 31;
			break;
		}
		case 33:case 34:case 35:
		{
			if (regLock[nw.reg[0]]) return false;
			if (!nw.isLabel) {
				if (regLock[nw.reg[1]]) return false;
				nw.location = (char*)reg[nw.reg[1]];
			}
			nw.arg[1] = reg[nw.reg[0]];
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
			if (regLock[nw.reg[0]]) 
				return false;
			nw.label = reg[nw.reg[0]];
			nw.stage = 31; //special number
			return true;
		}

		}
		nw.stage = 3;
		return true;
	}

	bool EX(Pack* p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 3) return true;
		switch (nw.code) {
		case 2:case 3:case 4:
		case 10:
		case 33:case 34:case 35:
		{
			if (!nw.isLabel) nw.location = nw.location + nw.arg[0];
			break;
		}
		case 5:
		{
			nw.arg[0] = nw.arg[0] + nw.arg[1];
			break;
		}
		case 6:case 7:
		{
			nw.arg[0] = (unsigned int)nw.arg[0] + (unsigned int)nw.arg[1];
			break;
		}
		case 8:
		{
			if (nw.label == 3) {
				nw.arg[0] = nw.arg[0] / nw.arg[1];
			}
			else {
				int temp;
				temp = nw.arg[0] / nw.arg[1];
				nw.arg[1] = nw.arg[0] % nw.arg[1];
				nw.arg[0] = temp;
			}
			break;
		}
		case 9: {
			if (nw.label == 3) {
				nw.arg[0] = (unsigned int)nw.arg[0] / (unsigned int)nw.arg[1];
			}
			else {
				int temp;
				temp = (unsigned int)nw.arg[0] / (unsigned int)nw.arg[1];
				nw.arg[1] = (unsigned int)nw.arg[0] % (unsigned int)nw.arg[1];
				nw.arg[0] = temp;
			}
			break;
		}
		case 12: {
			if (nw.label == 3) {
				nw.arg[0] = nw.arg[0] * nw.arg[1];
			}
			else {
				long long temp = (long long)nw.arg[0] * (long long)nw.arg[1];
				nw.arg[0] = *(reinterpret_cast<int*>(&temp));
				nw.arg[1] = *((reinterpret_cast<int*>(&temp)) + 1);
			}
			break;
		}
		case 13: {
			if (nw.label == 3) {
				nw.arg[0] = (unsigned int)nw.arg[0] * (unsigned int)nw.arg[1];
			}
			else {
				unsigned long long temp = (unsigned long long)nw.arg[0] 
										* (unsigned long long)nw.arg[1];
				nw.arg[0] = *(reinterpret_cast<int*>(&temp));
				nw.arg[1] = *((reinterpret_cast<int*>(&temp)) + 1);
			}
			break;
		}
		case 14:case 15:
		{
			nw.arg[0] = -nw.arg[0];
			break;
		}
		case 16:
		{
			nw.arg[0] = nw.arg[0] % nw.arg[1];
			break;
		}
		case 17:
		{
			nw.arg[0] = (unsigned int)nw.arg[0] % (unsigned int)nw.arg[1];
			break;
		}
		case 18:
		{
			nw.arg[0] = (nw.arg[0] == nw.arg[1]) ? 1 : 0;
			break;
		}
		case 19:
		{
			nw.arg[0] = (nw.arg[0] >= nw.arg[1]) ? 1 : 0;
			break;
		}
		case 20:
		{
			nw.arg[0] = (nw.arg[0] > nw.arg[1]) ? 1 : 0;
			break;
		}
		case 21:
		{
			nw.arg[0] = (nw.arg[0] <= nw.arg[1]) ? 1 : 0;
			break;
		}
		case 22:
		{
			nw.arg[0] = (nw.arg[0] < nw.arg[1]) ? 1 : 0;
			break;
		}
		case 23:
		{
			nw.arg[0] = (nw.arg[0] != nw.arg[1]) ? 1 : 0;
			break;
		}
		case 24: {
			nw.arg[0] = nw.arg[0] - nw.arg[1];
			break;
		}
		case 25: {
			nw.arg[0] = (unsigned int)nw.arg[0] - (unsigned int)nw.arg[1];
			break;
		}
		case 26:case 27: 
		{
			nw.arg[0] = nw.arg[0] ^ nw.arg[1];
			break;
		}
		case 36:case 37: 
		{
			if (nw.judge != (nw.arg[0] == nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}
		case 38:case 39:
		{
			if (nw.judge != (nw.arg[0] >= nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}
		case 40:case 41:
		{
			if (nw.judge != (nw.arg[0] > nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}
		case 42:case 43:
		{
			if (nw.judge != (nw.arg[0] <= nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}
		case 44:case 45:
		{
			if (nw.judge != (nw.arg[0] < nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}
		case 46:case 47:
		{
			if (nw.judge != (nw.arg[0] != nw.arg[1])) {
				nw.stage = 41;
				oracle.punish();
				return true;
			}
			else oracle.confirm();
			break;
		}

		}
		nw.stage = 4;
		return true;
	}

	bool MEM(Pack* p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 4) return true;
		switch (nw.code) {
		case 1: {
			switch (nw.arg[0]) {
			case 1: {
				O << nw.arg[1];
				break;
			}
			case 4: {
				char* p = nw.location;
				while ((*p) != '\0') {
					O << (*p);
					++p;
				}
				break;
			}
			case 5: {
				I >> nw.arg[1];
				char ch = I.get();
				break;
			}
			case 8: {
				I.get(nw.location, nw.arg[1] + 1);
				char ch = I.get();
				break;
			}
			case 9: {
				nw.location = ram + hp;
				hp += nw.arg[1];
				break;
			}

			}
			break;
		}
		case 2: {
			nw.arg[0] = (int)(*(reinterpret_cast<unsigned char*>(nw.location)));
			break;
		}
		case 3: {
			nw.arg[0] = (int)(*(reinterpret_cast<unsigned short*>(nw.location)));
			break;
		}
		case 4: {
			nw.arg[0] = (*(reinterpret_cast<int*>(nw.location)));
			break;
		}
		case 33: {
			(*nw.location) = nw.arg[1];
			break;
		}
		case 34: {
			(*(reinterpret_cast<short*>(nw.location))) = nw.arg[1];
			break;
		}
		case 35: {
			(*(reinterpret_cast<int*>(nw.location))) = nw.arg[1];
			break;
		}

		}
		nw.stage = 5;
		return true;
	}

	int Ret;
	bool WB(Pack* p) {
		if (p == NULL) return false;
		Pack& nw(*p);
		if (nw.stage > 5) return true;
		switch (nw.code) {
		case 1: {
			switch (nw.arg[0]) {
			case 5: {
				reg[2] = nw.arg[1];
				--regLock[2];
				break;
			}
			case 9: {
				reg[2] = (int)nw.location;
				--regLock[2];
				break;
			}
			case 10: {
				Ret = 0;
				break;
			}
			case 17: {
				Ret = nw.arg[1];
				break;
			}
			}
			break;
		}
		case 2:case 3:case 4:
		case 5:case 6:case 7:
		case 11:
		case 14:case 15:
		case 16:case 17:
		case 18:case 19:case 20:case 21:case 22:case 23:
		case 24:case 25:case 26:case 27:
		case 31:
		{
			reg[nw.reg[0]] = nw.arg[0];
			--regLock[nw.reg[0]];
			break;
		}
		case 8:case 9:
		case 12:case 13:
		{
			if (nw.label == 3) {
				reg[nw.reg[0]] = nw.arg[0];
				--regLock[nw.reg[0]];
			}
			else {
				reg[32] = nw.arg[0];
				--regLock[32];
				reg[33] = nw.arg[1];
				--regLock[33];
			}
			break;
		}
		case 10: {
			reg[nw.reg[0]] = (int)nw.location;
			--regLock[nw.reg[0]];
			break;
		}
		case 28:case 32: 
		{
			reg[31] = nw.arg[0];
			--regLock[31];
			break;
		}
		case 29:case 30: 
		{
			reg[nw.reg[0]] = nw.arg[0];
			--regLock[nw.reg[0]];
			break;
		}

		}
		p = NULL;
		return true;
	}
 
#ifdef littleround_strict
	int strict_charge;
#endif

#ifdef littleround_multithread
	bool b_IF, b_ID, b_EX, b_MEM, b_WB;
	Pack *p_IF, *p_ID, *p_EX, *p_MEM, *p_WB;
	bool a_IF, a_ID, a_EX, a_MEM, a_WB;
	void f_IF() {
		while (Ret < 0) {
			while (a_IF) this_thread::yield();
			b_IF = IF(p_IF);
			a_IF = true;
		}
	}
	void f_ID() {
		while (Ret < 0) {
			while (a_ID) this_thread::yield();
			b_ID = ID(p_ID);
			a_ID = true;
		}
	}
	void f_EX() {
		while (Ret < 0) {
			while (a_EX) this_thread::yield();
			b_EX = EX(p_EX);
			a_EX = true;
		}
	}
	void f_MEM() {
		while (Ret < 0) {
			while (a_MEM) this_thread::yield();
			b_MEM = MEM(p_MEM);
			a_MEM = true;
		}

	}
	void f_WB() {
		while (Ret < 0) {
			while (a_WB) this_thread::yield();
			b_WB = WB(p_WB);
			a_WB = true;
		}
	}
#endif
	int cyc;

	void dispatch(const vector<Pack>& vp) {
		Pack use[5];
#ifndef littleround_multithread
		bool b_IF, b_ID, b_EX, b_MEM, b_WB;
		Pack *p_IF, *p_ID, *p_EX, *p_MEM, *p_WB;
#else
		a_IF = true; a_ID = true; 
		a_EX = true; a_MEM = true; 
		a_WB = true;
		thread t_IF(&CPU::f_IF, this);
		thread t_ID(&CPU::f_ID, this);
		thread t_EX(&CPU::f_EX, this);
		thread t_MEM(&CPU::f_MEM, this);
		thread t_WB(&CPU::f_WB, this);
#endif
		while (vp[pc].code == 0) {
			++pc;
			if (pc > (int)vp.size()) {
				/*O << "Invalid Program!" << endl;
				return;*/
				--pc;
			}
		}
		p_IF = use; p_ID = NULL; p_EX = NULL;
		p_MEM = NULL; p_WB = NULL;
		(*p_IF) = vp[pc];

#ifdef littleround_strict
		strict_charge = 0;
#endif
		while (true) {
#ifdef littleround_multithread
			/*future<bool> f_IF = async(launch::async, &CPU::IF, this, p_IF);
			future<bool> f_ID = async(launch::async, &CPU::ID, this, p_ID);
			future<bool> f_EX = async(launch::async, &CPU::EX, this, p_EX);
			future<bool> f_MEM = async(launch::async, &CPU::MEM, this, p_MEM);
			future<bool> f_WB = async(launch::async, &CPU::WB, this, p_WB);
			b_IF = f_IF.get();
			b_ID = f_ID.get();
			b_EX = f_EX.get();
			b_MEM = f_MEM.get();
			b_WB = f_WB.get();*/
			a_IF = false; a_ID = false; a_EX = false; a_MEM = false; a_WB = false;
			while (!a_IF) this_thread::yield();
			while (!a_ID) this_thread::yield();
			while (!a_EX) this_thread::yield();
			while (!a_MEM) this_thread::yield();
			while (!a_WB) this_thread::yield();

#else
  			b_IF = IF(p_IF);
			b_ID = ID(p_ID);
			b_EX = EX(p_EX);
			b_MEM = MEM(p_MEM);
			b_WB = WB(p_WB);
#endif		
			++cyc;
			if (b_WB) p_WB = NULL;
			//do some trick to avoid mutex
			//stage41-wrong fetch
			if (p_EX != NULL && p_EX->stage == 41) {
				p_EX->stage = 4;
				p_IF = NULL; p_ID = NULL;
				b_IF = false; b_ID = false;
				JR_LOCK = false;
				pc = p_EX->label;
				//protect the oracle!
				oracle.s = oracle.t;
			}
			//lock (lock 35)
			if (p_ID != NULL && p_ID->lock < 40) {
				if (p_ID->lock == 35) {
					++regLock[32];
					++regLock[33];
				}
				else {
					++regLock[p_ID->lock];
				}
			}
			//stage31-unlock
			if (p_ID != NULL && p_ID->stage == 31) {
				p_ID->stage = 3;
				pc = p_ID->label;
				p_IF = NULL; b_IF = false;
				JR_LOCK = false;
			}
			//Ret
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
			if (p_IF == NULL && isOn) {
				if (!isOn) { continue; }
				//cout << pc << endl;
#ifdef littleround_strict
				++strict_charge;
				if (strict_charge < 6) continue;
				strict_charge = 0;
#endif
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
					if (pc > (int)vp.size()) {
						/*O << "Invalid Program!" << endl;
						return;*/
						--pc;
					}
				}
				(*p_IF) = vp[pc];
			}

			//isOn
			if (!isOn) p_IF = NULL;
			//out
			if (Ret > -1) {
				p_IF = p_ID = p_EX = p_MEM = p_WB = NULL;
				a_IF = false; a_ID = false; a_EX = false; a_MEM = false; a_WB = false;
				t_IF.join();
				t_ID.join();
				t_EX.join();
				t_MEM.join();
				t_WB.join();
				return;
			}
		}
	}

	int run(const Program& pg) {
		pc = pg.entry;
		memset(ram, 0, Memory);
		memset(reg, 0, sizeof(reg));
		for (int i = 0; i < 34; i++) regLock[i] = 0;
		reg[29] = (int)(ram + Memory);
		hp = 0;

		nop = 0;
		JR_LOCK = false;
		isOn = true;
		Ret = -1;
		cyc = 0;

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
				hp += (int)nw->length;
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
					toPush.arg[0] = fromStringToNumber(nw->arg[1]);
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
					if (nw->arg[1][0] == '$') { toPush.reg[1] = idReg[nw->arg[1]]; toPush.isImm = false; }
					else { toPush.arg[1] = fromStringToNumber(nw->arg[1]); toPush.isImm = true; }
					toPush.label = fromStringToNumber(nw->arg[2]);
					break;
				}
				case 37:case 39:case 41:case 43:case 45:case 47:
				{
					toPush.reg[0] = idReg[nw->arg[0]];
					toPush.isImm = true; toPush.arg[1] = 0;
					toPush.label = fromStringToNumber(nw->arg[1]);
					break;
				}
				}
			}
			}
			vp.push_back(toPush);
		}
		for (int i = 0; i < vp.size(); i++) {
			if (vp[i].code == 2 || vp[i].code == 3 || vp[i].code == 4 ||
				vp[i].code == 10 || vp[i].code == 33 || vp[i].code == 34 ||
				vp[i].code == 35) {
				if (vp[i].isLabel) vp[i].location = memRef[vp[i].label];
			}
		}
		dispatch(vp);
		//ofstream ac("ac.out");
		//ac << oracle;
		return Ret;
	}
};
#endif