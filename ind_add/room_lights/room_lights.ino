/*
 * code to control ws281b individually addressable lights using an arduino nano
 *
 * Kirk Vasilas 
 * 
 */

#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    261
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define RED_BTN     1
#define GRE_BTN     2
#define BLK_BTN     3
CRGB leds[NUM_LEDS];
bool status_on = true;
uint8_t brightness = 255;

#define UPDATES_PER_SECOND 100

//Pin reads for buttons
bool d1 = false;
bool d2 = false;
bool d3 = false;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    yelllow_setup();
    currentBlending = LINEARBLEND;

    Serial.begin(115200);
    delay(500);
    Serial.println("***************************");
    Serial.println("**  Serial Comm Set Up!  **");
    Serial.println("***************************");
    Serial.println("Enter your choice");
}

/*
void loop(){
    d1 = digital.read(p1);
    d2 = digital.read(p2);
    d3 = digital.read(p3);

    
    if(d1 && !d2 && !d3){
        Serial.println("Freedom - Linear");
        currentPalette = myRedWhiteBluePalette_p;
        currentBlending = LINEARBLEND;
    }
    if(d1 && !d2 && !d3){
        Serial.println("yelllow - Linear");
        yelllow_setup();
        currentBlending = LINEARBLEND;
    }
}
*/


void loop(){
    //prev_func = curr_func;
    //digital read all pins and compare state if state changes to make it happen always
    int input = Serial.read();
    switch(input){
        case '0':
            Serial.println("yelllow - Linear");
            yelllow_setup();
            currentBlending = LINEARBLEND;
            break;
        case '1':
            Serial.println("Freedom - Linear");
            currentPalette = myRedWhiteBluePalette_p;
            currentBlending = LINEARBLEND;
            break;
        case '2':
            Serial.println("Random - Linear");
            RandomPalette();
            currentBlending = LINEARBLEND;
            break;
        case '3':
            Serial.println("Lava - Linear");
            currentPalette = LavaColors_p;
            currentBlending = LINEARBLEND;
            break;
        case '4':
            Serial.println("RainbowColors - Linear");
            currentPalette = RainbowColors_p;
            currentBlending = LINEARBLEND;
            break;
        case '5':
            Serial.println("bounce");
            break;
        case '6':
            Serial.println("Black and White - Linear");
            BlackAndWhiteStripes();
            currentBlending = LINEARBLEND;
            break;
        case '7':
            Serial.println("Cloud - Linear");
            currentPalette = CloudColors_p;
            currentBlending = LINEARBLEND;
            break;
    }
    run_me();
}

void run_me(){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; // motion speed

    FillLEDsFromPaletteColors(startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex){
    brightness = 255;

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }   
}


// This function fills the palette with totally random colors.
void RandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void BlackAndWhiteStripes()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    
}

void yelllow_setup()
{
    fill_solid( currentPalette, 16, CRGB::FairyLightNCC );
    brightness = 150;
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
