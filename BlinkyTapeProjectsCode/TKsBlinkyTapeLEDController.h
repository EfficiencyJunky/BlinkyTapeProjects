/*
  TKsLEDStripController.h     - Class that provides specific controlls of a defined LED Strip using the FastLED Library
                                Originally intended to play nice with MIDI controllers
  Created by Turner E. Kirk, January 20, 2019.
  Released into the public domain.
*/

#ifndef TKsBlinkyTapeLEDController_h
#define TKsBlinkyTapeLEDController_h

// ******************************************************************
//            Includes and Defines
// ******************************************************************
#include <FastLED.h>

#include "TKsLEDStripGlobalVariables.h"
#include "ring.h"
#include "dot.h"

//add more animations here
// #include "animators/DevinAnimation.h"
// #include "animators/DevinAnimationWithCCControl.h"
// #include "animators/DSCupcakePartyAnimation.h"
// #include "animators/FLConfettiAnimation.h"
// #include "animators/FlashbulbWholeStripAnimation.h"
// #include "animators/RainbowAnimation.h"
// #include "animators/ColorPaletteAnimation.h"
// #include "animators/ColorWipeMiddleOut.h"



// ******************************************************************
//            TKsLEDStripController class definitions
// ******************************************************************

// ############## I'M WORKING HERE!!! ##############################################################################################
class TKsLEDStripController
{

  // public variables and functions here for TKsLEDStripController
  public:
    TKsLEDStripController(CRGB *leds, uint16_t _numPixelsInStrip, uint16_t reverseTheLEDConfigurationAt = 0); // Constructor needs to be fully defined
    void Update();
    
    //DIRECT CONTROL VIA MIDI CC MESSAGES
    void SetCenterPixelToLight(uint8_t centerPixelPosition);
    void SetBredthOfPixelsToLight(uint8_t pixelBredth);
    void SetPixelHue(uint8_t pixelHueValue);
    void SetPixelBrightness(uint8_t pixelBrightnessValue);
    void SetAnimationParameter1(uint8_t animationParameter1Value);
    void SetMIDIMessageReceived(bool midiMessageReceivedStatus);
    
    void ToggleAnimation(AnimationType newAnimationState);
    void InitializeAnimation ();
    AnimationType GetActiveAnimationType();
    
  // private variables and functions here for TKsLEDStripController
  private:
    //********** PRIVATE MEMBER VARIABLES **********
    CRGB *ledStrip;
    uint16_t* ledOrder;
    
    TKsLFO* lfoArray;
    
    AnimationType activeAnimationType;
   
    TKsAnimator* animatorArray[TOTAL_NUM_TRIGGERABLE_ANIMATIONS];

    CHSV hsvPlaceholder = CHSV(60, 255, 127); // possibly never used in current configurartion
    //CRGB rgbPlaceholder = CRGB(127, 127, 127); // old setting pre April 15th 2019

    // INITIAL SETTING FOR COLOR OF STRIP  // new setting as of April 15th 2019
    CRGB rgbPlaceholder = CRGB::Black; //CRGB(0, 0, 60) <-- using this will set strip to a dim blue 
    
    //CHSV colorWipeMiddleOutColorCHSV = CHSV(255, 0, WHITE_BRIGHTNESS_ATTENUATOR * FULL_BRIGHTNESS);    
    
    bool midiMessageReceived = true;
    //bool midiMessageReceived = false;

    //LEDStripParameters values; // replace all the items below with this struct to make things easier
    
    uint16_t numPixelsInStrip;
    
    uint16_t lowerPixelBoundary = 0; //Always going to be 0
    uint16_t upperPixelBoundary; //Initialize this in Constructor
  
    uint16_t centerPixelToLight; //Initialize this in Constructor based on actual LED Strip size
    uint16_t bredthOfPixelsToLight; //Initialize this in Constructor function based on actual LED Strip size
    
    uint8_t pixelHue = 0; // Initial state
    uint8_t pixelBrightness = 127;  // Initial state
    uint8_t animationParameter1 = 64;  // Initial state


    //GENERAL UPDATE TIME INTERVALS
    unsigned long lastUpdateTime = 0; // time of last update of position
    uint16_t updateInterval = INITIAL_UPDATE_INTERVAL;   // milliseconds between updates. Likely needs to be 5

 
    //BEATSINE ANIMATION VARIABLES
    uint32_t beatSineTimeBase = 0;
  

    //********** PRIVATE MEMBER FUNCTIOINS **********
    void SetPixelBoundaries();
    void SetStripHSV();
    void SetStripRGB();
    //void SetPixelSaturationNormal();
    CHSV SetWhiteOrNotAndBrightness(uint8_t newBrightness);
    CHSV SetWhiteOrNotAndBrightnessAndSaturation(uint8_t newSaturation, uint8_t newBrightness);
    void UpdateStripWithMIDI_CCInput(); // SHOW STRIP STATE -- loads the leds with the current state and displays



};



#endif
