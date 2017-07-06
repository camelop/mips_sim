#ifndef littleround_MIPS_pack
#define littleround_MIPS_pack
class Pack {
	friend class CPU;
private:
	int code;
	int reg[3];
	int label;
	int arg[2];
	int stage;
	char* location;
	int lock;
	bool isImm;
	bool isLabel;
	bool judge;
public:
	Pack() {
		stage = 1;
	}
};
#endif