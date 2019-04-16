#include<sys/types.h>
#include<signal.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h> // system()
#include <math.h>

#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>

using std::cout;

int main(){
    cpu_set_t set;
    CPU_ZERO(&set); // clear cpu mask
    CPU_SET(0, &set); // set cpu 0
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);  // 0 is the calling process
    
    setpriority(PRIO_PROCESS, 0, 5);

    while(1);
}