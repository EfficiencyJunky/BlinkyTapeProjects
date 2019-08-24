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
class TKsBlinkyTapeLEDController
{

  // public variables and functions here for TKsLEDStripController
  public:

    TKsBlinkyTapeLEDController(CRGB *leds, CRGBPalette16 pPalettes, uint16_t pLedStripEndIndex, bool reverseTheLEDConfiguration = false);
    void Update();
    void nextPattern();
    void nextPalette();

    void fastBlink();
    void showCurrentBrightness();
    void showCurrentPalette();
    void setStripState(uint8_t NEW_STATE);
    uint8_t getStripState();



    // TKsLEDStripController(CRGB *leds, uint16_t _numPixelsInStrip, uint16_t reverseTheLEDConfigurationAt = 0); // Constructor needs to be fully defined
    // void Update();
    
    // //DIRECT CONTROL VIA MIDI CC MESSAGES
    // void SetCenterPixelToLight(uint8_t centerPixelPosition);

    // //HELPER METHODS    
    // void ToggleAnimation(AnimationType newAnimationState);
    // void InitializeAnimation ();
    // AnimationType GetActiveAnimationType();
    
  // private variables and functions here for TKsLEDStripController
  private:

    //********** PRIVATE MEMBER VARIABLES **********
    CRGB *ledStrip;

//    uint16_t* ledOrder;

    uint8_t STATE = 0;
    
    CRGB brightnessDemoColor = CRGB::Blue;
    
    uint16_t numPixelsInStrip;
    uint16_t ledStripStartIndex;

    bool gReverseDirection = false;

    unsigned long lastPatternUpdateTime = 0; // time of last update of the pattern
    unsigned long lastHueUpdateTime = 0;  
    unsigned long lastCycleUpdateTime = 0;
  
    unsigned long patternUpdateInterval = 0;   // milliseconds between updates. Likely needs to be 5
    unsigned long hueUpdateInterval = 10;
    unsigned long fireUpdateInterval = 15;
    unsigned long cycleUpdateInterval = 10000;
    
    typedef void (TKsBlinkyTapeLEDController::*AnimationsList[12])(); // make sure to update the number (currently 11) when adding animations to the structure below
  
    AnimationsList gPatterns = { &TKsBlinkyTapeLEDController::rainbow, 
                                 &TKsBlinkyTapeLEDController::rainbowWithGlitter,
                                 &TKsBlinkyTapeLEDController::confetti,
                                 //&TKsBlinkyTapeLEDController::patrioticConfetti,
                                 &TKsBlinkyTapeLEDController::paletteConfetti,
                                 &TKsBlinkyTapeLEDController::sinelon,
                                 &TKsBlinkyTapeLEDController::sinelon2,
                                 &TKsBlinkyTapeLEDController::juggle,
                                 //&TKsBlinkyTapeLEDController::gearDots,
                                 &TKsBlinkyTapeLEDController::bpm, 
                                 &TKsBlinkyTapeLEDController::FillLEDsFromPaletteColors,
                                 &TKsBlinkyTapeLEDController::fire2012WithPalette, // always must be third to last
                                 &TKsBlinkyTapeLEDController::cycle, //this animation always must be second to last
                                 &TKsBlinkyTapeLEDController::fadeToBlack};
    
    //Need to add a list of palettes to cycle though here            
    CRGBPalette16 gPalettes;

    uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
    uint8_t gCurrentPaletteNumber = 0; // Index number of which palette is current
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns

    uint8_t cycleFunctionPatternIndex = 0;
    

// GEAR DOTS
    Ring *r1;
    Ring *r2;

    Dot *d1;
    Dot *d2;
    Dot *d3;
    Dot *d4;
    Dot *d5;
    Dot *d6;
    Dot *d7;
    Dot *d8;
    
    Dot *dots;
// GEAR DOTS

//START **** FIRE ANIMATION CLASS VARIABLE
    // Array of temperature readings at each simulation cell
    // Since this is in a class now, the heat array has been declared as a class member
    byte *heat;
//END **** FIRE ANIMATION CLASS VARIABLE


    //********** PRIVATE ANIMATION AND MEMBER FUNCTIOINS **********
    //********** PRIVATE ANIMATION AND MEMBER FUNCTIOINS **********
    //********** PRIVATE ANIMATION AND MEMBER FUNCTIOINS **********
    //********** PRIVATE ANIMATION AND MEMBER FUNCTIOINS **********        
    void rainbow();
    void rainbowWithGlitter();
    void addGlitter( fract8 chanceOfGlitter);
    void confetti();
    void patrioticConfetti();
    void paletteConfetti();
    void sinelon();
    void sinelon2();
    void juggle();
    void bpm();
    // GEAR DOTS
    void gearDots();
    // change patterns periodically
    void cycle();
    void fire2012WithPalette();
    void FillLEDsFromPaletteColors();
    void FillLEDsFromPaletteOneColorAtAtime();
    void fadeToBlack();



    //********** PRIVATE MEMBER FUNCTIOINS **********
    // void SetPixelBoundaries();
    // void SetStripHSV();
    // void SetStripRGB();
    // //void SetPixelSaturationNormal();
    // CHSV SetWhiteOrNotAndBrightness(uint8_t newBrightness);
    // CHSV SetWhiteOrNotAndBrightnessAndSaturation(uint8_t newSaturation, uint8_t newBrightness);
    // void UpdateStripWithMIDI_CCInput(); // SHOW STRIP STATE -- loads the leds with the current state and displays



};



#endif
