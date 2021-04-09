#include <ACS780.h>
ACS780 sensor(ACS780LLRTR_100U, A1);
void setup() {
  Serial.begin(9600);
  sensor.calibrate();
}
void loop() {
  float I = sensor.getCurrentDC();
  Serial.println(String("I = ") + I + " A");
  delay(1000);
}
