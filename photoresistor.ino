// DHT sensor library が必要
#include <DHT.h>

// photoresistor は 26 と 27 番ピンに接続してるよ
#define PHOTOPIN_LEFT 27
#define PHOTOPIN_RIGHT 26

void setup()
{
    Serial1.begin(115200);
}

void loop()
{
    delay(1000);

    // analogRead(PHOTOPIN_LEFT)とanalogRead(PHOTOPIN_RIGHT)をluxに変換する式
    float GAMMA = 0.7;
    float RL10 = 50;
    int analogValueLeft = analogRead(PHOTOPIN_LEFT);
    int analogValueRight = analogRead(PHOTOPIN_RIGHT);
    float voltageLeft = analogValueLeft / 1024. * 5;
    float voltageRight = analogValueRight / 1024. * 5;
    float resistanceLeft = 2000 * voltageLeft / (1 - voltageLeft / 5);
    float resistanceRight = 2000 * voltageRight / (1 - voltageRight / 5);
    float luxLeft = pow(RL10 * 1e3 * pow(10, GAMMA) / resistanceLeft, (1 / GAMMA));
    float luxRight = pow(RL10 * 1e3 * pow(10, GAMMA) / resistanceRight, (1 / GAMMA));

    Serial1.println("左光センサーの値: " + String(analogRead(PHOTOPIN_LEFT)) + "\t" + "左光量: " + String(luxLeft) + " lux");
    Serial1.println("右光センサーの値: " + String(analogRead(PHOTOPIN_RIGHT)) + "\t" + "右光量: " + String(luxRight) + " lux");
}