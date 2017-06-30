#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
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
set<string> type_o_i_i_sheet;
set<string> type_o_i_sheet;
set<string> type_ls_sheet;
set<string> wb_sheet;

map<string, int> idReg;

extern const int Memory;

void init() {
	//init wb_sheet;
	wb_sheet.insert("la");
	wb_sheet.insert("lb");
	wb_sheet.insert("lh");
	wb_sheet.insert("lw");
	wb_sheet.insert("add");
	wb_sheet.insert("addu");
	wb_sheet.insert("addiu");
	wb_sheet.insert("sub");
	wb_sheet.insert("subu");
	wb_sheet.insert("mul");
	wb_sheet.insert("mulu");
	wb_sheet.insert("div");
	wb_sheet.insert("divu");
	wb_sheet.insert("xor");
	wb_sheet.insert("xoru");
	wb_sheet.insert("neg");
	wb_sheet.insert("negu");
	wb_sheet.insert("rem");
	wb_sheet.insert("remu");
	wb_sheet.insert("li");
	wb_sheet.insert("seq");
	wb_sheet.insert("sge");
	wb_sheet.insert("sgt");
	wb_sheet.insert("sle");
	wb_sheet.insert("slt");
	wb_sheet.insert("sne");

	//init type_ls_sheet
	type_ls_sheet.insert("la");
	type_ls_sheet.insert("lb");
	type_ls_sheet.insert("lh");
	type_ls_sheet.insert("lw");
	type_ls_sheet.insert("sb");
	type_ls_sheet.insert("sh");
	type_ls_sheet.insert("sw");

	//init type_o_i_i_sheet
	type_o_i_i_sheet.insert("add");
	type_o_i_i_sheet.insert("addu");
	type_o_i_i_sheet.insert("addiu");
	type_o_i_i_sheet.insert("sub");
	type_o_i_i_sheet.insert("subu");
	type_o_i_i_sheet.insert("div");
	type_o_i_i_sheet.insert("xor");
	type_o_i_i_sheet.insert("xoru");
	type_o_i_i_sheet.insert("rem");
	type_o_i_i_sheet.insert("remu");
	type_o_i_i_sheet.insert("seq");
	type_o_i_i_sheet.insert("sge");
	type_o_i_i_sheet.insert("sgt");
	type_o_i_i_sheet.insert("sle");
	type_o_i_i_sheet.insert("slt");
	type_o_i_i_sheet.insert("sne");
	
	type_o_i_i_sheet.insert("mul");
	type_o_i_i_sheet.insert("mulu");
	type_o_i_i_sheet.insert("div");
	type_o_i_i_sheet.insert("divu");


	//init type_o_i_sheet;
	type_o_i_sheet.insert("neg");
	type_o_i_sheet.insert("negu");
	type_o_i_sheet.insert("li");
	type_o_i_sheet.insert("move");
	type_o_i_sheet.insert("mfhi");
	type_o_i_sheet.insert("mflo");

	type_o_i_sheet.insert("mul");
	type_o_i_sheet.insert("mulu");
	type_o_i_sheet.insert("div");
	type_o_i_sheet.insert("divu");

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

//int main(int argc, char* argv[]) {
int main(){
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

	ifstream mipsIn("array_test1-mahaojun.s");
	ifstream iData("array_test1-mahaojun.in");
	//ifstream dataIn(inDataLocation);
	//ofstream dataOut("output.txt");
	
	Program pg(mipsIn);
	CPU myCPU(iData, cout);
	int ret = myCPU.run(pg);
	return ret;
}