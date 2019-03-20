
#include <iostream> // para: cout
#include <time.h>   // para: time()
#include <unistd.h>
#include <stdlib.h>



using std::cout;
using std::cin;


int main ( )
{

  time_t tempo1, tempo2;
  
  int numero;

  tempo1 = time( (time_t *) 0);  // apontando o ponteiro para null.

  cout << "Já se passaram  " << tempo1 << " segundos desde 0:00:00 de 01/01/1970 " << '\n';
  // printf(" Com printf: %ld \n", tempo_real);
    for(int i=0; i< 1000000; i++)for(int k=0; k<1000;k++);
      
  tempo2 = time( (time_t *) 0);  // apontando o ponteiro para null.
  cout << "Já se passaram  " << tempo2 << " segundos desde 0:00:00 de 01/01/1970 " << '\n';

  cout << "DeltaT = " << tempo2- tempo1 << '\n';
    

  exit(0);
}

