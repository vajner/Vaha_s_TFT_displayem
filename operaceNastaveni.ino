void operaceNastaveni(menuVolby tlacitkoMenu) {
  if(zobrazeno) {
      if (kalibracniVaha != oldKalibracniVaha || kalibracniVaha == 0) {
        TFTscreen.setTextSize(vahaTextSize);
        TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
        // vycisti text pokud se hodnota zmenila
        TFTscreen.setTextColor(Display_Backround_Color);
        TFTscreen.print(oldKalibracniVaha);
        TFTscreen.setTextColor(Display_Text_Color_Value);
        TFTscreen.setCursor(pozice_hodnoty_vahy_x, pozice_hodnoty_vahy_y);
        TFTscreen.print(kalibracniVaha);
        oldKalibracniVaha = kalibracniVaha;
      } 
      switch (tlacitkoMenu) {
        case PLUS: {
          kalibracniVaha++;
          if(pauzaTlacitka > 10) {
            pauzaTlacitka=pauzaTlacitka-10;
          }
          break;
        }
        case MINUS: {
          kalibracniVaha--;
          if(kalibracniVaha < 0) {
            kalibracniVaha = 0;
          }
          if(pauzaTlacitka > 10) {
            pauzaTlacitka=pauzaTlacitka-10;
          }
          break;
        }
        case OK: {
          setKalibracniVaha(kalibracniVaha);
        }
        case ZPET: {
          operaceId--;
          zobrazeno = false;
        }
        default:{
          pauzaTlacitka=255;
        }
      }
    } else {
      kalibracniVaha = getKalibracniVaha();
      vymazZahlavi();
      vymazVahu();
      zobrazZahlavi("Nastaveni");
      setMenuTlacitka("Zpet", "-", "+", "Ok");
      zobrazeno=true;
    }
}
