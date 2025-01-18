void setMenuTlacitka(String tl_1_txt, String tl_2_txt, String tl_3_txt, String tl_4_txt, boolean zobrazit) {
  byte y=116;

  if (zobrazit) {
    TFTscreen.setTextColor(Display_Menu_Button_Color);
  } else {
    TFTscreen.setTextColor(Display_Text_Color);
  }
  //TFTscreen.setFont(&FreeSerif9pt7b);
  TFTscreen.setFont();
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(8, y);
  TFTscreen.print(tl_1_txt);
  TFTscreen.setCursor(59, y);
  TFTscreen.print(tl_2_txt);
  TFTscreen.setCursor(99, y);
  TFTscreen.print(tl_3_txt);
  TFTscreen.setCursor(130, y);
  TFTscreen.print(tl_4_txt);
}

void zobrazZakladniMenu(boolean zobrazit) {
  //setMenuTlacitka("Zpet", "-", "+", "Menu", true);
  setMenuTlacitka("", "", "", "Menu", zobrazit);
}

void zobrazTlacitkaMenu() {
  byte sirka_tlacitka = 39;
  byte vyska_tlacitka = 15;
  byte poziceTlacitka = 1;
  byte odskok_y = 113;
  for(int i = 1; i <= 4; i++) {
    TFTscreen.fillRect(poziceTlacitka, odskok_y, sirka_tlacitka, vyska_tlacitka, Display_Text_Color);
    poziceTlacitka = poziceTlacitka+1+sirka_tlacitka;
    Serial.print("poziceTlacitka : ");
    Serial.println(poziceTlacitka);
   }
}

void zobrazZahlaviVahy(String text, boolean zobrazit){
  if(zobrazit) {
    TFTscreen.setTextColor(Display_Text_Color);
  } else {
    TFTscreen.setTextColor(Display_Backround_Color);
  }
  TFTscreen.setFont();
  TFTscreen.setTextSize(1);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(30, 10);
  TFTscreen.print(text);
  TFTscreen.setCursor(0, 0);
  TFTscreen.drawFastHLine(5, 30, 150, ST77XX_BLUE);
  TFTscreen.drawFastHLine(5, 31, 150, ST77XX_BLUE);
  TFTscreen.drawFastHLine(5, 32, 150, ST77XX_BLUE);
}

String testMenuBtn() {
  Serial.println("Test tlacitka");
  String tlacitko;
  if(getValBtnMenu() == LOW) {
    tlacitko = "MENU";
    Serial.print("Menu btn ");
    Serial.print(tlacitko);
    Serial.print(":");
    Serial.println(getValBtnMenu());
  }
  if(getValBtnPlus() == LOW) {
    tlacitko = "PLUS";
    Serial.print("Menu btn ");
    Serial.print(tlacitko);
    Serial.print(":");
    Serial.println(getValBtnPlus());
  }

  
  return tlacitko;
}

int getValBtnMenu(){
  return digitalRead(Btn_menu);
}

int getValBtnPlus(){
  return digitalRead(Btn_plus);
}

int getValBtnMinus(){
  return digitalRead(Btn_minus);
}

int getValBtnZpet(){
  return digitalRead(Btn_zpet);
}
