#ifndef ACS780_h
#define ACS780_h

#include <Arduino.h>

#define ADC_SCALE 1023.0
#define VREF 5.0
#define DEFAULT_FREQUENCY 50

enum ACS780_type {ACS780LLRTR_050B,ACS780LLRTR_050U,ACS780LLRTR_100B,ACS780LLRTR_100U,ACS780KLRTR_150B,ACS780KLRTR_150U};

class ACS780 {
public:
	ACS780(ACS780_type type, uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	float getCurrentDC();
	float getCurrentAC();
	float getCurrentAC(uint16_t frequency);

private:
	float zero = 512.0;
	float sensitivity;
	uint8_t pin;
};

#endif