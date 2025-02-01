void operaceVazeni() {
  if(vahaPovolena) {
    if (zobrazeno) {
      static boolean newDataReady = 0;
      const int serialPrintInterval = 500;
      if (vahovy_senzor.update()) newDataReady = true;
      if (newDataReady) {
        if (millis() > t + serialPrintInterval) {
          int sensorVal = int(vahovy_senzor.getData()+0.5);
          if (sensorVal != sensorOldVal || sensorVal == 0) {
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
          }
          newDataReady = 0;
          t = millis();
        }
      }
    } else {
      vymazZahlavi();
      vymazVahu();
      TFTscreen.setTextColor(Display_Text_Color);
      zobrazZahlavi("Hmotnost");
      zobrazTlacitkaMenu();
      setMenuTlacitka("", "", "", "Menu");
      zobrazeno = true;
    }
  }
}

void initVahovySenzor() {
  Serial.println("Inicializace vahoveho senzoru ....");
  float kalibracniHodnota = 0;
  vahovy_senzor.begin();
  if (!getKalibrovano()) {
    vahaPovolena = false;
    byte x = 10;
    byte y = 30;
    TFTscreen.setTextSize(2);
    TFTscreen.setTextColor(Display_Color_Red);
    TFTscreen.setCursor(x+55, y);
    TFTscreen.print("Je");
    TFTscreen.setCursor(x+15, y+19);
    TFTscreen.print("vyzadovana");
    TFTscreen.setCursor(x+19, y+40);
    TFTscreen.print("kalibrace");
    setMenuTlacitka("", "", "", "Menu");
    zobrazeno = true;
    Serial.println("NOT INIT !!!!");
  } else {
    kalibracniHodnota = getKalibracniHodnota();
    unsigned long stabilizingtime = 2000;
    boolean _tare = true;
    vahovy_senzor.start(stabilizingtime, _tare);
    vahovy_senzor.setCalFactor(kalibracniHodnota);
    Serial.println("Startup is complete");
  }
  Serial.println("Inicializace vahoveho senzoru - Ok");  
}