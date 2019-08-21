// August 27th, 2018
// One strip with two buttons. Strip can be reversed with a "true" in the final member of the constructor
// Button one controlls current animation and brightness
// Button two controlls palette choice
// added some new animations that work with palettes
//
#include "FastLED.h"
#include "ring.h"
#include "dot.h"
#include <Button.h>

FASTLED_USING_NAMESPACE


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif


// ****************** CONSTANT DEFINED VARIABLES ********************
//
// ******************************************************************

//trinket pro pins
/*
#define DATA_PIN_BIKE_CENTER_STRIP    10
#define DATA_PIN_BIKE_SIDE_STRIP   11
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  A1
#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  A2

#define PULLUP              false // these should be true for kevin's button setup
#define INVERT              false // these should be true for kevin's button setup

*/

//Blinky Tape Pins

#define DATA_PIN_BIKE_CENTER_STRIP    13
//#define DATA_PIN_BIKE_SIDE_STRIP   11

// Use these for strip with 2 buttons
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  11
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE_backup  10

#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  7

// Use these for strip with 1 button
//#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  10
//#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  11

#define PULLUP              true // these should be true for kevin's button setup
#define INVERT              true // these should be true for kevin's button setup



//Teensy pins
/*
#define LED_ENABLE_PIN 7
#define DATA_PIN_BIKE_CENTER_STRIP    11
#define DATA_PIN_BIKE_SIDE_STRIP   13
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  22
#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  21

#define PULLUP              true // these should be true for kevin's button setup
#define INVERT              true // these should be true for kevin's button setup

*/

#define LED_TYPE NEOPIXEL

#define NUM_LEDS_BIKE_CENTER_STRIP  34 // 92 for Kevin's Purposes and the staff
//#define NUM_LEDS_BIKE_SIDE_STRIP  0   // 92 for Kevin's Purposes and the staff

//#define NUM_LEDS_BIKE_TOTAL (NUM_LEDS_BIKE_CENTER_STRIP + NUM_LEDS_BIKE_SIDE_STRIP)
#define NUM_LEDS_BIKE_TOTAL NUM_LEDS_BIKE_CENTER_STRIP

//#define INITIAL_BRIGHTNESS          40 //start with low brightness for Kevin's wack wiring sake (kidding kevin)
#define INITIAL_BRIGHTNESS          60
#define BRIGHTNESS_INCREMENT          20
#define BRIGHTNESS_MAX_MODULO          180 //


#define DEBOUNCE_MS         20
#define LONG_PRESS          1000

#define FRAMES_PER_SECOND  120

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//BEGIN ******* FIRE ANIMATION GLOBAL VARIABLES ********
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120



//PartyColors is the Instagram palette
//CRGBPalette16 gPal(LavaColors_p);
CRGBPalette16 gPal(HeatColors_p);
//CRGBPalette16 gPal(CloudColors_p);
//CRGBPalette16 gPal(PartyColors_p);

//END ******* FIRE ANIMATION GLOBAL VARIABLES ********

Button button_BikeCenterStrip_and_BrightnessChange(BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE, PULLUP, INVERT, DEBOUNCE_MS);
Button button_BikeCenterStrip_and_BrightnessChange_backup(BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE_backup, PULLUP, INVERT, DEBOUNCE_MS);

Button button_BikeSideStrip_and_PaletteChange(BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE, PULLUP, INVERT, DEBOUNCE_MS);



// *********** STRIP SETUP VARIABLES FOR MULTIPLE INDIVIDUAL STRIPS **********************
//
// ***************************************************************************************
/*
CRGB leds_bike_center[NUM_LEDS_BIKE_CENTER_STRIP];
CRGB leds_bike_side[NUM_LEDS_BIKE_SIDE_STRIP];

TKsBlinkyTapeLEDController ledStrip_bike_center(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP);
TKsBlinkyTapeLEDController ledStrip_bike_side(&(leds_bike_side[0]), gPal, NUM_LEDS_BIKE_SIDE_STRIP);
*/

// *********** STRIP SETUP VARIABLES FOR ONE STRIP WITH MULTIPLE SEGMENTS ****************
//
// ***************************************************************************************

CRGB leds_bike_center[NUM_LEDS_BIKE_TOTAL];
//CRGB leds_bike_side[NUM_LEDS_BIKE_SIDE_STRIP];

#ifdef __LIGHT_STICKS__
  TKsBlinkyTapeLEDController ledStrip_bike_center(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP, true);


#elif defined __TWO_SEGMENTS_ONE_STRIP__
  TKsBlinkyTapeLEDController ledStrip_bike_center(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP);
//  TKsBlinkyTapeLEDController ledStrip_bike_side(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP, NUM_LEDS_BIKE_TOTAL);

  TKsBlinkyTapeLEDController ledStrip_bike_side(&(leds_bike_center[0]) + NUM_LEDS_BIKE_CENTER_STRIP, gPal, NUM_LEDS_BIKE_SIDE_STRIP);


#elif defined __TWO_STRIPS__
  // do something here

#endif


//USE THIS IF YOU WANT THE STRIP FLIPPED FOR FIRE ANIMATION
//TKsBlinkyTapeLEDController ledStrip_bike_center(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP, true);



