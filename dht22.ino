// DHT sensor library が必要
#include <DHT.h>

// DHT22 は 20 番ピンにデータを送るよ
#define DHTPIN 20
// DHT22 を使ってるよ～
#define DHTTYPE DHT22

// DHT センサーの初期化
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial1.begin(115200);
    dht.begin();
}

void loop()
{
    delay(3000);

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // センサーからのデータがNaNとかだったら失敗
    if (isnan(h) || isnan(t))
    {
        Serial1.println("失敗っ！！！");
        return;
    }
    
    Serial1.println("湿度: " + String(h) + " %\t" + "温度: " + String(t) + " *C");
}