// Define Pins
#define WHITE 7
#define GREEN 4
#define RED 2
#define READ1 8
#define READ2 12
#define READ3 13

int r1 = 0;
int r2 = 0;
int r3 = 0;
int curr_state = 0;
int next_state = 0;

void setup()
{
    Serial.begin(115200);
    delay(500);


    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(WHITE, OUTPUT);
    pinMode(READ1, INPUT);
    pinMode(READ2, INPUT);
    pinMode(READ3, INPUT);

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(WHITE, LOW);
}

void loop(){
    r1 = digitalRead(READ1);
    r2 = digitalRead(READ2);
    r3 = digitalRead(READ3);

    if (r1 == HIGH && r2 == LOW && r3 == LOW)
    {
        next_state = 1;
        if (next_state != curr_state){
            one_high();
            curr_state = 1;
        }
    }
    else if (r1 == LOW && r2 == HIGH && r3 == LOW)
    {

        next_state = 2;
        if(next_state != curr_state){
            two_high();
            curr_state = 2;
        }
    }
    else if (r1 == LOW && r2 == LOW && r3 == HIGH)
    {
        next_state = 3;
        if (next_state != curr_state)
        {
            three_high();
            curr_state = 3;
        }
    }
    else if (r1 == HIGH && r2 == HIGH && r3 == HIGH)
    {
        if (next_state != curr_state)
        {
            next_state = 4;
            all_print();
            curr_state = 4;
        }
    }
}

void stuff_print(){
    Serial.println("r1");
    Serial.println(r1);
    Serial.println("r2");
    Serial.println(r2);
    Serial.println("r3");
    Serial.println(r3);
}
void one_high(){
    Serial.println("One is high");
}
void two_high()
{
    Serial.println("two is high");
}
void three_high()
{
    Serial.println("three is high");
}
void all_print(){
    Serial.println("dicks");
}