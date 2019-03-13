#include <iostream>
#include <time.h>   // para: time()
#include <unistd.h>
#include <stdlib.h>
#include "BlackGPIO/BlackGPIO.h"
#include "PWM/PWM.h"
#include "ADC/Adc.h"
#include <string.h>

using namespace std;
using namespace BlackLib;

int main(int argc, char * argv[]){
	// analog pin 5 for reading and writing (r & w)
	ADC adc(AINx::AIN5); 

	// instantiating pwm pin P9_22 for r & w
	PWM pwm(P9_22); 

	// Initializing pwm
	pwm.setState(statePwm::run); 
	
	// Digital input and output
	BlackGPIO pushbutton(GPIO_44, input);
	BlackGPIO led(GPIO_39, output);

	float dutyCycle;
	int period = 1000000;
	pwm.setPeriod(period);

	while(true){
		string val = pushbutton.getValue();

		if (val == "1"){
			led.setValue(high);

			cout << "val = " << val << " ";

			dutyCycle  = adc.getPercentValue();
			cout << "adc perc value = " << adc.getPercentValue() << " ";

			pwm.setDutyCycle(dutyCycle*period/100.0);
			cout << "pwm duty cycle = " << pwm.getDutyCycle() << " ";
			cout << "division = " << dutyCycle*period/100.0 << endl;
		}
		else {
			cout << "val = " << " ";
			cout << "pushbutton is off" << endl;
			pwm.setDutyCycle(0.0);
			led.setValue(low);
		}
	}
	return 0;
}
