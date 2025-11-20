#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN);

Adafruit_SSD1306 display(A4);

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pixels.begin();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    float read_val = analogRead(A0);
    display_func(read_val);
  }
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
  for(int i=0; i<NUMPIXELS; i++) {
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
