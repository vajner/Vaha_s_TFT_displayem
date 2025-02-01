/*
  Arduino HX711 vaha s 1.8" TFT I2C Displejem
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "HX711_ADC.h"
#include <EEPROM.h>
//#include <math.h>

const String verzeProgramu = "1.01";

const uint16_t Display_Color_Black = 0x0000;
const uint16_t Display_Color_Blue = 0x001F;
const uint16_t Display_Color_Red = 0xF800;
//const uint16_t Display_Color_Green = 0x07E0;
//const uint16_t Display_Color_Cyan = 0x07FF;
const uint16_t Display_Color_Magenta = 0xF81F;
//const uint16_t Display_Color_Yellow = 0xFFE0;
const uint16_t Display_Color_White = 0xFFFF;

uint16_t      Display_Text_Color = Display_Color_Blue;
uint16_t      Display_Backround_Color = Display_Color_Black;
uint16_t      Display_Text_Color_Value = Display_Color_Magenta;
uint16_t      Display_Menu_Button_Color = Display_Color_White;

unsigned long t = 0;


int kalibracniVaha    = 0;
int oldKalibracniVaha = 0;
byte pauzaTlacitka = 250;
int pruchod = 0;
//int sensorVal = 0;
int sensorOldVal = 0;
//char vybranaOperace = 0;
const byte pozice_hodnoty_vahy_x = 15;
const byte pozice_hodnoty_vahy_y = 45;
const byte vahaTextSize = 5;

boolean vazeni = true;
boolean rezim_menu = false;
enum menuVolby {ZPET, PLUS, MINUS, MENU, OK, null};
const String operace[6] = {"VAZENI", "NAVIGACE", "NASTAVENI", "KALIBRACE", "INFO", "LOGO"};
byte operaceId=0;
int cursorPosition = 0;
boolean zobrazeno = false;
boolean vahaPovolena = true;
boolean vahovySenzorPripraven = false;

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define Btn_menu PD6
#define Btn_plus PD5
#define Btn_minus PD4
#define Btn_zpet PD3

#define vahaDataPin 12
#define vahaClockPin 7

float vaha;

HX711_ADC vahovy_senzor(vahaDataPin, vahaClockPin);
Adafruit_ST7735 TFTscreen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
byte TftOrientation = 3;

void setup() {
  Serial.println("Nastaveni - setup()");
  pinMode(Btn_menu, INPUT_PULLUP);
  pinMode(Btn_plus, INPUT_PULLUP);
  pinMode(Btn_minus, INPUT_PULLUP);
  pinMode(Btn_zpet, INPUT_PULLUP);
  Serial.begin(115200);
  initDisplay();
  initVahovySenzor();
}

void loop() {
  menuVolby tlacitkoMenu = testMenuBtn(pauzaTlacitka);
  switch (tlacitkoMenu) {
    case MENU: {
      operaceMenu();
      break;
    }
  }
  if (operace[operaceId].equals("VAZENI")) {
    operaceVazeni();
  } 
  if(operace[operaceId].equals("NAVIGACE")) {
    operaceNavigace(tlacitkoMenu);
  }
  if(operace[operaceId].equals("NASTAVENI")) {
    operaceNastaveni(tlacitkoMenu);
  }
  if(operace[operaceId].equals("KALIBRACE")) {
    operaceKalibrace(tlacitkoMenu);
  }
  if(operace[operaceId].equals("INFO")) {
    operaceInfo(tlacitkoMenu);
  }
  if(operace[operaceId].equals("LOGO")) {
    operaceLogo(tlacitkoMenu);
  }
  

}

void initDisplay() {
  //Serial.println("Inicializace disleje ....");
  // inicializace ST7735S chipu
  TFTscreen.initR(INITR_BLACKTAB);  

  //Otoc displej - datovy konektor vlevo
  TFTscreen.setRotation(3);
  TFTscreen.fillRect(0, 0, 160, 128, Display_Color_Black);
  //Serial.println("Inicializace disleje - Hotovo ....");
}
