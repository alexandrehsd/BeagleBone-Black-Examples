#include <stdio.h>
#include <time.h> /* time_t, struct tm, difftime, time, mktime */

int main(int argc, char const *argv[])
{
	time_t instant_time;

  	struct tm input_time; /* Structure containing a calendar date and time broken down into its components.*/
  	double seconds;

  	input_time.tm_year = 100; // years since 1900
  	input_time.tm_mon = 0; // range (0,11)
  	input_time.tm_mday = 1; // range (1,31)
  	input_time.tm_hour = 0; // range (0,23)
  	input_time.tm_min = 0; // range (0,59)
  	input_time.tm_sec = 0; // range (0,60)

  	time(&instant_time);  /* get current time; same as: timer = time(NULL)  */

  	/* 
  	mktime:
  		receives as a parameter a pointer to a tm structure 
  		that contains a calendar time broken down into its components

  		returns a time_t value corresponding to the calendar time passed as argument.

  	difftime:
  		returns the result of end-beginning (time_t types) 
  		in seconds as a floating-point value of type double.
  	*/

  	seconds = difftime(instant_time,mktime(&input_time)); 
  	printf ("%.f seconds passed since January 1, 2000 in the current timezone\n", seconds);

  	return 0;
}