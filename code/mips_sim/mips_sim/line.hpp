#ifndef littleround_MIPS_line
#define littleround_MIPS_line
#include<string>
#include<vector>

using namespace std;

class Line {
	friend class Program; friend ostream& operator <<(ostream& fout, const Program& pg);
public:
	enum Line_type {
		tLabel, tInstruction, tData, tFrame
	};
protected:
	Line_type type;
	unsigned int id;
public:
	Line() {}
	Line(Line_type type) :type(type) {}
	Line(unsigned int id):id(id) {}
	Line(Line_type type, unsigned int id) :type(type), id(id) {}

	virtual ~Line() {};
};

class Label :public Line {
	friend class Program;
	friend ostream& operator <<(ostream& fout, const Program& pg);
protected:
	string name;
public:
	Label() :Line(tLabel) {}
	Label(unsigned int id) :Line(tLabel, id) {}
};

class Instruction : public Line {
	friend class Program; 
	friend ostream& operator <<(ostream& fout, const Program& pg);
protected:
	string ins;
	char argc;
	string argv[3];
public:
	Instruction() :Line(tInstruction) {}
	Instruction(unsigned int id) :Line(tInstruction, id) {}
};

class Frame : public Line {
	friend class Program;
	friend ostream& operator <<(ostream& fout, const Program& pg);
protected:
	bool isData;
public:
	Frame() :Line(tFrame) {}
	Frame(unsigned int id) :Line(tFrame, id) {}
};

class Data : public Line {
	friend unsigned long long 
		distribute(unsigned long long &mem, const Data& d);
	friend class Program;
	friend ostream& operator <<(ostream& fout, const Program& pg);
public:
	enum Data_type {
		align, ascii, asciiz, byte, half, word, space
	};
protected:
	Data_type dType;
	unsigned long long location;
	unsigned long long length;
	vector<string> arg;
public:
	Data() :Line(tData) {}
	Data(unsigned int id) :Line(tData, id) {}
};

#endif