// ****************** SETUP FUNCTION ********************************
// ****************** SETUP FUNCTION ********************************
// ****************** SETUP FUNCTION ********************************
void setup() {
  delay(3000); // 3 second delay for recovery ??? who knows why

//START ***** GLOBAL VARIABLE INITIALIZATION FOR FIRE ANIMATION ******
  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  //gPal = HeatColors_p;

  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
//END ***** GLOBAL VARIABLE INITIALIZATION FOR FIRE ANIMATION ******



  // tell FastLED about the LED strip configuration
  //***** VERSION WHERE THERE ARE MULTIPLE SEGMENTS IN A SINGLE STRIP *****
        //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds, NUM_LEDS_TOTAL).setCorrection(TypicalLEDStrip);
  //***** VERSION WHERE THERE ARE MULTIPLE SEGMENTS IN A SINGLE STRIP *****

  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds_bike_center, NUM_LEDS_BIKE_CENTER_STRIP).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_SIDE_STRIP>(leds_bike_side, NUM_LEDS_BIKE_SIDE_STRIP).setCorrection(TypicalLEDStrip);

  FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds_bike_center, NUM_LEDS_BIKE_TOTAL).setCorrection(TypicalLEDStrip);

  // Use this for the Staff
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_SIDE_STRIP>(leds_bike_center, NUM_LEDS_BIKE_TOTAL).setCorrection(TypicalLEDStrip);

  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP,COLOR_ORDER>(leds_segment_1, NUM_LEDS_BIKE_CENTER_STRIP).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);


  //pinMode(LED_ENABLE_PIN, OUTPUT);
  //digitalWrite(LED_ENABLE_PIN, HIGH);  // enable access to LEDs

  // set master brightness control
  FastLED.setBrightness(INITIAL_BRIGHTNESS);

}

// ****************** MAIN LOOP *************************************
// ****************** MAIN LOOP *************************************
// ****************** MAIN LOOP *************************************
void loop() {

  // Add entropy to random number generator; we use a lot of it for the FIRE ANIMATION
  random16_add_entropy( random());

  readButtons();

  ledStrip_bike_center.Update();

#ifdef __TWO_SEGMENTS_ONE_STRIP__
  ledStrip_bike_side.Update();
#endif

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);

}


// ****************** HELPER FUNCTIONS *************************************
// ****************** HELPER FUNCTIONS *************************************
// ****************** HELPER FUNCTIONS *************************************
void readButtons(){

  //Read the button associated with bike center strip and brightness change (with long press)
  button_BikeCenterStrip_and_BrightnessChange.read();

  switch (ledStrip_bike_center.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){

        ledStrip_bike_center.nextPattern();

#ifdef __TWO_SEGMENTS_ONE_STRIP__
        ledStrip_bike_side.nextPattern();
#endif


      }
      else if (button_BikeCenterStrip_and_BrightnessChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_CHANGE_BRIGHTNESS);
      }
      break;

    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.
    case TO_CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        ledStrip_bike_center.setStripState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        nextBrightness();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        ledStrip_bike_center.setStripState(SHOW_PATTERN);
      }
      break;
  }



  button_BikeCenterStrip_and_BrightnessChange_backup.read();

  switch (ledStrip_bike_center.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.nextPattern();

#ifdef __TWO_SEGMENTS_ONE_STRIP__
        ledStrip_bike_side.nextPattern();
#endif

      }
      else if (button_BikeCenterStrip_and_BrightnessChange_backup.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_CHANGE_BRIGHTNESS);
      }
      break;

    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.
    case TO_CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.setStripState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        nextBrightness();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.setStripState(SHOW_PATTERN);
      }
      break;
  }




  //Read the button associated with bike side strip and palette change (with long press)
  button_BikeSideStrip_and_PaletteChange.read();

  if (button_BikeSideStrip_and_PaletteChange.wasReleased()){
    ledStrip_bike_center.nextPalette();

#ifdef __TWO_SEGMENTS_ONE_STRIP__
        ledStrip_bike_side.nextPalette();
#endif
  }


/*
  switch (ledStrip_bike_side.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.nextPattern();
      else if (button_BikeSideStrip_and_PaletteChange.pressedFor(LONG_PRESS))
        ledStrip_bike_side.setStripState(TO_CHANGE_PALETTE);
      break;

    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.
    case TO_CHANGE_PALETTE:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.setStripState(CHANGE_PALETTE);
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_PALETTE:
      if (button_BikeSideStrip_and_PaletteChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_side.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeSideStrip_and_PaletteChange.wasReleased()){
        ledStrip_bike_side.nextPalette();
        ledStrip_bike_center.nextPalette();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.setStripState(SHOW_PATTERN);
      break;
  }

 */
}

void nextBrightness() {
  uint8_t currentBrightness = FastLED.getBrightness();
  currentBrightness += BRIGHTNESS_INCREMENT;

  if(currentBrightness < BRIGHTNESS_MAX_MODULO){
    currentBrightness = currentBrightness % BRIGHTNESS_MAX_MODULO;
  }
  else if(currentBrightness >= BRIGHTNESS_MAX_MODULO){
    currentBrightness = BRIGHTNESS_INCREMENT;
  }

  FastLED.setBrightness(currentBrightness);
}

void nextBrightness_old() {
  uint8_t currentBrightness = FastLED.getBrightness();
  currentBrightness += 16;
  currentBrightness = currentBrightness % 132;
  FastLED.setBrightness(currentBrightness);
}
