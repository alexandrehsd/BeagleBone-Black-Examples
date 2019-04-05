#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"

using namespace BlackLib;

void mapping2disp(int digit);

int main(int argc, char *argv[]){

	int digit;
	while(true){
		printf("%s", "Entre com um dígito: ");
		scanf("%d", &digit);
		mapping2disp(digit);
		printf("\n");
	}

}

void mapping2disp(int digit){

	BlackGPIO disp_uc(GPIO_4, output); // upper centenr
	BlackGPIO disp_ur(GPIO_51, output); // upper right
	BlackGPIO disp_ul(GPIO_49, output); // upper left
	BlackGPIO disp_mi(GPIO_20, output); // mid
	BlackGPIO disp_lr(GPIO_48, output); // lower right
	BlackGPIO disp_ll(GPIO_14, output); // lower left
	BlackGPIO disp_lc(GPIO_5, output); // lower center

	disp_uc.setValue(low); 
	disp_ur.setValue(low); 
	disp_ul.setValue(low); 
	disp_mi.setValue(low); 
	disp_lr.setValue(low); 
	disp_ll.setValue(low); 
	disp_lc.setValue(low);

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
			break;
		case 10:
			break;
		default:
			printf("%s\n", "SCORE NUMBER INVALID!");
			exit(1);
	}
}