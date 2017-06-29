#include<iostream>
using namespace std;
int main(){
	/*
	long long x=1111111111111111111111ll;
	int y=x;
	cout<<&x<<endl;
	x=(long long)&x;
	cout<<x<<endl;
	cout<<(long long*)x;
	cout<<y<<endl;
	*/
	unsigned long long x,yy,zz;
	int y=-5;
	yy=(unsigned long long)y;
	int z=-6;
	zz=(unsigned long long)z;
	x=yy+zz;
	int p = (int) x;
	cout<<p;
	
}