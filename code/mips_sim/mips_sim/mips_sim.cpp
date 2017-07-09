#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

//#define PYTHON_TEST
//#define littleround_profile
#define littleround_multithread
//#define littleround_strict

class Line;
class Data; class Instruction; class Label; class Frame;
class Program;
class CPU;
class Pack;
class Oracle;

#include "line.hpp"
#include "program.hpp"
#include "CPU.hpp"

#define MIPS_TEST1

using namespace std;

map<string, Line::Line_type> findType;
map<string, Data::Data_type> find_dType;
set<string> label_1_sheet;
set<string> label_2_sheet;
set<string> label_2_check_sheet;
set<string> label_3_sheet;

map<string, int> idReg;
map<string, int> toCode;

extern const int Memory = 4 * 1024 * 1024;

void init() {
	//init toCode
	toCode["syscall"]=1;
	toCode["lb"] = 2;
	toCode["lh"] = 3;
	toCode["lw"] = 4;
	toCode["add"] = 5;
	toCode["addiu"] = 6;
	toCode["addu"] = 7;
	toCode["div"] = 8;
	toCode["divu"] = 9;
	toCode["la"] = 10;
	toCode["li"] = 11;
	toCode["mul"] = 12;
	toCode["mulu"] = 13;
	toCode["neg"] = 14;
	toCode["negu"] = 15;
	toCode["rem"] = 16;
	toCode["remu"] = 17;
	toCode["seq"] = 18;
	toCode["sge"] = 19;
	toCode["sgt"] = 20;
	toCode["sle"] = 21;
	toCode["slt"] = 22;
	toCode["sne"] = 23;
	toCode["sub"] = 24;
	toCode["subu"] = 25;
	toCode["xor"] = 26;
	toCode["xoru"] = 27;
	toCode["jalr"] = 28;
	toCode["mfhi"] = 29;
	toCode["mflo"] = 30;
	toCode["move"] = 31;
	toCode["jal"] = 32;
	toCode["sb"] = 33;
	toCode["sh"] = 34;
	toCode["sw"] = 35;
	toCode["beq"] = 36;
	toCode["beqz"] = 37;
	toCode["bge"] = 38;
	toCode["bgez"] = 39;
	toCode["bgt"] = 40;
	toCode["bgtz"] = 41;
	toCode["ble"] = 42;
	toCode["blez"] = 43;
	toCode["blt"] = 44;
	toCode["bltz"] = 45;
	toCode["bne"] = 46;
	toCode["bnez"] = 47;
	toCode["jr"] = 48;
	toCode["b"] = 49;
	toCode["j"] = 50;
	toCode["nop"] = 51;

	//init idReg
	idReg["$0"] = 0;
	idReg["$1"] = 1;
	idReg["$2"] = 2;
	idReg["$3"] = 3;
	idReg["$4"] = 4;
	idReg["$5"] = 5;
	idReg["$6"] = 6;
	idReg["$7"] = 7;
	idReg["$8"] = 8;
	idReg["$9"] = 9;
	idReg["$10"] = 10;
	idReg["$11"] = 11;
	idReg["$12"] = 12;
	idReg["$13"] = 13;
	idReg["$14"] = 14;
	idReg["$15"] = 15;
	idReg["$16"] = 16;
	idReg["$17"] = 17;
	idReg["$18"] = 18;
	idReg["$19"] = 19;
	idReg["$20"] = 20;
	idReg["$21"] = 21;
	idReg["$22"] = 22;
	idReg["$23"] = 23;
	idReg["$24"] = 24;
	idReg["$25"] = 25;
	idReg["$26"] = 26;
	idReg["$27"] = 27;
	idReg["$28"] = 28;
	idReg["$29"] = 29;
	idReg["$30"] = 30;
	idReg["$31"] = 31;
	idReg["$32"] = 32;
	idReg["$33"] = 33;

	idReg["$zero"] = 0;
	idReg["$at"] = 1;
	idReg["$v0"] = 2;
	idReg["$v1"] = 3;
	idReg["$a0"] = 4;
	idReg["$a1"] = 5;
	idReg["$a2"] = 6;
	idReg["$a3"] = 7;
	idReg["$t0"] = 8;
	idReg["$t1"] = 9;
	idReg["$t2"] = 10;
	idReg["$t3"] = 11;
	idReg["$t4"] = 12;
	idReg["$t5"] = 13;
	idReg["$t6"] = 14;
	idReg["$t7"] = 15;
	idReg["$s0"] = 16;
	idReg["$s1"] = 17;
	idReg["$s2"] = 18;
	idReg["$s3"] = 19;
	idReg["$s4"] = 20;
	idReg["$s5"] = 21;
	idReg["$s6"] = 22;
	idReg["$s7"] = 23;
	idReg["$t8"] = 24;
	idReg["$t9"] = 25;
	idReg["$k0"] = 26;
	idReg["$k1"] = 27;
	idReg["$gp"] = 28;
	idReg["$sp"] = 29;
	idReg["$s8"] = 30;
	idReg["$fp"] = 30;
	idReg["$ra"] = 31;
	idReg["$lohi"] = 32;
	idReg["$lo"] = 32;
	idReg["$hi"] = 33;

	//init label_1_sheet
	label_1_sheet.insert("j");
	label_1_sheet.insert("b");
	label_1_sheet.insert("jal");

	//init label_2_sheet
	label_2_sheet.insert("beqz");
	label_2_sheet.insert("bnez");
	label_2_sheet.insert("blez");
	label_2_sheet.insert("bgez");
	label_2_sheet.insert("bgtz");
	label_2_sheet.insert("bltz");

	//init label_2_check_sheet
	label_2_check_sheet.insert("la");
	label_2_check_sheet.insert("lb");
	label_2_check_sheet.insert("lh");
	label_2_check_sheet.insert("lw");
	label_2_check_sheet.insert("sb");
	label_2_check_sheet.insert("sh");
	label_2_check_sheet.insert("sw");

	//init label_3_sheet
	label_3_sheet.insert("beq");
	label_3_sheet.insert("bne");
	label_3_sheet.insert("bge");
	label_3_sheet.insert("ble");
	label_3_sheet.insert("bgt");
	label_3_sheet.insert("blt");

	//init findType
	//.
	findType[".align"] = Line::Line_type::tData;
	findType[".ascii"] = Line::Line_type::tData;
	findType[".asciiz"] = Line::Line_type::tData;
	findType[".byte"] = Line::Line_type::tData;
	findType[".half"] = Line::Line_type::tData;
	findType[".word"] = Line::Line_type::tData;
	findType[".space"] = Line::Line_type::tData;

	findType[".data"] = Line::Line_type::tFrame;
	findType[".text"] = Line::Line_type::tFrame;

	//a,s,m,d,x,n,r
	findType["add"] = Line::Line_type::tInstruction;
	findType["addu"] = Line::Line_type::tInstruction;
	findType["addiu"] = Line::Line_type::tInstruction;
	findType["sub"] = Line::Line_type::tInstruction;
	findType["subu"] = Line::Line_type::tInstruction;
	findType["mul"] = Line::Line_type::tInstruction;
	findType["mulu"] = Line::Line_type::tInstruction;
	findType["div"] = Line::Line_type::tInstruction;
	findType["divu"] = Line::Line_type::tInstruction;
	findType["xor"] = Line::Line_type::tInstruction;
	findType["xoru"] = Line::Line_type::tInstruction;
	findType["neg"] = Line::Line_type::tInstruction;
	findType["negu"] = Line::Line_type::tInstruction;
	findType["rem"] = Line::Line_type::tInstruction;
	findType["remu"] = Line::Line_type::tInstruction;

	//l
	findType["li"] = Line::Line_type::tInstruction;

	//s (not special considering "sub")
	findType["seq"] = Line::Line_type::tInstruction;
	findType["sge"] = Line::Line_type::tInstruction;
	findType["sgt"] = Line::Line_type::tInstruction;
	findType["sle"] = Line::Line_type::tInstruction;
	findType["slt"] = Line::Line_type::tInstruction;
	findType["sne"] = Line::Line_type::tInstruction;

	//b,j
	findType["b"] = Line::Line_type::tInstruction;
	findType["beq"] = Line::Line_type::tInstruction;
	findType["bne"] = Line::Line_type::tInstruction;
	findType["bge"] = Line::Line_type::tInstruction;
	findType["ble"] = Line::Line_type::tInstruction;
	findType["bgt"] = Line::Line_type::tInstruction;
	findType["blt"] = Line::Line_type::tInstruction;
	findType["beqz"] = Line::Line_type::tInstruction;
	findType["bnez"] = Line::Line_type::tInstruction;
	findType["blez"] = Line::Line_type::tInstruction;
	findType["bgez"] = Line::Line_type::tInstruction;
	findType["bgtz"] = Line::Line_type::tInstruction;
	findType["bltz"] = Line::Line_type::tInstruction;
	findType["j"] = Line::Line_type::tInstruction;
	findType["jr"] = Line::Line_type::tInstruction;
	findType["jal"] = Line::Line_type::tInstruction;
	findType["jalr"] = Line::Line_type::tInstruction;

	//l (imm also)
	findType["la"] = Line::Line_type::tInstruction;
	findType["lb"] = Line::Line_type::tInstruction;
	findType["lh"] = Line::Line_type::tInstruction;
	findType["lw"] = Line::Line_type::tInstruction;

	//s
	findType["sb"] = Line::Line_type::tInstruction;
	findType["sh"] = Line::Line_type::tInstruction;
	findType["sw"] = Line::Line_type::tInstruction;
	
	//m
	findType["move"] = Line::Line_type::tInstruction;
	findType["mfhi"] = Line::Line_type::tInstruction;
	findType["mflo"] = Line::Line_type::tInstruction;

	//n,s
	findType["nop"] = Line::Line_type::tInstruction;
	findType["syscall"] = Line::Line_type::tInstruction;

	//init find_dType
	find_dType[".align"] = Data::Data_type::align;
	find_dType[".ascii"] = Data::Data_type::ascii;
	find_dType[".asciiz"] = Data::Data_type::asciiz;
	find_dType[".byte"] = Data::Data_type::byte;
	find_dType[".half"] = Data::Data_type::half;
	find_dType[".word"] = Data::Data_type::word;
	find_dType[".space"] = Data::Data_type::space;

}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
#ifdef MY_OUTSIDE
	string inMipsLocation, inDataLocation;
	if (argc == 1) {
		++argc;
		//cout << "Input the index of the mips file: ";
		//cin>>inMipsLocation;
	}
	else {
		inMipsLocation = argv[1];
	}
	if (argc == 2) {
		//cout << "Input the index of the in file: ";
		//cin >> inDataLocation;
	}
	else {
		inDataLocation = argv[2];
	}
	ifstream mipsIn(inMipsLocation);
#endif


#ifdef PYTHON_TEST
	ifstream mipsIn(argv[1]);
	istream& iData(cin);
#endif
#ifndef PYTHON_TEST
	string pgName = "array_test1-mahaojun";
	ifstream mipsIn(pgName + ".s");
	ifstream iData(pgName+".in");
#endif
	
	Program pg(mipsIn);
	CPU myCPU(iData, cout);
	int ret = myCPU.run(pg);
	return ret;
}