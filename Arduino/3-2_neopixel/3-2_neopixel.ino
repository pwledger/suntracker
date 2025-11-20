#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS,13);

void setup() 
{
  pixels.begin();
  pixels.clear();
}

void loop() 
{
  for(int i=0; i <NUMPIXELS; i++)
  {
    if (i <= 2){
      pixels.setPixelColor(i,pixels.Color(255,0,0));
    }
    else if (i <= 5){
      pixels.setPixelColor(i, pixels.Color(0,255,0));
    }
    else{
      pixels.setPixelColor(i,pixels.Color(0,0,255));
    }
  }
  pixels.setBrightness(20);
  pixels.show();
  }
