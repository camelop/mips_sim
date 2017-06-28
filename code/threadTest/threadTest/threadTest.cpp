#include<iostream>
#include<thread>
#include<windows.h> 

using namespace std;

bool run = true;
bool two = true;

void p1() {
	while (run) cout << '1';
}
void p2() {
	while (run) if (two) cout << '2';
}
void p3() {
	while (run) if (two) cout << '3';
}

int main() {
	thread t1(&p1);
	thread t2(&p2);
	thread t3(&p3);
	t1.detach();
	t2.detach();
	t3.detach();

	system("pause");
	two = false;
	system("pause");

	run = false;
	return 0;
}
