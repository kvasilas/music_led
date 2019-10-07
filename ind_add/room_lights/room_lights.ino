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
#define RED_BTN     13
#define GRE_BTN     12
#define BLK_BTN     8
CRGB leds[NUM_LEDS];
bool status_on = true;
uint8_t brightness = 255;

#define UPDATES_PER_SECOND 100

//Pin reads for buttons
int r1 = 0;
int r2 = 0;
int r3 = 0;
int curr_state = 0;
int next_state = 0;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    
    yelllow_setup();
    currentBlending = LINEARBLEND;

    Serial.begin(115200);
    delay(500);
    Serial.println("***************************");
    Serial.println("**  Serial Comm Set Up!  **");
    Serial.println("***************************");
    Serial.println("Enter your choice");
}


void loop(){
    r1 = digitalRead(RED_BTN);
    r2 = digitalRead(GRE_BTN);
    r3 = digitalRead(BLK_BTN);
    // Red -- Green -- Black
    //  x  --   x   --   x

    if (r1 == LOW && r2 == LOW && r3 == LOW)
    {
        next_state = 0;
        if (next_state != curr_state)
        {
            Serial.println("yelllow - Linear");
            yelllow_setup();
            currentBlending = LINEARBLEND;
            curr_state = 0;
        }
    }
    if (r1 == LOW && r2 == LOW && r3 == HIGH)
    {
        next_state = 1;
        if (next_state != curr_state)
        {
            Serial.println("Freedom - Linear");
            currentPalette = myRedWhiteBluePalette_p;
            currentBlending = LINEARBLEND;
            curr_state = 1;
        }
    }
    else if (r1 == LOW && r2 == HIGH && r3 == LOW)
    {
        next_state = 2;
        if (next_state != curr_state)
        {
            Serial.println("Random - Linear");
            RandomPalette();
            currentBlending = LINEARBLEND;
            curr_state = 2;
        }
    }
    else if (r1 == LOW && r2 == HIGH && r3 == HIGH)
    {
        next_state = 3;
        if (next_state != curr_state)
        {
            Serial.println("Lava - Linear");
            currentPalette = LavaColors_p;
            currentBlending = LINEARBLEND;
            curr_state = 3;
        }
    }
    else if (r1 == HIGH && r2 == LOW && r3 == LOW)
    {
        next_state = 4;
        if (next_state != curr_state)
        {
            Serial.println("RainbowColors - Linear");
            currentPalette = RainbowColors_p;
            currentBlending = LINEARBLEND;
            curr_state = 4;
        }
    }
    else if (r1 == HIGH && r2 == LOW && r3 == HIGH)
    {
        next_state = 5;
        if (next_state != curr_state)
        {
            Serial.println("black and white");
            blue_setup();
            currentBlending = LINEARBLEND;
            curr_state = 5;
        }
    }
    else if (r1 == HIGH && r2 == HIGH && r3 == LOW)
    {
        next_state = 6;
        if (next_state != curr_state)
        {
            Serial.println("Black and White - Linear");
            BlackAndWhiteStripes();
            currentBlending = LINEARBLEND;
            curr_state = 6;
        }
    }
    else if (r1 == HIGH && r2 == HIGH && r3 == HIGH)
    {
        next_state = 7;
        if (next_state != curr_state)
        {
            Serial.println("Cloud - Linear");
            currentPalette = CloudColors_p;
            currentBlending = LINEARBLEND;
            curr_state = 7;
        }
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

void blue_setup()
{
    fill_solid(currentPalette, 16, CRGB::LightBlue);
    brightness = 200;
}
