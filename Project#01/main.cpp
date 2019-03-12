#include <iostream>
#include <time.h>   // para: time()
#include <unistd.h>
#include <stdlib.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"
#include <string.h>

using std::cout;
using namespace BlackLib;

int main(int argc, char * argv[]){
	// analog pin 3 for reading and writing (r & w)
	ADC adc(AINx::AIN3); 

	// instantiating pwm pin P9_22 for r & w
	PWM pwm(P9_21); 

	// Initializing pwm
	pwm.setState(statePwm::run); 
	
	// Digital input and output
	BlackGPIO pushbutton(GPIO_15, input);
	BlackGPIO led(GPIO_50, output);

	float dutyCycle;
	int period = 1000000;
	pwm.setPeriod(period);

	while(true){
		string val = pushbutton.getValue();

		if (val == "1"){
			led.setValue(high);

			dutyCycle  = adc.getPercentValue();
			cout << "adc value = " << adc.getIntValue() << " ";

			pwm.setDutyCycle(dutyCycle*period/100.0);
			cout << "pwm duty cycle = " << pwm.getDutyCycle() << " ";
			cout << "division = " << dutyCycle*period/100.0 << endl;
		}
		else {
			pwm.setDutyCycle(0);
			led.setValue(low);
		}
	}
	return 0;
}
