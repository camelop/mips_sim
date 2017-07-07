#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h> 

using namespace std;

shared_mutex x;

void P() {
	while (1) {
		x.lock();
		cout << endl;
	}
}

int main() {
	thread t1(P);
	while (true) {
		system("pause");
		x.unlock();
	}
	return 0;
}
