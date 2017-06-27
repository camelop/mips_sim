#ifndef littleround_MIPS_CPU
#define littleround_MIPS_CPU

using namespace std;

class Reg {
	friend class CPU;
public:
	enum Reg_type {
		number,address
	};
private:
	char data[8];
	char* address;
};

class CPU {

};

#endif