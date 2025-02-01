void operaceInfo(menuVolby tlacitkoMenu) {
  if (zobrazeno) {
    switch (tlacitkoMenu) {
      case ZPET:        {
        operaceMinus();
        zobrazeno = false;
      }
    }
  } else {
    vymazZahlavi();
    vymazVahu();
    zobrazZahlavi("O programu");
    TFTscreen.setTextSize(2);
    TFTscreen.setTextColor(Display_Menu_Button_Color);
    TFTscreen.setCursor(pozice_hodnoty_vahy_x+10, pozice_hodnoty_vahy_y+5);
    TFTscreen.print("Verze:");
    TFTscreen.setCursor(pozice_hodnoty_vahy_x+25, pozice_hodnoty_vahy_y+25);
    TFTscreen.print(verzeProgramu);
    setMenuTlacitka("Zpet", "", "", "");
    zobrazeno = true;
  }
}