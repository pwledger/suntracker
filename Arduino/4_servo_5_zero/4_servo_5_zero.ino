#include <Servo.h>
Servo servo_updown;

void setup() {
  Serial.begin(9600);
  servo_updown.attach(5);
  servo_updown.write(90);
  delay(2000);
}

void loop() {
}
