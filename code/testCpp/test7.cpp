#include<iostream>
using namespace std;
int main(){
	char x[8];
	unsigned char * pc = reinterpret_cast<unsigned char*>(x);
	short* ps = reinterpret_cast<short*>(x);
	int* pi = reinterpret_cast<int*>(x);
	long long* pll = reinterpret_cast<long long*>(x);
	(*pll) =0;
	(*ps)=-50;
	cout<<(int)(*pc)<<' '<<(*ps)<<' '<<(*pi)<<' '<<(*pll)<<endl;
	unsigned long long last = (*pll);
	cout<<(int)((unsigned char)last)<<' '
	<<(short)(last)<<' '
	<<(int)(last)<<' '
	<<last<<endl;
	cout<<(1==1);
	cout<<(1!=1);
}