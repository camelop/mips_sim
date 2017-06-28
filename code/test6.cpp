#include<iostream>
#include<thread>
#include<windows.h> 

using namespace std;

bool run=true;

void p1(){
	while (run) cout<<'1';
}
void p2(){
	while (run) cout<<'2';
}

int main(){
	thread t1(&p1,this);
	thread t2(&p2,this);
	t1.detach();
	t2.detach();
	
	system("pause");
	
	run=false; 
	return 0;
} 
