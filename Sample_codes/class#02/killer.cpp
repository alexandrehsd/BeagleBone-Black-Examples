#include <iostream>
#include <stdlib.h>
//#include <sys/types.h>
//#include <unistd.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

	string victim;
	string action = "kill ";
	
	cout << "\nplease, enter the pid of the process you wish to kill: ";
	getline(cin, victim);
	
	string command = action + victim;

	system(command.c_str());
	cout << "\nKILLED!\n";
	return 0;
}