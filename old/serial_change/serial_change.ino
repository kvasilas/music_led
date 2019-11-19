void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    delay(500);
    Serial.println("***************************");
    Serial.println("**  Serial Comm Set Up!  **");
    Serial.println("***************************");
}

void loop()
{
    // put your main code here, to run repeatedly:
    int input = Serial.read();
    switch (input)
    {
    case 'r':
        // r();
        Serial.println("RED");
        break;
    case 'b':
        //b();
        Serial.println("BLUE");
        break;
    case 'g':
        // g();
        Serial.println("GREEN");
        break;
    case 'o':
        //off();
        Serial.println("off your self");
        break;
    }
}