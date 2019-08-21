/*
  TKsLEDStripController.cpp   - Class that provides specific controlls of a defined LED Strip using the FastLED Library
                                Originally intended to play nice with MIDI controllers
  Created by Turner E. Kirk, January 20, 2019.
  Released into the public domain.
*/


// ******************************************************************
//            Includes
// ******************************************************************

#include "TKsBlinkyTapeLEDController.h"

// *****************************************************************************************************
//
//      CONSTRUCTOR
//
// *****************************************************************************************************


//TKsBlinkyTapeLEDController::TKsBlinkyTapeLEDController(CRGB *leds, CRGBPalette16 pPalettes, uint16_t pLedStripStartIndex, uint16_t pLedStripEndIndex, bool reverseTheLEDConfiguration = false)
TKsBlinkyTapeLEDController::TKsBlinkyTapeLEDController(CRGB *leds, CRGBPalette16 pPalettes, uint16_t pLedStripEndIndex, bool reverseTheLEDConfiguration = false)
{

//  LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, 0, NUM_LEDS_BIKE_CENTER_STRIP-1);

  ledStrip = leds;

  STATE = 0;

  gPalettes = pPalettes;

  numPixelsInStrip = pLedStripEndIndex;

  ledStripStartIndex = 0;

//***** IMPORTANT *****
  // This code will tell the strip to reverse or not for FIRE animation
  gReverseDirection = reverseTheLEDConfiguration;


// GEAR DOTS

#ifdef __LIGHT_STICKS__
  r1 = new Ring(ledStrip + ledStripStartIndex, numPixelsInStrip/2);
  r2 = new Ring(ledStrip + ledStripStartIndex + numPixelsInStrip/2, numPixelsInStrip/2);

#elif defined __TWO_SEGMENTS_ONE_STRIP__
  r1 = new Ring(ledStrip + ledStripStartIndex + 1, numPixelsInStrip/2 - 1);
  r2 = new Ring(ledStrip + ledStripStartIndex + numPixelsInStrip/2 - 1, numPixelsInStrip/2);  
#endif


  d1 = new Dot(r1, CRGB::Magenta, 0, 4, 0);
  d2 = new Dot(r1, CRGB::Orange, 6*16, 4, 0);
  d3 = new Dot(r1, CRGB::Green, 12*16, 4, 0);
  d4 = new Dot(r1, CRGB::Blue, 18*16, 4, 0);
  d5 = new Dot(r2, CRGB::Magenta, 0, -4, 0);
  d6 = new Dot(r2, CRGB::Orange, 6*16, -4, 0);
  d7 = new Dot(r2, CRGB::Green, 12*16, -4, 0);
  d8 = new Dot(r2, CRGB::Blue, 18*16, -4, 0);

  dots = new Dot[8]{*d1, *d2, *d3, *d4, *d5, *d6, *d7, *d8};
// GEAR DOTS

//START **** FIRE ANIMATION CLASS VARIABLE INITIALIZER
  // Array of temperature readings at each simulation cell
  // Since this is in a class now, the heat array has been declared as a class member
  heat = new byte[numPixelsInStrip];
  
//END **** FIRE ANIMATION CLASS VARIABLE INITIALIZER
  
}


