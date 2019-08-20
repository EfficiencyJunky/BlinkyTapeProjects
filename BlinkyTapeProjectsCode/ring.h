#ifndef Ring_h
#define Ring_h

#include <FastLED.h>

class Ring {
    CRGB *leds;
    int num_leds;
    
  public:
    int len;
    Ring(CRGB *l, int n);

    // Ring(CRGB *l, int n) {
    //   leds = l;
    //   num_leds = n;
    //   len = num_leds * 16;
    // }    
    void draw(int pos, CRGB color);

};


#endif // Ring_h
