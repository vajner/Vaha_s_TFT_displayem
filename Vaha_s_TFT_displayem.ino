/*
  Arduino TFT vaha
 */

// #include <TFT.h>  // Arduino LCD library
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "Adafruit_miniTFTWing.h"
#include "HX711.h"
#include <EEPROM.h>
//#include <Fonts/FreeSans18pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>

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
uint16_t      Display_Menu_Button_Color = Display_Color_White;
int         kalibracniHodnota = 0;   //1997;
int         oldKalibracniHodnota = 0;
byte pauzaTlacitka = 250;
int pruchodu = 0;


int sensorVal = 0;
int sensorOldVal = 0;
char vybranaOperace = 0;
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
//float kalibracni_faktor = 196404;

HX711 vahovy_senzor;
Adafruit_ST7735 TFTscreen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
//char sensorPrintout[4];
byte TftOrientation = 3;

void setup() {
  Serial.println("Nastaveni - setup()");
  pinMode(Btn_menu, INPUT_PULLUP);
  pinMode(Btn_plus, INPUT_PULLUP);
  pinMode(Btn_minus, INPUT_PULLUP);
  pinMode(Btn_zpet, INPUT_PULLUP);
  Serial.begin(115200);
  initDisplay();
  //showLogo();
  zobrazZahlavi("Hmotnost");
  zobrazTlacitkaMenu();
  setMenuTlacitka("", "", "", "Menu");
  initVahovySenzor();
  kalibracniHodnota = getKalibracniHodnota();
  //TFTscreen.setFont(&FreeSans18pt7b);
}

