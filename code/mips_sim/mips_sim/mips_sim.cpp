#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "line.hpp"
#include "program.hpp"

#define MIPS_TEST1

using namespace std;

map<string, Line::Line_type> findType;
map<string, Data::Data_type> find_dType;
set<string> label_1_sheet;
set<string> label_2_sheet;
set<string> label_2_check_sheet;
set<string> label_3_sheet;

const int Memory = 4 * 1024 * 1024;

void init() {
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
	init();

#ifdef MIPS_TEST1
	ifstream mipsIn1("array_test1-mahaojun.s");
	Program pg1(mipsIn1);
	cout << pg1;
	return 0;
#endif

	string inMipsLocation, inDataLocation;
	if (argc == 1) {
		++argc;
		cout << "Input the index of the mips file: ";
		cin>>inMipsLocation;
	}
	else {
		inMipsLocation = argv[1];
	}
	if (argc == 2) {
		cout << "Input the index of the in file: ";
		cin >> inDataLocation;
	}
	else {
		inDataLocation = argv[2];
	}
	ifstream mipsIn(inMipsLocation);
	ifstream dataIn(inDataLocation);
	ofstream dataOut("output.txt");
	
	Program pg(mipsIn);

	
}