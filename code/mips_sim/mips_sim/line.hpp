#ifndef littleround_MIPS_line
#define littleround_MIPS_line
#include<string>

using namespace std;

class Line {
friend class Program;
protected:
	enum Line_type {
		tLabel, tInstruction, tData, tFrame
	} type;
	unsigned int id;
public:
	Line() {}
	Line(Line_type type) :type(type) {}
	Line(unsigned int id):id(id) {}
	Line(Line_type type, unsigned int id) :type(type), id(id) {}
};

class Label :public Line {
protected:
	string name;
public:
	Label() :Line(tLabel) {}
	Label(unsigned int id) :Line(tLabel, id) {}
};

class Instruction : public Line {
protected:
	string ins;
	char argc;
	string arg[3];
public:
	Instruction() :Line(tInstruction) {}
	Instruction(unsigned int id) :Line(tInstruction, id) {}
};

class Frame : public Line {
protected:
	bool isData;
public:
	Frame() :Line(tFrame) {}
	Frame(unsigned int id) :Line(tFrame, id) {}
};

class Data : public Line {
protected:
	enum Data_type {
		align, ascii, byte, half, word, space
	} dType;
	unsigned int location;
	unsigned int length;
public:
	Data() :Line(tData) {}
	Data(unsigned int id) :Line(tData, id) {}
};

#endif