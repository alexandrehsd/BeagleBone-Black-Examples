/*
Este programa recebe o pid de um processo e para a instrução 
	0 - Resume o processo
	1 - Para a execução do processo
	2 - Mata o processo
	3 - Seta o processo para rodar apenas no core 0
*/

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

	switch (inst)
	{
		case 0:
			kill(pid, SIGCONT);
			break;
		case 1:
			kill(pid, SIGSTOP);
			break;
		case 2:
			kill(pid, SIGKILL);
			break;
		case 3:
			cpu_set_t set;
			CPU_ZERO(&set);        // clear cpu mask
			CPU_SET(0, &set);      // set cpu 0
			sched_setaffinity(pid, sizeof(cpu_set_t), &set);  // 0 is the calling process
			break;
		default:
			break;
	}

	
 	exit(0);
}