#include <Servo.h>

int ldrtopl = 1;
int ldrtopr = 2;
int ldrbotl = 3;
int ldrbotr = 6;
int topl = 0;
int topr = 0;
int botl = 0;
int botr = 0;

Servo servo_updown;
Servo servo_rightleft;

int threshold_value = 30;                                                                

void setup() {
  servo_rightleft.attach(5);
  servo_updown.attach(6);
  servo_rightleft.write(90);
  servo_updown.write(120);
  delay(2000);
}

void loop() {
  topl = analogRead(ldrtopl);
  topr = analogRead(ldrtopr);
  botl = analogRead(ldrbotl);
  botr = analogRead(ldrbotr);

  int avgtop = (topl + topr) / 2;
  int avgbot = (botl + botr) / 2;
  int avgleft = (topl + botl) / 2;
  int avgright = (topr + botr) / 2;

  int diffelev = avgtop - avgbot;
  int diffazi = avgright - avgleft;

  if (abs(diffazi) >= threshold_value) {
    if (diffazi > 0) {
      if (servo_rightleft.read() > 0) {
        servo_rightleft.write((servo_rightleft.read() - 1));
      }
    } 
    else if (diffazi < 0) {
      if (servo_rightleft.read() < 180) {
        servo_rightleft.write((servo_rightleft.read() + 1));
      }
    }
  }

  if (abs(diffelev) >= threshold_value) {
    if (diffelev > 0) {
      if (servo_updown.read() > 120) {
        servo_updown.write((servo_updown.read() - 1));
      }
    } 
    else if (diffelev < 0) {
      if (servo_updown.read() < 180) {
        servo_updown.write((servo_updown.read() + 1));
      }
    }
  }
  delay(10);
}
