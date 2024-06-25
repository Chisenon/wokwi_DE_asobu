#include <Servo.h>

int position = 90;

Servo servo;

void setup()
{
    servo.attach(22);
}

void loop()
{
    while (position <= 180)
    {
        servo.write(position);
        delay(15);
        position += 1;
    }
    while (position >= 0)
    {
        servo.write(position);
        delay(15);
        position -= 1;
    }
    
}