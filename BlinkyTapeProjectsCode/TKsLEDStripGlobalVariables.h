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
//#include <FastLED.h>

// __MOLDOVER__, __GGFO_BODY_DIAMOND__, or __GGFO_SUIT__

#define __MOLDOVER__


// ************************************************************************************************************
//            Strip settings -- Change these to fit your application
// ************************************************************************************************************

// how many individually addressable strips are you using total?
// needs to match the number of initialized strips you will actually be using

#ifdef __GGFO_BODY_DIAMOND__
    #define TOTAL_NUM_STRIPS 2

    // DATA PIN FOR EACH STRIP WE ARE USING
    #define DATA_PIN_STRIP_01 3    //right section
    #define DATA_PIN_STRIP_02 5    //left section

    // NUMBER OF LED'S IN EACH STRIP WE ARE USING
    #define NUM_PIXELS_IN_STRIP_01 95    //right section
    #define NUM_PIXELS_IN_STRIP_02 95    //left section

    // DATA PIN AND NUMBER OF LED'S IN EACH STRIP WE ARE NOT USING
    #define DATA_PIN_STRIP_03 11
    #define DATA_PIN_STRIP_04 12
    #define DATA_PIN_STRIP_05 13
    #define DATA_PIN_STRIP_06 14
    #define DATA_PIN_STRIP_07 15
    #define DATA_PIN_STRIP_08 16
    #define NUM_PIXELS_IN_STRIP_03 30
    #define NUM_PIXELS_IN_STRIP_04 30
    #define NUM_PIXELS_IN_STRIP_05 30
    #define NUM_PIXELS_IN_STRIP_06 30
    #define NUM_PIXELS_IN_STRIP_07 30
    #define NUM_PIXELS_IN_STRIP_08 30


#elif defined __GGFO_SUIT__
    #define TOTAL_NUM_STRIPS 5

    // DATA PIN FOR EACH STRIP
    #define DATA_PIN_STRIP_01 3     //left jacket
    #define DATA_PIN_STRIP_02 5     //right jacket
    #define DATA_PIN_STRIP_03 6     //back jacket
    #define DATA_PIN_STRIP_04 14    //left leg
    #define DATA_PIN_STRIP_05 11    //right leg

    // NUMBER OF LED'S IN EACH STRIP
    #define NUM_PIXELS_IN_STRIP_01 127     //left jacket   -- 132 LEDs
    #define NUM_PIXELS_IN_STRIP_02 127     //right jacket  -- 132 LEDs
    #define NUM_PIXELS_IN_STRIP_03 112     //back jacket   -- 112 LEDs
    #define NUM_PIXELS_IN_STRIP_04 50     //left leg
    #define NUM_PIXELS_IN_STRIP_05 50     //right leg

    // WHERE TO REVERSE PIXEL ORIENTATION DUE TO IMPROPER WIRING
    #define LEFT_REVERSE_PIXEL_ORDER_AT_PIXEL_NUMBER 46        // left jacket (strip 01) reverse the pixel order here (because of incorrect wiring)
    #define BACK_REVERSE_PIXEL_ORDER_AT_PIXEL_NUMBER 100        // back jacket (strip 03) reverse the pixel order here (because of incorrect wiring)

    // DATA PIN AND NUMBER OF LED'S IN EACH STRIP WE ARE NOT USING
    #define DATA_PIN_STRIP_06 13
    #define DATA_PIN_STRIP_07 15
    #define DATA_PIN_STRIP_08 16
    #define NUM_PIXELS_IN_STRIP_06 30
    #define NUM_PIXELS_IN_STRIP_07 30
    #define NUM_PIXELS_IN_STRIP_08 30


#elif defined __MOLDOVER__
    #define TOTAL_NUM_STRIPS 8

    // DATA PIN FOR EACH STRIP
    #define DATA_PIN_STRIP_01 9      // pin 9
    #define DATA_PIN_STRIP_02 10     // pin 10
    #define DATA_PIN_STRIP_03 11     // pin 11
    #define DATA_PIN_STRIP_04 12     // pin 12
    #define DATA_PIN_STRIP_05 13     // pin 13
    #define DATA_PIN_STRIP_06 14     // pin 14
    #define DATA_PIN_STRIP_07 15     // pin 15
    #define DATA_PIN_STRIP_08 16     // pin 16

    // NUMBER OF LED'S IN EACH STRIP
    #define NUM_PIXELS_IN_STRIP_01 30     // pin 9
    #define NUM_PIXELS_IN_STRIP_02 30     // pin 10
    #define NUM_PIXELS_IN_STRIP_03 30     // pin 11
    #define NUM_PIXELS_IN_STRIP_04 30     // pin 12
    #define NUM_PIXELS_IN_STRIP_05 30     // pin 13
    #define NUM_PIXELS_IN_STRIP_06 30     // pin 14
    #define NUM_PIXELS_IN_STRIP_07 30     // pin 15
    #define NUM_PIXELS_IN_STRIP_08 30     // pin 16