void loop() {
  menuVolby tlacitkoMenu = testMenuBtn(pauzaTlacitka);
 
  switch (tlacitkoMenu) {
    case MENU: {
      Serial.println(" ---- Zvoleno MENU ---");
      operaceId=indexOfOperace("NAVIGACE");
      break;
    }
    /*case PLUS: {
      Serial.println(" ---- Zvoleno PLUS ---");
      menuUp();
      nakresliKuzor();
      break;
    }
    case MINUS: {
      Serial.println(" ---- Zvoleno MINUS ---");
      menuDown();
      nakresliKuzor();
      break;
    }*/
    case ZPET: {
      Serial.println(" ---- Zvoleno ZPET ---");
      Serial.print("cursorPosition=");
      Serial.print(cursorPosition);
      Serial.print("   operaceId pred=");
      Serial.print(operaceId);
      operaceId--;
      Serial.print("   operaceId po=");
      Serial.print(operaceId);
      Serial.print("   operace=");
      Serial.println(operace[operaceId]);
      
      /*if (operace[operaceId]=="VAZENI") {
        //vazeni = true;
        //operaceId--;
        //cursorPosition=0;
        vymazZahlavi();
        vymazVahu();
        zobrazZahlavi("Hmotnost");
        zobrazTlacitkaMenu();
        setMenuTlacitka("", "", "", "Menu");
        initVahovySenzor();
      }*/
      break;
    }
    case OK: {
      if(operace[operaceId].equals("NAVIGACE")) {
        Serial.println(" ---- Zvoleno OK ---");
        Serial.print("operaceId pred=");
        Serial.print(operaceId);
        Serial.print("   operace=");
        Serial.println(operace[operaceId]);
        operaceId = operaceId+cursorPosition+1;
        zobrazeno = false;
        Serial.print("operaceId po=");
        Serial.print(operaceId);
        Serial.print("    operace=");
        Serial.println(operace[operaceId]);
      }
    }
    /*default: {
      tlacitkoMenu = null;
    }*/

  }

  if (operace[operaceId]=="VAZENI") {
    // nacti hodnotu senzoru na pinu A0
    sensorVal = (vahovy_senzor.get_units(HX711_AVERAGE_MODE)+0.5);
    
    if (sensorVal != sensorOldVal) {
      vahovy_senzor.set_scale(kalibracniHodnota);
      Serial.print("Vaha: ");
      Serial.println(sensorVal);
      TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
      TFTscreen.setTextSize(vahaTextSize);

      // vycisti text pokud se hodnota zmenila
      TFTscreen.setTextColor(Display_Backround_Color);
      TFTscreen.print(sensorOldVal);
      
      TFTscreen.setTextColor(Display_Text_Color_Value);
      TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);

      // print hodnotu sensoru
      TFTscreen.print(sensorVal);
      sensorOldVal = sensorVal;
      delay(1000);
    } 
  } 
  /*else {
    TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
    TFTscreen.setTextColor(Display_Backround_Color);
    TFTscreen.print(sensorOldVal);
  }*/
  
  if(operace[operaceId]=="NAVIGACE") {
    if(zobrazeno) {
      //Serial.print("operace[operaceId]==NAVIGACE");
      //Serial.print("     tlacitko-");
      //Serial.println(tlacitkoMenu);
      switch (tlacitkoMenu) {
        case PLUS: {
          Serial.println(" ---- Zvoleno PLUS ---");
          menuUp();
          nakresliKuzor();
          break;
        }
        case MINUS: {
          Serial.println(" ---- Zvoleno MINUS ---");
          menuDown();
          nakresliKuzor();
          break;
        }
      }
    } else {
      vymazZahlavi();
      vymazVahu();
      //zobrazZahlaviNasteveni(true, Display_Backround_Color, Display_Text_Color);
      //zobrazZakladniMenu(true);
      zobrazZahlavi("Volby");
      //zobrazTlacitkaMenu();
      setMenuTlacitka("Zpet", "-", "+", "OK");
      vykresliMenu();
      nakresliKuzor();
      zobrazeno=true;
    }
  }

  if(operace[operaceId]=="LOGO" and !zobrazeno) {
    Serial.print("operaceId=");
    Serial.println(operaceId);
    showLogo();
    zobrazTlacitkaMenu();
    setMenuTlacitka("Zpet", "", "", "");
    zobrazeno=true;
  }

  if(operace[operaceId]=="NASTAVENI") {
    if(zobrazeno) {
      if (kalibracniHodnota != oldKalibracniHodnota) {
        TFTscreen.setTextSize(vahaTextSize);
        TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
        // vycisti text pokud se hodnota zmenila
        TFTscreen.setTextColor(Display_Backround_Color);
        TFTscreen.print(oldKalibracniHodnota);
        TFTscreen.setTextColor(Display_Text_Color_Value);
        TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
        TFTscreen.print(kalibracniHodnota);
        oldKalibracniHodnota = kalibracniHodnota;
        //delay(500);
      } 
      switch (tlacitkoMenu) {
        case PLUS: {
          Serial.print(" ---- Zvoleno PLUS ---");
          Serial.print("pauzaTlacitka-");
          Serial.println(pauzaTlacitka);
          kalibracniHodnota++;
          //pruchodu++;
          if(pauzaTlacitka > 10) {
            pauzaTlacitka=pauzaTlacitka-10;
          }
          break;
        }
        case MINUS: {
          Serial.println(" ---- Zvoleno MINUS ---");
          kalibracniHodnota--;
          //pruchodu--;
          if(pauzaTlacitka > 10) {
            pauzaTlacitka=pauzaTlacitka-10;
          }
          break;
        }
        case OK: {
          setKalibracniHodnota(kalibracniHodnota);
        }
        default:{
          //pruchodu=0;
          pauzaTlacitka=255;
        }
      }
    } else {
      Serial.print("operaceId=");
      Serial.println(operaceId);
      vymazZahlavi();
      vymazVahu();
      zobrazZahlavi("Nastaveni");
      setMenuTlacitka("Zpet", "-", "+", "Ok");
      zobrazeno=true;
    }
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
  // inicializace ST7735S chipu
  TFTscreen.initR(INITR_BLACKTAB);  

  //Otoc displej - datovy konektor vlevo
  TFTscreen.setRotation(3);
  TFTscreen.fillRect(0, 0, 160, 128, Display_Color_Black);
  Serial.println("... Hotovo ....");
}

void setKalibracniHodnota(int kalibracniHodnota) {
  Serial.print("Zapis hodnoty do EEPROM-");
  Serial.print(kalibracniHodnota);
  //EEPROM.update(0, kalibracniHodnota);
  EEPROM.write(0, kalibracniHodnota);
  EEPROM.write(1, kalibracniHodnota >> 8);
  Serial.println("    - zapsano");
}

int getKalibracniHodnota() {
  Serial.print("Nacitani dat z EEPROM-");
  //int value = EEPROM.read(0);
  int val;
  val = (EEPROM.read(1) << 8);
  val |= EEPROM.read(0);
  if (isnan(val)) {
    val = 0;
  }
  Serial.print("nacteno=");
  Serial.println(val);
  return val;
}



