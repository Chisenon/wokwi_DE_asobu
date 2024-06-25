#include <DHT.h>
#include <Servo.h>

#define DHTPIN 20
#define PHOTOPIN_LEFT 27
#define PHOTOPIN_RIGHT 26
#define DHTTYPE DHT22

const float GAMMA = 0.7;
const float RL10 = 50;

int position = 90;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;

void setup()
{
    Serial1.begin(115200);
    dht.begin();
    servo.attach(22);
    servo.write(position);
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    int analogValueLeft = analogRead(PHOTOPIN_LEFT);
    int analogValueRight = analogRead(PHOTOPIN_RIGHT);
    float voltageLeft = analogValueLeft * (5.0 / 1024.0);
    float voltageRight = analogValueRight * (5.0 / 1024.0);
    float resistanceLeft = 2000 * voltageLeft / (1 - voltageLeft / 5);
    float resistanceRight = 2000 * voltageRight / (1 - voltageRight / 5);
    float luxLeft = powf(RL10 * 1e3 * powf(10, GAMMA) / resistanceLeft, (1 / GAMMA));
    float luxRight = powf(RL10 * 1e3 * powf(10, GAMMA) / resistanceRight, (1 / GAMMA)); 

    float luxDifference = luxRight - luxLeft;

    // 差を0から180の範囲にマッピングする
    if (luxDifference > 0)
    {
        position = map(luxDifference, 0, luxRight, 90, 180);
    }
    else
    {
        position = map(-luxDifference, 0, luxLeft, 90, 0);
    }

    position = constrain(position, 0, 180);

    servo.write(position);

    // デバッグ情報
    Serial1.print("左光センサーの値: ");
    Serial1.print(analogValueLeft);
    Serial1.print("\t左光量: ");
    Serial1.print(luxLeft);
    Serial1.print(" lux\t");

    Serial1.print("右光センサーの値: ");
    Serial1.print(analogValueRight);
    Serial1.print("\t右光量: ");
    Serial1.print(luxRight);
    Serial1.print(" lux\t");

    Serial1.print("サーボ位置: ");
    Serial1.println(position);
    
    if (isnan(h) || isnan(t))
    {
        Serial1.println("失敗っ！！！");
        return;
    }

    Serial1.println("湿度: " + String(h) + " %\t" + "温度: " + String(t) + " *C");

    delay(500);
}
