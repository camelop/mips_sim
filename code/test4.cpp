#include<iostream>
using namespace std;
int main(){
	long long x=1111111111111111111111ll;
	int y=x;
	cout<<&x<<endl;
	x=(long long)&x;
	cout<<x<<endl;
	cout<<(long long*)x;
	cout<<y<<endl;
}