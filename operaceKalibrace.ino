void operaceKalibrace(menuVolby tlacitkoMenu) {
  if (zobrazeno) {
    switch (tlacitkoMenu) {
      case ZPET: {
        Serial.print("operace=");
        Serial.println(operace[operaceId]);
        operaceMinus();
        zobrazeno = false;
        Serial.print("operace=");
        Serial.println(operace[operaceId]);
        //pruchod = 0;
        break;
      }
      case OK: {
        pruchod++;
        zobrazeno = false;
        break;
      }
    }
  } else {
    Serial.println("operaceKalibrace - ELSE");
    vymazZahlavi();
    vymazVahu();
    zobrazZahlavi("Kalibrace");
    setMenuTlacitka("Zpet", "", "", "Ok");
    TFTscreen.setTextSize(2);
    TFTscreen.setTextColor(Display_Menu_Button_Color);
    TFTscreen.setCursor(0, pozice_hodnoty_vahy_y-5);
    switch (pruchod) {
      case 0: {
        TFTscreen.println("   Uvolnete");
        TFTscreen.println("    senzor");
        TFTscreen.println("      a");
        TFTscreen.println(" stisknete OK");
        zobrazeno=true;
        break;
      }
      case 1: {
        Serial.println("Krok 1 - kalibrace");
        vymazVahu();
        TFTscreen.println("   Kalibruji");
        kalibracePrazdnehoCidla();
        pruchod++;
        zobrazeno=true;
      }
      case 2: {
        vymazVahu();
        TFTscreen.setCursor(0, pozice_hodnoty_vahy_y-5);
        TFTscreen.println("   Zatizte");
        TFTscreen.println("    senzor");
        TFTscreen.println("      a");
        TFTscreen.println(" stisknete OK");
        zobrazTlacitkaMenu();
        setMenuTlacitka("Zpet", "", "", "Ok");
        zobrazeno=true;
        break;
      }
      case 3:{
        vymazVahu();
        TFTscreen.println("   Kalibruji");
        pruchod++;
        kalibraceZatizenehoCidla();
      }
      case 4: {
          vymazVahu();
          TFTscreen.println("    Senzor");
          TFTscreen.println("   nastaven");
          zobrazTlacitkaMenu();
          setMenuTlacitka("Zpet", "", "", "");
          zobrazeno = true;
      }
    } 
  }
}

void kalibraceZatizenehoCidla() {
    float znamaVaha = getKalibracniVaha();
    Serial.println(znamaVaha);
    vahovy_senzor.refreshDataSet();
    float newCalibrationValue = vahovy_senzor.getNewCalibration(znamaVaha);
    Serial.print("Nova kalibracni hodnota nestavena na:");
    Serial.print(newCalibrationValue);
    setKalibracniHodnota(newCalibrationValue);
}

void kalibracePrazdnehoCidla() {
  Serial.println("Kalibrace praydneho cidla ......");
  boolean _resume = false;
  boolean kalibrovat = true;
  while (_resume == false) {
    Serial.println("Krok 1 - kalibrovani ......");
    vahovy_senzor.update();
    if(kalibrovat) {
      vahovy_senzor.tareNoDelay();
      kalibrovat = false;
    }
    if (vahovy_senzor.getTareStatus() == true) {
      Serial.println("Kalibrace ukoncena");
      _resume = true;
    }
  }
}
