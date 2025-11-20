#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(A4);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Hello,");
  display.setCursor(0,16);
  display.print("World!");
  display.display();
}
