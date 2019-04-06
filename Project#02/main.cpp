/*
REQUISITOS DO JOGO

Os leds devem piscar 6 vezes, entre intervalos de 0.7 segundos
O jogador só pode apertar um botão uma vez a cada 0.3 segundos

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

// 7 segments display
BlackGPIO disp_uc(GPIO_4, output); // upper centenr
BlackGPIO disp_ur(GPIO_51, output); // upper right
BlackGPIO disp_ul(GPIO_49, output); // upper left
BlackGPIO disp_mi(GPIO_20, output); // mid
BlackGPIO disp_lr(GPIO_48, output); // lower right
BlackGPIO disp_ll(GPIO_14, output); // lower left
BlackGPIO disp_lc(GPIO_5, output); // lower center

void call_turn(BlackGPIO leds[], int output[]);
void press_inputs(BlackGPIO buttons[], int input[], BlackGPIO leds[]);
bool compare(int input[], int output[]);
int score(int score_counter, int input[], int output[]);
void reset_disp();
void mapping2disp(int digit);

int main(int argc, char *argv[]){
	// Digital outputs
	BlackGPIO led_0(GPIO_65, output);
	BlackGPIO led_1(GPIO_27, output);
	BlackGPIO led_2(GPIO_47, output);

	BlackGPIO led_state_ready(GPIO_45, output);

	// Digital inputs
	BlackGPIO button_0(GPIO_46, input);
	BlackGPIO button_1(GPIO_26, input);
	BlackGPIO button_2(GPIO_44, input);

	BlackGPIO leds[3] = {led_0, led_1, led_2};
	BlackGPIO buttons[3] = {button_0, button_1, button_2};

  	int output[NBLINKS];
  	int input[NRESPONSES];
  	
  	int score_counter = 5;

  	while(score_counter > 0 && score_counter < 10){
  		printf("%s\n", "This is a new turn, fasten your seatbelt!");
  		call_turn(leds, output);

  		mapping2disp(score_counter);
  		sleep(3); // time between leds blinks and player input

  		led_state_ready.setValue(high);
  		press_inputs(buttons, input, leds);
  		led_state_ready.setValue(low);

  		score_counter = score(score_counter, input, output);
  		printf("Your current score is: %d\n", score_counter);
  		sleep(3); // time between each turn
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
  	/*
		If the game is abruptly ended during call_turn() execution,
		the 7 segment display don't turn off, hence, I forced them to
		be off while in call_turn() and after call_turn() they turn on.
  	*/
  	reset_disp();

  	for(int i_rand = 0; i_rand<NBLINKS; i_rand++){

  		usleep(250000); // Time between each blink

  		printf("Blink number: %d\n", i_rand+1);
  		output[i_rand] = rand() % 3;

  		switch(output[i_rand]){
  			case 0:
  				leds[output[i_rand]].setValue(high);
  				printf("ANSWER -> LED NUMBER: %d\n", output[i_rand]);
  				usleep(700000);
  				break;
  			case 1:
  				leds[output[i_rand]].setValue(high);
  				printf("ANSWER -> LED NUMBER: %d\n", output[i_rand]);
  				usleep(700000);
  				break;
  			case 2:
  				leds[output[i_rand]].setValue(high);
  				printf("ANSWER -> LED NUMBER: %d\n", output[i_rand]);
  				usleep(700000);
  				break;
  			default:
  				printf("%s\n", "Wrong assignement for a digital output!");
  				exit(1);
  		}

  		for(int j_led = 0; j_led<NDIG_OUTPUT; j_led++)
  			leds[j_led].setValue(low); // Consider put this after each usleep
  	}
}

void press_inputs(BlackGPIO buttons[], int input[], BlackGPIO leds[]){
	int response_counter = 0;

	std::string str_b0;
	std::string str_b1;
	std::string str_b2;

	std::string strs_b[3] = {str_b0, str_b1, str_b2};

	int time_diff = 0, start_t, end_t;
	start_t = time(NULL);

	while(response_counter < NRESPONSES && time_diff < 10){

		for (int i = 0; i < NDIG_INPUT; i++){
			strs_b[i] = buttons[i].getValue();

			if(strs_b[i] == "1"){
				printf("A button was pressed, %d left.\n", NRESPONSES-response_counter-1);
				input[response_counter] = i;
				leds[i].setValue(high);
				response_counter++;
				usleep(350000); // time between pressed buttons 0.35 seconds
				leds[i].setValue(low);
				break;
			}
		}

		end_t = time(NULL);
		time_diff = end_t - start_t;
	}

	/*
		If the player delayed in pushing the buttons,
		this if-statement forces the input array to have -1 in all
		positions that weren't filled by the player
		with a valid number, thus, causing the 
		score_counter variable to decrease after the compare() 
		function is called inside main()
	*/
	if(time_diff >= 10){
		printf("%s\n", "TOO SLOW! the time for input was exceeded!");
		for (int feed_i = response_counter; feed_i<NDIG_INPUT; feed_i++){
			input[feed_i] = -1;
		}
	}
}

bool compare(int input[], int output[]){
	for (int i = 0; i < NRESPONSES; i++){
		if (input[i] != output[i]){
			return false;
		}
	}
	return true;
}

int score(int score_counter, int input[], int output[]){
	return compare(input, output) ? score_counter+1 : score_counter-1;
}

void reset_disp(){
	disp_uc.setValue(low); 
	disp_ur.setValue(low); 
	disp_ul.setValue(low); 
	disp_mi.setValue(low); 
	disp_lr.setValue(low); 
	disp_ll.setValue(low); 
	disp_lc.setValue(low);
}

void mapping2disp(int digit){

	reset_disp();

	switch(digit){
		case 0:
			disp_uc.setValue(high); 
			disp_ur.setValue(high); 
			disp_ul.setValue(high); 
			disp_lr.setValue(high); 
			disp_ll.setValue(high); 
			disp_lc.setValue(high);
			break;
		case 1:
			disp_lr.setValue(high);
			disp_ur.setValue(high);
			break;
		case 2:
			disp_uc.setValue(high); 
			disp_ur.setValue(high); 
			disp_mi.setValue(high);  
			disp_ll.setValue(high); 
			disp_lc.setValue(high);
			break;
		case 3:
			disp_uc.setValue(high); 
			disp_ur.setValue(high); 
			disp_mi.setValue(high); 
			disp_lr.setValue(high); 
			disp_lc.setValue(high);
			break;
		case 4:
			disp_ur.setValue(high); 
			disp_ul.setValue(high); 
			disp_mi.setValue(high); 
			disp_lr.setValue(high);
			break;
		case 5:
			disp_uc.setValue(high);  
			disp_ul.setValue(high); 
			disp_mi.setValue(high); 
			disp_lr.setValue(high);  
			disp_lc.setValue(high);
			break;
		case 6:
			disp_uc.setValue(high); 
			disp_ul.setValue(high); 
			disp_mi.setValue(high); 
			disp_lr.setValue(high); 
			disp_ll.setValue(high); 
			disp_lc.setValue(high);
			break;
		case 7:
			disp_uc.setValue(high); 
			disp_ur.setValue(high);  
			disp_lr.setValue(high); 
			break;
		case 8:
			disp_uc.setValue(high); 
			disp_ur.setValue(high); 
			disp_ul.setValue(high); 
			disp_mi.setValue(high); 
			disp_lr.setValue(high); 
			disp_ll.setValue(high); 
			disp_lc.setValue(high);
			break;
		case 9:
			disp_uc.setValue(high);
			disp_ur.setValue(high);
			disp_ul.setValue(high);
			disp_mi.setValue(high);
			disp_lr.setValue(high);
			disp_lc.setValue(high);
			break;
		case 10:
			break;
		default:
			printf("%s\n", "SCORE NUMBER INVALID!");
			exit(1);
	}
}