#include "ACS780.h"
int zero; 
ACS780::ACS780(ACS780_type type, uint8_t _pin) {
	switch (type) {
		case ACS780LLRTR_050B:
		 sensitivity = 0.04 ;
		 break;
		case ACS780LLRTR_050U:
		 sensitivity = 0.06 ;
		 break;
		case ACS780LLRTR_100B:
		 sensitivity = 0.02 ;
		 break;
		case ACS780LLRTR_100U:
		 sensitivity = 0.04 ;
		 break;   
		case ACS780KLRTR_150B:
		 sensitivity = 0.01333 ;
		 break;	
		case ACS780KLRTR_150U:
		  sensitivity = 0.02666 ;
		  break;
		default:
			sensitivity = 0.01333 ;
			break;
	}
	pin = _pin;
}

int ACS780::calibrate() {
	int _zero = 0;
	for (int i = 0; i < 10; i++) {
		_zero += analogRead(pin);
		delay(10);
	}
	_zero /= 10;
	zero = _zero;
	return _zero;
}

void ACS780::setZeroPoint(int _zero) {
	zero = _zero;
}

void ACS780::setSensitivity(float sens) {
	sensitivity = sens;
}

float ACS780::getCurrentDC() {
	float I = (zero - analogRead(pin)) / ADC_SCALE * VREF / sensitivity;
	return I;
}

float ACS780::getCurrentAC() {
	return getCurrentAC(DEFAULT_FREQUENCY);
}

float ACS780::getCurrentAC(uint16_t frequency) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Isum = 0, measurements_count = 0;
	int32_t Inow;

	while (micros() - t_start < period) {
		Inow = zero - analogRead(pin);
		Isum += Inow*Inow;
		measurements_count++;
	}

	float Irms = sqrt(Isum / measurements_count) / ADC_SCALE * VREF / sensitivity;
	return Irms;
}