// *****************************************************************************************************
//
//      MAIN UPDATE FUNCTION
//      Chooses the animation method to run based on the activeAnimationType, as selected by button press
//      It updates based on a timer, the interval for the timer is held in the updateInterval variable
//
// *****************************************************************************************************
void TKsBlinkyTapeLEDController::Update() {

  switch (STATE) {

    case SHOW_PATTERN:
      //(this->*(gPatterns[gCurrentPatternNumber]))();
      
        if( (millis() - lastPatternUpdateTime) > patternUpdateInterval ){
          (this->*(gPatterns[gCurrentPatternNumber]))();
          lastPatternUpdateTime = millis();
        }
      
      break;

    //This is a transition state where we run the fast blink function as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS or SHOW_PATTERN state.
    case TO_CHANGE_BRIGHTNESS:
    case TO_CHANGE_PALETTE:
    case TO_SHOW_PATTERN:      
      fastBlink();
      break;

    case CHANGE_BRIGHTNESS:
      showCurrentBrightness();
      break;   

    case CHANGE_PALETTE:
      showCurrentPalette();
      break; 


  }

  // slowly cycle the "base color" through the rainbow
  if( (millis() - lastHueUpdateTime) > hueUpdateInterval){
    gHue++;
    lastHueUpdateTime = millis();
  }
  
  // DON'T USE THE "EVERY_N_MILLISECONDS" BUILT-IN FAST LED TIMER HERE. IT WILL BREAK THINGS FOR SOME REASON.
  //EVERY_N_MILLISECONDS( hueUpdateInterval ) { gHue++; }
  
}

// *****************************************************************************************************
// ******************************* PUBLIC HELPER METHODS ***********************************************
// ******************************* PUBLIC HELPER METHODS ***********************************************
// ******************************* PUBLIC HELPER METHODS ***********************************************
// ******************************* PUBLIC HELPER METHODS ***********************************************
// *****************************************************************************************************

void TKsBlinkyTapeLEDController::nextPattern() {
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % (ARRAY_SIZE( gPatterns ));

  //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
  if( gCurrentPatternNumber == (ARRAY_SIZE( gPatterns ) - 3) ){
    patternUpdateInterval = 15;
    //patternUpdateInterval = fireUpdateInterval;
    
    for( uint16_t i = 0; i < numPixelsInStrip; i++) {
      heat[i] = 0;
    }
    
  }
  else{
    patternUpdateInterval = 0;
  }
  
}




void TKsBlinkyTapeLEDController::nextPalette() {

  // add one to the current palette number, and wrap around at the end
  //gCurrentPaletteNumber = (gCurrentPaletteNumber + 1) % ARRAY_SIZE( gPalettes );
  if( gCurrentPaletteNumber ==  0)  { gPalettes = RainbowColors_p;         }
  //else if( secondHand ==  5)  { SetupPurpleAndGreenPalette();      }
  //else if( secondHand == 10)  { SetupBlackAndWhiteStripedPalette();}
  else if( gCurrentPaletteNumber == 1)  { gPalettes = ForestColors_p;          }
  else if( gCurrentPaletteNumber == 2)  { gPalettes = CloudColors_p;           }
  else if( gCurrentPaletteNumber == 3)  { gPalettes = LavaColors_p;            }
  else if( gCurrentPaletteNumber == 4)  { gPalettes = OceanColors_p;           }
  else if( gCurrentPaletteNumber == 5)  { gPalettes = PartyColors_p;           }
  //else if( secondHand == 40)  { SetupRandomPalette();              }
  //else if( secondHand == 45)  { SetupRandomPalette();              }
  //else if( secondHand == 50)  { SetupRandomPalette();              }
  else if( gCurrentPaletteNumber == 6)  { gPalettes = RainbowStripeColors_p;   }
  else if( gCurrentPaletteNumber == 7)  { gPalettes = HeatColors_p;   }

  
  
  if(gCurrentPaletteNumber == 7){ gCurrentPaletteNumber = 0; }
  else { gCurrentPaletteNumber++; }
  
} 

//Used for button long press feedback
void TKsBlinkyTapeLEDController::fastBlink() {
  uint8_t bpm = 45;  
  uint8_t on = beatsin8(bpm);
  if (on > 127) {
    fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, CRGB::White);
  } else {
    fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, CRGB::Black);    
  }
}

void TKsBlinkyTapeLEDController::showCurrentBrightness() {
    fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, brightnessDemoColor);  
}


void TKsBlinkyTapeLEDController::showCurrentPalette(){
    fill_palette( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 0, 8 /* higher = narrower stripes */,  gPalettes, 255, LINEARBLEND);
/*
    uint8_t colorIndex = 0;
    
    for( int i = 0; i < numPixelsInStrip; i++) {
      ledStrip[ledStripStartIndex + i] = ColorFromPalette(gPalettes, colorIndex, 255, LINEARBLEND);
      colorIndex += 3;
    }
*/      
}

