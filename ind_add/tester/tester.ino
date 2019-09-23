#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    75
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
bool status_on = true;
uint8_t brightness = 255;
//static uint8_t startIndex = 0;

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    Serial.begin(115200);
    delay(500);
    Serial.println("***************************");
    Serial.println("**  Serial Comm Set Up!  **");
    Serial.println("***************************");
    Serial.println("Enter your choice");
}

void loop(){
    //prev_func = curr_func;
    //digital read all pins and compare state if state changes to make it happen always
    int input = Serial.read();
    if(input != 'o'){status_on = true;}
    switch(input){
        case 'a':
            //curr_func = 1;
            Serial.println("RainbowColors - Linear");
            currentPalette = RainbowColors_p;
            currentBlending = LINEARBLEND;
            break;
        case 'b':
            Serial.println("RainbowStripeColors - NOBLEND");
            currentPalette = RainbowStripeColors_p;
            currentBlending = NOBLEND;
            break;
        case 'c':
            Serial.println("Lava - Linear");
            currentPalette = LavaColors_p;
            currentBlending = LINEARBLEND;
            break;
        case 'd':
            Serial.println("Purple and Green - Linear");
            SetupPurpleAndGreenPalette();
            currentBlending = LINEARBLEND;
            break;
        case 'e':
            Serial.println("Random - Linear");
            SetupTotallyRandomPalette();
            currentBlending = LINEARBLEND;
            break;
        case 'f':
            Serial.println("Black and White - Noblend");
            SetupBlackAndWhiteStripedPalette();
            currentBlending = NOBLEND;
            break;
        case 'g':
            Serial.println("Black and White - Linear");
            SetupBlackAndWhiteStripedPalette();
            currentBlending = LINEARBLEND;
            break;
        case 'h':
            Serial.println("Cloud - Linear");
            currentPalette = CloudColors_p;
            currentBlending = LINEARBLEND;
            break;
        case 'i':
            Serial.println("Party - Linear");
            currentPalette = PartyColors_p;
            currentBlending = LINEARBLEND;
            break;
        case 'j':
            Serial.println("Freedom - Noblend");
            currentPalette = myRedWhiteBluePalette_p;
            currentBlending = NOBLEND;
            break;
        case 'k':
            Serial.println("Freedom - Linear");
            currentPalette = myRedWhiteBluePalette_p;
            currentBlending = LINEARBLEND;
            break;
        case 'l':
            Serial.println("yellow - Linear");
            yelllow_setup();
            currentBlending = LINEARBLEND;
            break;
        case 'm':
            Serial.println("yellow2 - Linear");
            yelllow_setup2();
            currentBlending = LINEARBLEND;
            break;

        case 'o':
            Serial.println("bounce - Linear");
            SetupBlackAndWhiteStripedPalette();
            currentBlending = LINEARBLEND;
            break;
    }
    run_me();
}

void run_me(){
    //if(curr_func != prev_func){}
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; // motion speed

    FillLEDsFromPaletteColors(startIndex);
    //bounce(startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex){
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }   
}
/*
void bounce(uint8_t colorIndex){
//    for (int i = 0; i < NUM_LEDS; i++)
//    {
//        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
//        colorIndex += 3;
//    }
    for (int i = NUM_LEDS; i > 0; i--)
    {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
*/
void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    //currentPalette[4] = CRGB::White;
    //currentPalette[8] = CRGB::White;
    //currentPalette[12] = CRGB::White;
    
}

void yelllow_setup()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::FairyLight);
    brightness = 150;
}

void yelllow_setup2()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::FairyLightNCC );
    brightness = 150;
}

void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
