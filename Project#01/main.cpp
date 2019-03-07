#include <iostream>
#include <time.h>   // para: time()
#include <unistd.h>
#include <stdlib.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"
#include <string.h>

using std::cout;

void PrintValues(){
	cout << "\n-------- STATES --------\n";
	cout << "adc value = " << adc.getIntValue() << endl;
	cout << "pwm duty cycle = " << getDutyCycle() << endl;
}

int main(int argc, char * argv[]){
	//time_t real_time;

	// analog pin 5 for reading and writing (r & w)
	ADC adc(AINx::AIN5); 

	// instantiating pwm pin P8_13 for r & w
	PWM pwm(P8_13); 

	// Initializing pwm
	pwm.setState(run); 
	
	// Digital input and output
	BlackGPIO pushbutton(GPIO_15, input);
	BlackGPIO led(GPIO_50, output);

	float dutyCycle;
	period = 1000000000;
	pwm.setPeriod(period);

	while(true){
		while(!strcmp(pushbutton.getValue(), "0")){
			pwm.setDutyCycle(0);
			led.setValue(low);
		}

		//real_time1 = time( (time_t *) 0);

		led.setValue(high);

		dutyCycle  = adc.getPercentValue();
		// cout << "adc value = " << adc.getIntValue() << endl;

		pwm.setDutyCycle(dutyCycle*period/100);
		// cout << "pwm duty cycle = " << getDutyCycle() << endl;

		//real_time2 = time( (time_t *) 0);
		//if ((real_time2-real_time1) >= 3)
		//	PrintValues();
	}
	return 0;
}
