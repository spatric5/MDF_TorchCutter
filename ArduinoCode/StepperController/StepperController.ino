#include <Stepper.h>

#define STEPS 250

Stepper stepper(STEPS, 10,11,12,13);

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Test");
  stepper.setSpeed(60);
}

void loop() {
  Serial.println("Forward");
  stepper.step(STEPS);
  Serial.println("Backward");
  stepper.step(-STEPS);

}
