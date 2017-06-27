#ifndef littleround_MIPS_RAM
#define littleround_MIPS_RAM

#include "line.hpp"
using namespace std;

class RAM {
public:
	long long fromStringToNumber(const string& s) {
		long long ten = 1;
		long long f = 1;
		long long ret = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == '-') {
				f = -1;
				continue;
			}
			ret += ten*(s[i] - '0');
			ten *= 10;
		}
		return ret*f;
	}

	unsigned long long distribute(unsigned long long &mem, const Data& d) {
		unsigned long long ret = 0;
		switch (d.dType) {
		case Data::Data_type::align : {
			unsigned long long two = (1 << fromStringToNumber(d.arg[0]));
			unsigned long long res = mem%two;
			if (res == 0) return 0;
			ret = two - res;
			mem += ret;
			return ret;
		}
		case Data::Data_type::ascii: {
			ret = d.arg[0].length();
			mem += ret;
			return ret;
		}
		case Data::Data_type::asciiz: {
			ret = d.arg[0].length() + 1;
			mem += ret;
			return ret;
		}
		case Data::Data_type::byte: {
			//recognize as digits
			mem += 1;
			return 1;
		}
		case Data::Data_type::half: {
			mem += 2;
			return 2;
		}
		case Data::Data_type::word: {
			mem += 4;
			return 4;
		}
		case Data::Data_type::space: {
			ret = fromStringToNumber(d.arg[0]);
			mem += ret;
			return ret;
		}
		default: {
			throw(-1); //undefined
		}
		}
	}
};
#endif