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

	// instantiating pwm pin P9_21 for r & w
	PWM pwm(P9_21); 
	
	// Digital input and output
	BlackGPIO pushbutton(GPIO_44, input);
	BlackGPIO led(GPIO_67, output);

	float dutyCycle;
	int period = 1000000;
	pwm.setPeriod(period);

	while(true){
		string val = pushbutton.getValue();

		if (val == "1"){
			pwm.setState(statePwm::run);
			led.setValue(high);

			cout << "Digital output = " << leg.getValue() << " ";
			cout << "val = " << val << " ";

			dutyCycle  = adc.getPercentValue();
			cout << "adc perc = " << adc.getPercentValue() << " ";

			pwm.setDutyCycle(dutyCycle*period/100.0);

			cout << "pwm duty cycle = " << pwm.getDutyCycle() << " ";
			cout << "division = " << dutyCycle*period/100.0 << endl;
		}
		else {
			pwm.setState(statePwm::stop);
			led.setValue(low);

			cout << "val = " << " ";
			cout << "pushbutton is off" << endl;
		}
	}
	return 0;
}
