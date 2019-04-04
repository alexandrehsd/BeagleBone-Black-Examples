#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"

using namespace BlackLib;

int main(int argc, char *argv[]){
	
	BlackGPIO disp_uc(GPIO_4, output); // upper centenr
	BlackGPIO disp_ur(GPIO_31, output); // upper right
	BlackGPIO disp_ul(GPIO_117, output); // upper left
	BlackGPIO disp_mi(GPIO_20, output); // mid
	BlackGPIO disp_lr(GPIO_48, output); // lower right
	BlackGPIO disp_ll(GPIO_14, output); // lower left
	BlackGPIO disp_lc(GPIO_5, output); // lower center

	while(true){
		disp_uc.setValue(high); 
		disp_ur.setValue(high); 
		disp_ul.setValue(high); 
		disp_mi.setValue(high); 
		disp_lr.setValue(high); 
		disp_ll.setValue(high); 
		disp_lc.setValue(high); 
	}
	

}