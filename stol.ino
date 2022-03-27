#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include "FastLED.h"
//-------------  Настройки -------------------
char auth[] = ""; //key
char ssid[] = ""; //Wifi
char pass[] = ""; //Password

#define NUM_LEDS1 10      // количество светодиодов в первом отрезке
#define LED_TYPE    WS2812 // тип ленты
#define PIN1 D1            //пин для подключение ленты
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define COLOR_ORDER GRB

//------------ Для разработчиков --------------

CRGB leds1[NUM_LEDS1];
int effect = 0;
int ef;
int r1, g1 = 255, b1;
int onof;
int data=255;
int r,g,b;
String sost = "false";
String msg;             // переменная для хранения сообщения
byte parseStart = 0;    // переменная запуска парсинга

bool colorLED = 0;      // флаг управления цветом ленты
bool powerLED = 0;      // флаг управления яркостью ленты

int prevPower = 0;      // хранение предыдущего значения яркости
int prevColor = 0;      // хранение предыдущего значения цвета


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "192.168.2.222", 8080); // подключение к серверу
  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
}
 
BLYNK_WRITE(V3)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
 
  static1(r, g, b);
}
BLYNK_WRITE(V4)
{
  int onof = param[0].asInt();
  if (onof == 0)
  {
    sost = "false";
    for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
    
  }
  }
  if(onof == 1)
  {
        sost = "true";
        for (int i = 0; i < NUM_LEDS1; i++ ){
        leds1[i] = CRGB(r1, g1, b1);
        FastLED.show();
        delay(10);}
  }
  Blynk.virtualWrite(V5, sost);
      
}

 
void loop()
{
  Blynk.run();
}








BLYNK_WRITE(V0)
{
  effect = 1;
  int ef = param[0].asInt();
}
BLYNK_WRITE(V2)
{
//effect = 0;
data = 255 / 100 * param.asInt(); 
FastLED.setBrightness(data);
FastLED.show();
}



void static1(int r, int g, int b)
{
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
    FastLED.show();
    delay(10);
  }
  r1 = r;
  g1 = g;
  b1 = b;
}
