//Servo motor library
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN);

Adafruit_SSD1306 display(A4);

int ldrtopl = 1;
int ldrtopr = 2;
int ldrbotl = 3;
int ldrbotr = 6;
int topl = 0;
int topr = 0;
int botl = 0;
int botr = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

//Declare two servos
Servo servo_updown;
Servo servo_rightleft;

int threshold_value = 30; //measurement sensitivity

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pixels.begin();

  servo_rightleft.attach(5);
  servo_updown.attach(6);

  servo_rightleft.write(90);
  servo_updown.write(120);
  delay(2000);
}

void loop()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    float read_val = analogRead(A0);
    display_func(read_val);
  }

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
    } else if (diffazi < 0) {
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
    } else if (diffelev < 0) {
      if (servo_updown.read() < 180) {
        servo_updown.write((servo_updown.read() + 1));
      }
    }
  }
  delay(10);
}

void display_func(float volt_sensor_val) {
  float temp = volt_sensor_val / 4.092;
  float volt = temp / 10;
  float power = volt * volt / 100; // milliWatt
  Serial.println(volt);
  if (volt > 6){
    volt = 6;
  }
  int gauge = map(volt,0,6,0,8);
  for(int i=0; i<NUMPIXELS; i++){
    if (i <= gauge) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    } 
    else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    } 
    delay(10);
  }
  pixels.setBrightness(20);
  pixels.show();
  
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 8);
  display.print(volt);
  display.print("V");
  display.display();
  display.clearDisplay();
}
