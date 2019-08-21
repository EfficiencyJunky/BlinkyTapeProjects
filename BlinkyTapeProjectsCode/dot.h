#ifndef Dot_h
#define Dot_h

#include <FastLED.h>
#include "ring.h"

class Dot {
  Ring *r;
  int pos;
  float vel;
  float acc;
  CRGB color;

  public:
    Dot(Ring *rr, CRGB c, int p, float v, float a);  
    void draw();
    // Dot(Ring *rr, CRGB c, int p, float v, float a) {
    //   color = c;
    //   pos = p;
    //   vel = v;
    //   acc = a;
    //   r = rr;
    // }
    void updatePos();
};



#endif // Dot_h
