#include<iostream>
#include<map>
#include<string>
using namespace std;

map<string, void (*)()> m;

void hello1(){
	cout<<"Good morning\n";
}

void hello2(){
	cout<<"Good Night\n";
}

int main(){
	m["i1"]=&hello1;
	m["i2"]=&hello2;
	string x;
	cin>>x;
	m[x]();
	return 0;
}
