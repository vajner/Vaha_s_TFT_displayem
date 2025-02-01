void operaceNavigace(menuVolby tlacitkoMenu) {
  if (zobrazeno) {
    switch (tlacitkoMenu) {
      case PLUS: {
        menuUp();
        nakresliKuzor();
        break;
      }
      case MINUS: {
        menuDown();
        nakresliKuzor();
        break;
      } 
      case ZPET: {
        operaceMinus();
        zobrazeno = false;
        break;
      }
      case OK: {
        operacePlus();
        zobrazeno = false;
      }
    }
  } else {
    vymazZahlavi();
    vymazVahu();
    zobrazZahlavi("Volby");
    setMenuTlacitka("Zpet", "-", "+", "OK");
    vykresliMenu();
    nakresliKuzor();
    zobrazeno = true;
  }
}

void operacePlus(){
  operaceId = operaceId+(cursorPosition+1);
}

void operaceMinus() {
  operaceId = operaceId-(cursorPosition+1);
  cursorPosition=0;
}