#include<iostream>
using namespace std;
char x[10];
int main(){
	cout<<sizeof(int*)<<endl;
	for (int i=0;i<10;i++) x[i]='\1';
	unsigned long long p = (unsigned long long)(&(x[1]));
	(*(reinterpret_cast<int*>(p))) = 255;
	for (int i=0;i<10;i++) cout<<(int)x[i]<<' ';
//	cout<<(*(reinterpret_cast<int*>(p)));
}