#endif


// ***************************************************************************************************************
//            OTHER HARDWARE OPTIONS (Default Midi channel, dipswitch pins, MIDI Note Value Mappings etc.)
// ***************************************************************************************************************
#ifndef DEFAULT_MIDI_CHANNEL
  #define DEFAULT_MIDI_CHANNEL 1                // Sets default MIDI Channel if dip switches are set to 0000
#endif

// order of dipswitch pins where pin 1 is LSB and pin 4 is MSB

#if defined(__GGFO_BODY_DIAMOND__) || defined(__GGFO_SUIT__)
  #define DIP_SWITCH_PIN_1    19 // this sets pin 1 (LSB) of the DIP switch to connect to input 8
  #define DIP_SWITCH_PIN_2    20 // this sets pin 2 of the DIP switch to connect to input 7
  #define DIP_SWITCH_PIN_3    21 // this sets pin 3 of the DIP switch to connect to input 6
  #define DIP_SWITCH_PIN_4    22 // this sets pin 4 (MSB) of the DIP switch to connect to input 5

#elif defined __MOLDOVER__
  #define DIP_SWITCH_PIN_1    8 // this sets pin 1 (LSB) of the DIP switch to connect to input 8
  #define DIP_SWITCH_PIN_2    7 // this sets pin 2 of the DIP switch to connect to input 7
  #define DIP_SWITCH_PIN_3    6 // this sets pin 3 of the DIP switch to connect to input 6
  #define DIP_SWITCH_PIN_4    5 // this sets pin 4 (MSB) of the DIP switch to connect to input 5
#endif

//Maps the human readable name of the note to the MIDI pitch value
#define NOTE_A0   33
#define NOTE_Bb0  34
#define NOTE_B0   35
#define NOTE_C1   36
#define NOTE_Db1  37
#define NOTE_D1   38
#define NOTE_Eb1  39
#define NOTE_E1   40
#define NOTE_F1   41
#define NOTE_Gb1  42
#define NOTE_G1   43
#define NOTE_Ab1  44


// ***************************************************************************************************************
//            FastLED.Show() settings -- Change these to fit your processor speed and power consumption needs
// ***************************************************************************************************************

#ifndef FRAMES_PER_SECOND
  #define FRAMES_PER_SECOND  60
#endif

//#ifndef
//  #define BRIGHTNESS  96
//#endif

#ifndef WHITE_BRIGHTNESS_ATTENUATOR
  #define WHITE_BRIGHTNESS_ATTENUATOR 0.72 //used to lower the output brightness of white color only (recommended between 0.6 and 0.84)
#endif


// ***************************************************************************************************************
//            VARIOUS OTHER GLOBAL DECLARATIONS. DON'T NEED TO CHANGE THESE
// ***************************************************************************************************************

#ifndef FULL_SATURATION
  #define FULL_SATURATION 255 // Keeps saturation at full
#endif

#ifndef FULL_BRIGHTNESS
  #define FULL_BRIGHTNESS 255 // Sets brightness to full. Does not affect the FastLED global brightness
#endif

#ifndef WHITE_HUE_COLOR
  #define WHITE_HUE_COLOR 255  // Saves special hue value for white.
#endif                         // If hue is set to 255, the saturation will drop to 0 making strip turn white (Max MIDI value of (127 x 2) + 1)




/*
******** MATH CONSTANTS ********
#ifndef MY_TWO_PI
  #define MY_TWO_PI 6.283185307179586476925286766559
#endif
*/

// ***************************************************************************************************************
//            GLOBAL ANIMATION AND COLOR PALLETTE DECLARATIONS
// ***************************************************************************************************************

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


#define WITH_CC_CONTROL true

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
