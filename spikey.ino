// What I need to do to make it work on my old Gemma Board:
// Arduino 1.8.16
// Board: Adafruit Gemma ATTiny85 @ 8MHz
// Programmer: USBTinyISP
// Press reset before upload

#include <Adafruit_NeoPixel.h>

#define N_LEDS 40
#define PIN     0

//NEO_GRBW
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();
  for(int i=0; i<=N_LEDS; i++)
  {
    strip.setPixelColor(i, 0xFF0000);
    strip.show();
  }
    delay(500);
  for(int i=0; i<=N_LEDS; i++)
  {
    strip.setPixelColor(i, 0x00FF00);
    strip.show();
  }
    delay(500);
    for(int i=0; i<=N_LEDS; i++)
  {
    strip.setPixelColor(i, 0x0000FF);
    strip.show();
  }
  delay(500);
}


void loop() {
  brightnessfade(255,64);
  rainbow(10);
  
  brightnessfade(64,127);
  rainbow(10);

  brightnessfade(127,255);
  rainbow(10);
 }

void brightnessfade(int start, int stop){
  int i;
  if( start < stop)
  {
    for( i=start; i<stop; i+=1 )
    {
      strip.setBrightness(i);
      strip.show();
      delay(3);
    }
  }
  else
  {
    for( i=start; i>stop; i-=1 )
    {
      strip.setBrightness(i);
      strip.show();
      delay(3);
    }
  }
  
}


void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void knightrider(int sweeps)
{
  int j;
  int pos = 0, dir = 1; // Position, direction of "eye"

  // Draw 5 pixels centered on pos.  setPixelColor() will clip any
  // pixels off the ends of the strip, we don't need to watch for that.

  for(int loopcounter=(2*sweeps*strip.numPixels()); loopcounter>0; loopcounter--)
  {
    strip.setPixelColor(pos - 7, 0x080000); // Dark red
    strip.setPixelColor(pos - 6, 0x080000); // Dark red
    strip.setPixelColor(pos - 5, 0x100000); // Dark red
    strip.setPixelColor(pos - 4, 0x100000); // Dark red
    strip.setPixelColor(pos - 3, 0x880000); // Medium red
    strip.setPixelColor(pos - 2, 0xFF0000); // Medium red
    strip.setPixelColor(pos - 1, 0xFF4000); // Center pixel is brightest
    strip.setPixelColor(pos    , 0xFF4000); // Center pixel is brightest
    strip.setPixelColor(pos + 1, 0xFF4000); // Center pixel is brightest
    strip.setPixelColor(pos + 2, 0xFF0000); // Medium red
    strip.setPixelColor(pos + 3, 0x880000); // Medium red
    strip.setPixelColor(pos + 4, 0x100000); // Dark red
    strip.setPixelColor(pos + 5, 0x100000); // Dark red
    strip.setPixelColor(pos + 6, 0x080000); // Dark red
    strip.setPixelColor(pos + 7, 0x080000); // Dark red
  
    strip.show();
    delay(40);
  
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(j=-7; j<= 7; j++) strip.setPixelColor(pos+j, 0);
  
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } else if(pos >= strip.numPixels()) {
      pos = strip.numPixels() - 2;
      dir = -dir;
    }
  }
}
