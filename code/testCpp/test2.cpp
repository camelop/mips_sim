#include<iostream>
#include<windows.h>

using namespace std;

bool lock=false;
bool out=false;
void T1(){
	int s=1;
	while (s<100000){
		if (out) return;
	//	if (lock) continue;
		lock=true;
		if (s==99999) {
			s=1;
			cout<<"T1"<<endl;
		}
		++s;
		lock=false;
	}
}
void T2(){
	int s=1;
	while (s<100000){
		if (out) return;
	//	if (lock) continue;
		lock=true;
		if (s==99999) {
			s=1;
			cout<<"T2"<<endl;
		}
		++s;
		lock=false;
	}
}

int main(){
	HANDLE t1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T1,NULL,true,0);
	HANDLE t2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T2,NULL,true,0);
	system("pause"); 
	ResumeThread(t1);
	ResumeThread(t2);
	system("pause"); 
	SuspendThread(t1);
	system("pause");
	SuspendThread(t2);
	system("pause");
	out=true;
	Sleep(1000);
	CloseHandle(t1);
	CloseHandle(t2);
	//dont know how to stop... 
	system("pause");
	return 0;
	
}
