/*
  Arduino TFT vaha
 */

// #include <TFT.h>  // Arduino LCD library
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "Adafruit_miniTFTWing.h"
#include "HX711.h"

// color definitions
const uint16_t Display_Color_Black = 0x0000;
const uint16_t Display_Color_Blue = 0x001F;
const uint16_t Display_Color_Red = 0xF800;
const uint16_t Display_Color_Green = 0x07E0;
const uint16_t Display_Color_Cyan = 0x07FF;
const uint16_t Display_Color_Magenta = 0xF81F;
const uint16_t Display_Color_Yellow = 0xFFE0;
const uint16_t Display_Color_White = 0xFFFF;

// The colors we actually want to use
uint16_t      Display_Text_Color = Display_Color_Blue;
uint16_t      Display_Backround_Color = Display_Color_Black;
uint16_t      Display_Text_Color_Value = Display_Color_Magenta;
uint8_t       Display_Veigth_Size = 6;
float         Kalibracni_Hodnota = 1997;

int sensorVal = "";
int sensorOldVal = "";



#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9

#define vahaDataPin 3
#define vahaClockPin 7

float vaha;
float alibracni_faktor = 196404;

HX711 vahovy_senzor;
Adafruit_ST7735 TFTscreen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
char sensorPrintout[4];
byte TftOrientation = 3;

void setup() {
  Serial.begin(115200);
  initDisplay();
  initVahovySenzor();
  
}

void loop() {

  // nacti hodnotu senzoru na pinu A0
  sensorVal = vahovy_senzor.get_units(HX711_AVERAGE_MODE)+0.5;
  
  if (sensorVal != sensorOldVal) {
    vahovy_senzor.set_scale(Kalibracni_Hodnota);
    Serial.print("Vaha: ");
    Serial.println(sensorVal);
    TFTscreen.setCursor(30, 60);
    TFTscreen.setTextSize(Display_Veigth_Size);

    // vycisti text pokud se hodnota zmenila
    TFTscreen.setTextColor(Display_Backround_Color);
    TFTscreen.print(sensorOldVal);
    
    TFTscreen.setTextColor(Display_Text_Color_Value);
    TFTscreen.setCursor(30, 60);

    // print hodnotu sensoru
    TFTscreen.print(sensorVal);
    sensorOldVal = sensorVal;
    delay(1000);
  }
}

void initVahovySenzor() {
  Serial.println("Inicializace vahoveho senzoru ....");
  Serial.print("HX711_LIB_VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  vahovy_senzor.begin(vahaDataPin, vahaClockPin);
  vahovy_senzor.set_scale();
  vahovy_senzor.tare();
  vahovy_senzor.calibrate_scale(186, 5);
  Serial.println("... Hotovo ....");
}

void initDisplay() {
  Serial.println("Inicializace disleje ....");
  TFTscreen.initR(INITR_BLACKTAB);  // inicializace ST7735S chipu

  // Vymaz displej a nastav cerne pozadi
  TFTscreen.setFont();
  TFTscreen.fillScreen(Display_Backround_Color);
  TFTscreen.setTextSize(1);

  //Otoc displej - datovy konektor vlevo
  TFTscreen.setRotation(3);

  // zapis staticky text na displej
  // nastav barvu textu
  TFTscreen.setTextColor(Display_Text_Color);

  // set the font size
  TFTscreen.setTextSize(2);
  // nastav souradnice pocatku textu
  TFTscreen.setCursor(30, 10);
  // zapis text
  TFTscreen.print("Hmotnost");
  TFTscreen.setCursor(0, 0);
  TFTscreen.drawFastHLine(5, 30, 150, ST77XX_BLUE);
  TFTscreen.drawFastHLine(5, 31, 150, ST77XX_BLUE);
  TFTscreen.drawFastHLine(5, 32, 150, ST77XX_BLUE);
  Serial.println("... Hotovo ....");
}
