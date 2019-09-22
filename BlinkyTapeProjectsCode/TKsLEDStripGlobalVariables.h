/*
  TKsLEDStripGlobalVariables.h  - Globally defined variables to be used throughout the sketches
                                  Defining things like led control output pins, MIDI channel, dip switch pins
                                  and brightness settings to manage power draw of circuit

  Created by Turner E. Kirk, January 20, 2019.
  Released into the public domain.
*/

#ifndef TKsLEDStripGlobalVariables_h
#define TKsLEDStripGlobalVariables_h



// ******************************************************************
//            Includes and GLOBAL define
// ******************************************************************



#define __LIGHT_STICKS__
#define __BLINKY_TAPE__

//#define __TWO_SEGMENTS_ONE_STRIP__
//#define __BLINKY_TAPE__


/*
#define __TWO_SEGMENTS_ONE_STRIP__
#define __TRINKET_PRO__
*/

enum {SHOW_PATTERN, TO_CHANGE_BRIGHTNESS, CHANGE_BRIGHTNESS, TO_CHANGE_PALETTE, CHANGE_PALETTE, TO_SHOW_PATTERN};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// ************************************************************************************************************
//            Strip settings -- Change these to fit your application
// ************************************************************************************************************

#ifdef __LIGHT_STICKS__
  #define NUM_LEDS_BIKE_CENTER_STRIP  34
  #define NUM_LEDS_BIKE_TOTAL NUM_LEDS_BIKE_CENTER_STRIP
  #define REVERSE_STRIP_FOR_FIRE_ANIMATION true

#elif defined __TWO_SEGMENTS_ONE_STRIP__

  #define NUM_LEDS_BIKE_CENTER_STRIP  60
  #define NUM_LEDS_BIKE_SIDE_STRIP    20
  #define NUM_LEDS_BIKE_TOTAL (NUM_LEDS_BIKE_CENTER_STRIP + NUM_LEDS_BIKE_SIDE_STRIP)

#elif defined __TWO_STRIPS__
  // do something here

#endif



// ************************************************************************************************************
//            Hardware settings -- Change these to fit the board you're using
// ************************************************************************************************************

// ******* Blinky Tape Pins *******
#ifdef __BLINKY_TAPE__
  // use these global variables
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




// ******* Trinket Pro Pins *******
#elif defined __TRINKET_PRO__
  #define DATA_PIN_BIKE_CENTER_STRIP    11
//  #define DATA_PIN_BIKE_SIDE_STRIP   11

  #define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  6
  #define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  5

  #define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE_backup  3

  #define PULLUP              true // these should be true for kevin's button setup
  #define INVERT              true // these should be true for kevin's button setup



// ******* Teensy Pins *******
#elif defined __TEENSY__
  #define LED_ENABLE_PIN 7
  #define DATA_PIN_BIKE_CENTER_STRIP    11
  #define DATA_PIN_BIKE_SIDE_STRIP   13
  #define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  22
  #define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  21

  #define PULLUP              true // these should be true for kevin's button setup
  #define INVERT              true // these should be true for kevin's button setup


#endif






// ***************************************************************************************************************
//            FastLED GLOBAL VARIABLES -- Change these to fit your processor speed and power consumption needs
// ***************************************************************************************************************

#define LED_TYPE NEOPIXEL
#define FRAMES_PER_SECOND  120

#define INITIAL_BRIGHTNESS     60 
#define BRIGHTNESS_INCREMENT   20 
#define BRIGHTNESS_MAX_MODULO 180


// ***************************************************************************************************************
//            BUTTON GLOBAL VARIABLES -- Change these to fit your processor speed and power consumption needs
// ***************************************************************************************************************
#define DEBOUNCE_MS         20
#define LONG_PRESS          1000


// ***************************************************************************************************************
//           FIRE ANIMATION GLOBAL VARIABLES
// ***************************************************************************************************************
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









// ***************************************************************************************************************
//            GLOBAL ANIMATION AND COLOR PALLETTE DECLARATIONS
// ***************************************************************************************************************

/*
//add more animations here

//this should always equal the number of options in AnimationType - 1 because "NONE" is not an animation
#define TOTAL_NUM_TRIGGERABLE_ANIMATIONS 9

enum AnimationType {
  DEVIN_ANIMATION,
  DEVIN_ANIMATION_WITH_CC_CONTROL,
  DS_CUPCAKEPARTY,
  FL_CONFETTI,
  DS_FLASHBULB_WHOLE_STRIP,
  DS_FLASHBULB_WHOLE_STRIP_WITH_CC_CONTROL,
  RAINBOW,
  //RAINBOW_REVERSE,
  COLOR_PALETTE,
  COLOR_WIPE_MIDDLE_OUT,
  NONE
};

#define INITIAL_UPDATE_INTERVAL 2

#define NORMAL_UPDATE_INTERVAL 5
#define DEVIN_ANIMATION_UPDATE_INTERVAL 40 // can't be much less than this due to processor intensive behavior
#define DEVIN_ANIMATION_WITH_CC_CONTROL_UPDATE_INTERVAL 40 // can't be much less than this due to processor intensive behavior
#define DS_CUPCAKEPARTY_ANIMATION_UPDATE_INTERVAL 100
#define FL_CONFETTI_ANIMATION_UPDATE_INTERVAL 10
#define DS_FLASHBULB_WHOLE_STRIP_ANIMATION_UPDATE_INTERVAL 10
#define DS_FLASHBULB_WHOLE_STRIP_WITH_CC_CONTROL_ANIMATION_UPDATE_INTERVAL 10 // THIS ONE IS NOT USED
#define RAINBOW_ANIMATION_UPDATE_INTERVAL 15
#define COLOR_PALETTE_ANIMATION_UPDATE_INTERVAL 15
#define COLOR_WIPE_MIDDLE_OUT_ANIMATION_UPDATE_INTERVAL 2
*/

/*
DEFINE_GRADIENT_PALETTE( MyRainbow_gp_2 ) {
      0,  255,  0,  0, // Red
     32,  171, 85,  0, // Orange
     64,  171,171,  0, // Yellow
     96,    0,255,  0, // Green
    128,    0,171, 85, // Aqua
    160,    0,  0,255, // Blue
    192,   85,  0,171, // Purple
    224,  171,  0, 85, // Pink
    253,  255,  0,  0,// and back to Red
    254,  255,  255,  255,// and white at the top
    255,  255,  255,  255};// and white at the top

//CRGBPalette16 myPalette(MyRainbow_gp);
CRGBPalette16 myPalette = RainbowColors_p;
*/

#endif
