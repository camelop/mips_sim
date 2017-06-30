#ifndef littleround_MIPS_op
#define littleround_MIPS_op

#include<iostream>
#include "program.hpp"
#include<string>
#include<vector>
#include<set>
#include<map>
#include<cstring>
#include "brick.hpp"
using namespace std;

extern set<string> type_ls_sheet;

class Op {
public:
	Op(
		const string& Iins,
		const vector<Brick>& Idata,
		const Brick& Ides,
		string& Oins,
		Brick& Odata,
		Brick& Odes,
		vector<char*>& memRef
	) {
		Oins = Iins;
		const string& ins = Iins;
		if (ins == "add" || ins == "addu" || ins == "addiu") {
			Odes = Ides;
			Odata.fromNumber((int)Idata[0].location + (int)Idata[1].location);
			return;
		}
		if (ins == "sub" || ins == "subu") {
			Odes = Ides;
			Odata.fromNumber((int)Idata[0].location - (int)Idata[1].location);
			return;
		}
		if (ins == "mul") {
			Odes = Ides;
			if (Odes.type == Brick::Brick_type::lohi) {
				Odata.fromNumber(
					(long long)((int)Idata[0].location) *
					(long long)((int)Idata[1].location)
					);
			}
			else {
				Odes = Ides;
				Odata.fromNumber((int)((int)Idata[0].location * (int)Idata[1].location));
			}
			return;
		}
		if (ins == "mulu") {
			Odes = Ides;
			if (Odes.type == Brick::Brick_type::lohi) {
				Odata.fromNumber(
					(long long)((unsigned int)Idata[0].location) *
					(long long)((unsigned int)Idata[1].location)
					);
			}
			else {
				Odes = Ides;
				Odata.fromNumber((unsigned int)Idata[0].location * (unsigned int)Idata[1].location);
			}
			return;
		}
		if (ins == "div") {
			Odes = Ides;
			if (Odes.type == Brick::Brick_type::lohi) {
				unsigned long long temp = 0;
				int* pint = reinterpret_cast<int*>(&temp);
				(*pint) = (int)Idata[0].location / (int)Idata[1].location;
				pint++;
				(*pint) = (int)Idata[0].location % (int)Idata[1].location;
				Odata.fromNumber(temp);
			}
			else {
				Odes = Ides;
				Odata.fromNumber((int)((int)Idata[0].location / (int)Idata[1].location));
			}
			return;
		}
		if (ins == "divu") {
			Odes = Ides;
			if (Odes.type == Brick::Brick_type::lohi) {
				unsigned long long temp = 0;
				unsigned int* pint = reinterpret_cast<unsigned int*>(&temp);
				(*pint) = (unsigned int)Idata[0].location / (unsigned int)Idata[1].location;
				pint++;
				(*pint) = (unsigned int)Idata[0].location % (unsigned int)Idata[1].location;
				Odata.fromNumber(temp);
			}
			else {
				Odes = Ides;
				Odata.fromNumber((unsigned int)Idata[0].location / (unsigned int)Idata[1].location);
			}
			return;
		}
		if (ins == "xor" || ins=="xoru") {
			Odes = Ides;
			Odata.fromNumber((int)Idata[0].location ^ (int)Idata[1].location);
			return;
		}
		if (ins == "neg" || ins == "negu") {
			Odes = Ides;
			Odata.fromNumber(-((int)Idata[0].location));
			return;
		}
		if (ins == "rem") {
			Odes = Ides;
			Odata.fromNumber((int)Idata[0].location % (int)Idata[1].location);
			return;
		}
		if (ins == "remu") {
			Odes = Ides;
			Odata.fromNumber((unsigned int)Idata[0].location % (unsigned int)Idata[1].location);
			return;
		}
		if (ins == "li" || ins == "move" || ins == "mfhi" || ins == "mflo") {
			Odes = Ides;
			Odata.fromNumber(Idata[0].location);
			return;
		}
		if (ins == "seq") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) ==
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "sge") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) >=
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "sgt") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) >
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "sle") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) <=
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "slt") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) <
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "sne") {
			Odes = Ides;
			Odata.fromNumber((
				((int)Idata[0].location) !=
				((int)Idata[1].location)
				));
			return;
		}
		if (ins == "jal" || ins == "jalr") {
			Odes = Ides;
			Odata = Idata[0];
			return;
		}
		if (type_ls_sheet.count(ins)) {
			char* temp;
			if (Idata.size() > 1) {
				temp = reinterpret_cast<char*>((int)Idata[0].location);
				temp = temp + (int)(Idata[1].location);
			}
			else {
				temp = memRef[(unsigned int)Idata[0].location];
			}
			if (ins[0] == 'l') {
				Odata.fromNumber((unsigned long long)temp);
				Odes = Ides;
				if (ins[1] == 'b') {
					Odata.type = Brick::Brick_type::ram1;
					Odes.type = Brick::Brick_type::reg;
				}
				else
					if (ins[1] == 'h') {
						Odata.type = Brick::Brick_type::ram2;
						Odes.type = Brick::Brick_type::reg;
					}
					else
						if (ins[1] == 'w') {
							Odata.type = Brick::Brick_type::ram4;
							Odes.type = Brick::Brick_type::reg;
						}
						else {
							Odata.type = Brick::Brick_type::imm;
							Odes.type = Brick::Brick_type::reg;
						}
			}
			else {
				Odata = Ides;
				Odes.fromNumber((unsigned long long)temp);
				if (ins[1] == 'b') {
					Odata.type = Brick::Brick_type::reg;
					Odes.type = Brick::Brick_type::ram1;
				} else
					if (ins[1] == 'h') {
						Odata.type = Brick::Brick_type::reg;
						Odes.type = Brick::Brick_type::ram2;
					} else 
						if (ins[1] == 'w') {
							Odata.type = Brick::Brick_type::reg;
							Odes.type = Brick::Brick_type::ram4;
						}
			}
			return;
		}
	}
};
#endif