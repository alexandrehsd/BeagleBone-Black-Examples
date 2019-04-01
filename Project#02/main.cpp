/*
REQUISITOS DO JOGO

Os leds devem piscar 6 vezes, entre intervalos de 0.4 segundos

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"

#define NBLINKS 6
#define NRESPONSES 6
#define TIME2ANS 10 // seconds
#define NDIG_OUTPUT 3
#define NDIG_INPUT 3

using namespace BlackLib;

void call_turn(BlackGPIO leds[], int output[]);
void press_inputs(BlackGPIO buttons[], int input[]);
bool compare(int input[], int output[]);
int score(int score_counter, int input[], int output[]);

int main(int argc, char *argv[]){
	// Digital outputs
	BlackGPIO led_0(GPIO_35, output);
	BlackGPIO led_1(GPIO_39, output);
	BlackGPIO led_2(GPIO_38, output);

	BlackGPIO led_state_ready(GPIO_34, output);

	// Digital inputs
	BlackGPIO button_0(GPIO_33, input);
	BlackGPIO button_1(GPIO_37, input);
	BlackGPIO button_2(GPIO_63, input);


	BlackGPIO leds[3] = {led_0, led_1, led_2};
	BlackGPIO buttons[3] = {button_0, button_1, button_2};

  	int output[NBLINKS];
  	int input[NRESPONSES];
  	
  	int score_counter = 5;

  	while(score_counter > 0 && score_counter < 10){
  		call_turn(leds, output);

  		sleep(4);

  		led_state_ready.setValue(high);
  		press_inputs(buttons, input);
  		led_state_ready.setValue(low);

  		score_counter = score(score_counter, input, output);
  		printf("Your current score is: %d\n", score_counter);
  	}

  	if(score_counter == 10) 
  		printf("%s\n", "CONGRATULATIONS, YOU WON!");
  	else 
  		printf("%s\n", "YOU LOSE!");

	exit(0);
}

void call_turn(BlackGPIO leds[], int output[]){
	/* initialize random seed: */
  	srand (time(NULL));

	int i_rand;
  	int j_led;

  	for(i_rand = 0; i_rand<NBLINKS; i_rand++){
  		output[i_rand] = rand() % 3;

  		for(j_led = 0; j_led<NDIG_OUTPUT; j_led++)
  			leds[i_rand].setValue(low); // Consider put this after each usleep

  		switch(output[i_rand]){
  			case 0:
  				leds[i_rand].setValue(high);
  				usleep(400000);
  				break;
  			case 1:
  				leds[i_rand].setValue(high);
  				usleep(400000);
  				break;
  			case 2:
  				leds[i_rand].setValue(high);
  				usleep(400000);
  				break;
  			default:
  				printf("%s\n", "Wrong assignement for a digital output!");
  				exit(1);
  		}
  	}
}

void press_inputs(BlackGPIO buttons[], int input[]){
	int response_counter = 0;
	int i;

	std::string str_b0;
	std::string str_b1;
	std::string str_b2;

	std::string strs_b[3] = {str_b0, str_b1, str_b2};

	while(response_counter < NRESPONSES){

		for (i = 0; i < NDIG_INPUT; i++)	{
			strs_b[i] = buttons[i].getValue();

			if(strs_b[i] == "1"){
				input[response_counter] = i;
				continue;
			}
		}

		/* Do I need to set the input values to low?

		for (int i = 0; i < 3; ++i)
			buttons[i].setValue(low);
		*/

		response_counter++;
	}
}

bool compare(int input[], int output[]){
	int i;
	for (i = 0; i < NRESPONSES; i++){
		if (input[i] != output[i]){
			return false;
		}
	}
	return true;
}

int score(int score_counter, int input[], int output[]){
	return compare(input, output) ? score_counter+1 : score_counter-1;
}