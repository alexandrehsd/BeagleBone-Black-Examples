#include <signal.h> // definição dos sinais de interrupções
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h> // system()

using namespace std;

int  main()
{
  	// o processo que vai matar
	int pid;
	cout << "Entre com o número do pid do processo: ";
	cin >> pid;

	cout << "\n";

	int inst;
	cout << "Entre com o número da instrução: ";
	cin >> inst;

	if(inst == 0)
		kill(pid, SIGCONT);
	else if(inst == 1)
		kill(pid, SIGSTOP);
	else
		kill(pid, SIGKILL);
	
 	exit(0);
}