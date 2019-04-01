#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"


int main(int argc, char *argv[]){
	
	BlackGPIO displayLed_a(GPIO_73, output); // a
	BlackGPIO displayLed_b(GPIO_75, output); // b
	BlackGPIO displayLed_c(GPIO_77, output); // c
	BlackGPIO displayLed_d(GPIO_44, output); // d
	BlackGPIO displayLed_e(GPIO_68, output); // e
	BlackGPIO displayLed_f(GPIO_35, output); // f
	BlackGPIO displayLed_g(GPIO_67, output); // g
	BlackGPIO displayLed_dp(GPIO_87, output); // DP

	while(true){
		displayLed_a.setValue(high); // a
		displayLed_b.setValue(high); // b
		displayLed_c.setValue(high); // c
		displayLed_d.setValue(high); // d
		displayLed_e.setValue(high); // e
		displayLed_f.setValue(high); // f
		displayLed_g.setValue(high); // g
		displayLed_dp.setValue(high); // DP
	}
	

}