void TKsBlinkyTapeLEDController::setStripState(uint8_t NEW_STATE){
  STATE = NEW_STATE;
}

uint8_t TKsBlinkyTapeLEDController::getStripState(){
  return STATE;
}



// *********************************************************************************************************
// ******************************* JAKES ANIMATION METHODS ***********************************************
// ******************************* JAKES ANIMATION METHODS ***********************************************
// ******************************* JAKES ANIMATION METHODS ***********************************************
// ******************************* JAKES ANIMATION METHODS ***********************************************
// *********************************************************************************************************
void TKsBlinkyTapeLEDController::nextPaletteSpeed() {

  patternUpdateInterval--;

  if(patternUpdateInterval == 0){
    patternUpdateInterval = 15;
  }
  
}


// *********************************************************************************************************
// ******************************* PRIVATE ANIMATION METHODS ***********************************************
// ******************************* PRIVATE ANIMATION METHODS ***********************************************
// ******************************* PRIVATE ANIMATION METHODS ***********************************************
// ******************************* PRIVATE ANIMATION METHODS ***********************************************
// *********************************************************************************************************


void TKsBlinkyTapeLEDController::rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, gHue, 7);
  
}

void TKsBlinkyTapeLEDController::rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void TKsBlinkyTapeLEDController::addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    ledStrip[ ledStripStartIndex + random16(numPixelsInStrip) ] += CRGB::White;
  }
}

void TKsBlinkyTapeLEDController::confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
  
  uint16_t pos = random16(numPixelsInStrip);
  
  ledStrip[ledStripStartIndex + pos] += CHSV( gHue + random8(64), 200, 255);
}


void TKsBlinkyTapeLEDController::patrioticConfetti() 
{
  // red, white, and blue colored speckles that blink in and fade smoothly
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
  
  uint16_t pos = random16(numPixelsInStrip);
  
  CRGB nextColor;
  
  switch (random(3)) {
    case 0:
      nextColor = CRGB::Red;
      break;
    case 1:
      nextColor = CRGB::White;
      break;
    case 2:
      nextColor = CRGB::Blue;
      break;
    default:
      nextColor = CRGB::Blue;
      break;
  }
  ledStrip[ledStripStartIndex + pos] = nextColor;
}

void TKsBlinkyTapeLEDController::paletteConfetti() 
{
  // red, white, and blue colored speckles that blink in and fade smoothly
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
  
  uint16_t pos = random16(numPixelsInStrip);
  
  ledStrip[ledStripStartIndex + pos] = ColorFromPalette( gPalettes, random8() );
}


void TKsBlinkyTapeLEDController::sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
  
  uint16_t pos = beatsin16( 13, 0, numPixelsInStrip-1 );
  
  ledStrip[ledStripStartIndex + pos] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos]] += CHSV( gHue, 255, 192);
}

//same as above but has two sinelones
void TKsBlinkyTapeLEDController::sinelon2()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
  
  uint16_t pos = beatsin16(13,0,numPixelsInStrip/2-1);
  ledStrip[ledStripStartIndex + pos] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos]] += CHSV( gHue, 255, 192);
  
  uint16_t pos1 = beatsin16(13,0,numPixelsInStrip/2-1);
  ledStrip[ledStripStartIndex + pos1 + numPixelsInStrip/2] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos1 + numPixelsInStrip/2]] += CHSV( gHue, 255, 192);
}

