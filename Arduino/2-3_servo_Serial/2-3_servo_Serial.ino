#include <Servo.h>
int servoPin = 7;
int angle = 0;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(angle);
}

void loop() {
  int value = 0;
  if(Serial.available()){
    value = Serial.parseInt();
  }
  if(value > 0 && value <= 180){
    angle = value;
    Serial.print("현재각도 : ");
    Serial.println(angle);
    servo.write(angle);
  }
}
