#include "ring.h"


Ring::Ring(CRGB *l, int n) {
  leds = l;
  num_leds = n;
  len = num_leds * 16;
}  


void Ring::draw(int pos, CRGB color) {
  int posOnStrip = pos / 16;
  uint8_t r = (pos % 16);
  if (r == 0 ){
    leds[posOnStrip] = color;
  } else {
    fract8 scaleBefore = 255 - r * 16;
    fract8 scaleAfter = r * 16;
    leds[posOnStrip] |= color;
    leds[(posOnStrip+1)%num_leds] |= color;
    leds[posOnStrip].nscale8(scaleBefore);
    leds[(posOnStrip+1)%num_leds].nscale8(scaleAfter);
  }
}
