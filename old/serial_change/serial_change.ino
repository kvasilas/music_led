// Define Pins
#define BLUE 7
#define GREEN 12
#define RED 2

// define variables
int redValue;
int greenValue;
int blueValue;

void setup()
{
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);

    Serial.begin(115200);
    delay(500);
    Serial.println("***************************");
    Serial.println("**  Serial Comm Set Up!  **");
    Serial.println("***************************");
    Serial.println("Enter your choice");
}

void loop()
{
#define delayTime 10 // fading time between colors
    int input = Serial.read();
    switch (input)
    {
    case 'r':
        r();
        Serial.println("RED");
        break;
    case 'b':
        b();
        Serial.println("BLUE");
        break;
    case 'g':
        g();
        Serial.println("GREEN");
        break;
    case 'o':
        off();
        Serial.println("off");
        break;
    }
}

void r()
{
    redValue = 255;
    greenValue = 0;
    blueValue = 0;
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
}

void g()
{
    redValue = 0;
    greenValue = 255;
    blueValue = 0;
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
}

void b()
{
    redValue = 0;
    greenValue = 0;
    blueValue = 255;
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
}

void off()
{
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
}

void red_to_green()
{
    redValue = 255; // choose a value between 1 and 255 to change the color.
    greenValue = 0;
    blueValue = 0;

    for (int i = 0; i < 255; i += 1)
    {
        redValue -= 1;
        greenValue += 1;
        // The following was reversed, counting in the wrong directions
        // analogWrite(RED, 255 - redValue);
        // analogWrite(GREEN, 255 - greenValue);
        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
        delay(delayTime);
    }
}

void green_to_blue()
{
    redValue = 0;
    greenValue = 255;
    blueValue = 0;

    for (int i = 0; i < 255; i += 1) // fades out green bring blue full when i=255
    {
        greenValue -= 1;
        blueValue += 1;
        // The following was reversed, counting in the wrong directions
        // analogWrite(GREEN, 255 - greenValue);
        // analogWrite(BLUE, 255 - blueValue);
        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
        delay(delayTime);
    }
}

void blue_to_red()
{
    redValue = 0;
    greenValue = 0;
    blueValue = 255;
    for (int i = 0; i < 255; i += 1){
        blueValue -= 1;
        redValue += 1;
        analogWrite(RED, redValue);
        delay(delayTime);
    }
}
