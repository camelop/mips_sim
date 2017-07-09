#ifndef littleround_oracle
#define littleround_oracle

#include <map>
#include <iostream>
#include <cstring>
using namespace std;

const int HashSize = 1009;

class SC {
	static char up;
	static char down;
public:
	char num;
	SC() :num(0) {}
	SC& operator --() {
		if (num > down) --num;
		return *this;
	}
	SC& operator ++() {
		if (num < up) ++num;
		return *this;
	}
	bool prefer() {
		return (num > 0);
	}
};

char SC::up = 2;
char SC::down = -1;

class Oracle {
	friend class CPU;
	int c_confirm, c_punish, c_consult;
	SC his[HashSize][16];
	int state[HashSize];
	int buff_pc[128];
	bool buff_choice[128];
	int s, t;
private:
	Oracle() {
		s = t = 0;
		c_confirm = c_punish = c_consult = 0;
		memset(state, 0, sizeof(state));
	}
	void confirm() {
		/*ofstream fout("ac_.out", ios::app | ios::out);
		fout << "¡Ì\n";
		fout.close();*/
	/*	++c_confirm;
		int& nw = buff_pc[s];
		if (buff_choice[s]) {
			++his[nw][state[nw]];
			state[nw] <<= 1;
			state[nw] &= 15;
			state[nw] |= 1;
		}
		else {
			--his[nw][state[nw]];
			state[nw] <<= 1;
			state[nw] &= 15;
		}
		++s; s &= 127;*/
	}
	void punish() {

		/*ofstream fout("ac_.out", ios::app | ios::out);
		fout <<"x\n";
		fout.close();*/
/*
		++c_punish;
		int& nw = buff_pc[s];
		if (!buff_choice[s]) {
			++his[nw][state[nw]];
			state[nw] <<= 1;
			state[nw] &= 15;
			state[nw] |= 1;
		}
		else {
			--his[nw][state[nw]];
			state[nw] <<= 1;
			state[nw] &= 15;
		}
		++s; s &= 127;*/
	}
	bool consult(int nw) {/*
		++c_consult;
		nw %= HashSize;
		buff_pc[t] = nw;
		buff_choice[t] = his[nw][state[nw]].prefer();
		++t; t &= 127;
		if (t == s - 1) cerr << "Oracle BUFFER NOT ENOUGH" << endl;*/

		/*ofstream fout("ac_.out",ios::app | ios::out);
		fout << nw << ' ' << buff_choice[t - 1] << '\n';
		fout.close();*/

		return false;
		//return buff_choice[t-1];
	}
	friend ostream& operator << (ostream& oo, const Oracle oracle) {
		//oo << oracle.c_confirm << ' ' << oracle.c_punish << endl;
		oo << "Consult:  " << oracle.c_consult <<'<'<<oracle.c_confirm<<','<<oracle.c_punish<< ">\n";
		oo << "Accuracy: " << 100.0 * (double)oracle.c_confirm / (double)oracle.c_consult << " %" << endl;
		return oo;
	}
};
#endif