void TKsBlinkyTapeLEDController::juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
  
  byte dothue = 0;
  
  for( uint16_t i = 0; i < 8; i++) {
    ledStrip[ledStripStartIndex + beatsin16( i+7, 0, numPixelsInStrip-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void TKsBlinkyTapeLEDController::bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  
  //CRGBPalette16 palette = PartyColors_p;
  
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  
  for( uint16_t i = 0; i < numPixelsInStrip; i++) { //9948
    //ledStrip[ledStripStartIndex + i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    ledStrip[ledStripStartIndex + i] = ColorFromPalette(gPalettes, gHue+(i*2), beat-gHue+(i*10));
  }
}

// GEAR DOTS
void TKsBlinkyTapeLEDController::gearDots() {
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
  
  for (uint16_t i=0; i< 8; i++) {
    dots[i].draw();
    dots[i].updatePos();
  }
}
// GEAR DOTS

// change patterns periodically
void TKsBlinkyTapeLEDController::cycle() {
  (this->*(gPatterns[cycleFunctionPatternIndex]))();
  //EVERY_N_SECONDS( 10 ) { 
  if((millis() - lastCycleUpdateTime) > cycleUpdateInterval){
    cycleFunctionPatternIndex = (cycleFunctionPatternIndex + 1) % ARRAY_SIZE( gPatterns );

    //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
    if( cycleFunctionPatternIndex == (ARRAY_SIZE( gPatterns ) -2) ){
      cycleFunctionPatternIndex = 0;
    }
    //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
    else if( gCurrentPatternNumber == (ARRAY_SIZE( gPatterns ) - 3) ){
      patternUpdateInterval = 15;
      //patternUpdateInterval = fireUpdateInterval;
      
      for( uint16_t i = 0; i < numPixelsInStrip; i++) {
        heat[i] = 0;
      }
      
    }
    else{
      patternUpdateInterval = 0;
    }


    
    lastCycleUpdateTime = millis();
    //somewhat fancier but also more wordy way of doing the same thing in the if statement above
    //cycleFunctionPatternIndex = (cycleFunctionPatternIndex == (ARRAY_SIZE( gPatterns ) -2) ) ? cycleFunctionPatternIndex++ : cycleFunctionPatternIndex; 
    
  } 

}

void TKsBlinkyTapeLEDController::fire2012WithPalette() {
// Fourth, the most sophisticated: this one sets up a new palette every
// time through the loop, based on a hue that changes every time.
// The palette is a gradient from black, to a dark color based on the hue,
// to a light color based on the hue, to white.
//
//   static uint8_t hue = 0;
//   hue++;
//   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
//   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
//   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
  
// Array of temperature readings at each simulation cell
// Since this is in a class now, the heat array has been declared as a class member
//  static byte heat[numPixelsInStrip];

  // Step 1.  Cool down every cell a little
    for( uint16_t i = 0; i < numPixelsInStrip; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / numPixelsInStrip) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( uint16_t k= numPixelsInStrip - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      uint16_t y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( uint16_t j = 0; j < numPixelsInStrip; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPalettes, colorindex);
      uint16_t pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (numPixelsInStrip-1) - j;
      } else {
        pixelnumber = j;
      }
      ledStrip[pixelnumber] = color;
//        ledStrip[ledOrder[j]] = color;
      
      //ledStrip[ledStripStartIndex + j] = color;
      //ledStrip[numPixelsInStrip -1- j] = color;


      
    }
}

void TKsBlinkyTapeLEDController::FillLEDsFromPaletteColors()
{
    uint8_t colorIndex = gHue;
    
    for( int i = 0; i < numPixelsInStrip; i++) {
        ledStrip[i] = ColorFromPalette( gPalettes, colorIndex);
//          ledStrip[ledOrder[i]] = ColorFromPalette( gPalettes, colorIndex);
        colorIndex += paletteSpeed;
    }
}  

void TKsBlinkyTapeLEDController::FillLEDsFromPaletteOneColorAtAtime()
{
    //uint8_t brightness = 255;
    
    for( int i = 0; i < numPixelsInStrip; i++) {
        ledStrip[i] = ColorFromPalette( gPalettes, gHue);
//          ledStrip[ledOrder[i]] = ColorFromPalette( gPalettes, gHue);
        //colorIndex += 3;
    }
}  

void TKsBlinkyTapeLEDController::fadeToBlack() {
  // turn off the strip in a "mysterious" way
  fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
}
