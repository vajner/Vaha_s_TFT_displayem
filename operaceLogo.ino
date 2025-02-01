void operaceLogo(menuVolby tlacitkoMenu) {
  if (zobrazeno) {
    switch (tlacitkoMenu) {
      case ZPET:        {
        operaceMinus();
        zobrazeno = false;
      }
    }
  } else {
    showLogo();
    //setMenuTlacitka("Zpet", "", "", "");
    zobrazeno = true;
  }
}