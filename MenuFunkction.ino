



//Menu
const byte pocet_polozek_menu = 4;
const String polozky_menu[pocet_polozek_menu] = {"Zapis vahy", "Kalibrace", "O produktu", "Kontakt"};

// Navigation button variables
//int readKey;
// Menu control variables
//int menuPage = 0;
//int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 4) + .5);

const byte text_size = 2;
const byte menu_x = 20;
const byte menu_y = 38;
const byte menu_vyska_radku=17;
const byte kurzor_x = 5;
const String kurzor = ">";
boolean tl_1_active = true;
boolean tl_2_active = true;
boolean tl_3_active = true;
boolean tl_4_active = true;


//boolean inMenu = false;

void vykresliMenu() {
  TFTscreen.setTextColor(Display_Menu_Button_Color);
  TFTscreen.setTextSize(text_size);
  byte y = menu_y;
  for(String polozka_menu : polozky_menu) {
    Serial.print("Menu - pozice textu:");
    Serial.println(y);
    TFTscreen.setCursor(menu_x, y);
    TFTscreen.print(polozka_menu);
    y = y + menu_vyska_radku;
  }
}

void nakresliKuzor() {
  byte x = kurzor_x;
  byte y = menu_y;
  byte pruchod = 0;
  Serial.print("nakresliKuzor() ---- ");
  TFTscreen.setTextSize(text_size);

  for(String polozka_menu : polozky_menu) {
    TFTscreen.setCursor(x, y);
    Serial.print("y:");
    Serial.print(y);
    y = y + menu_vyska_radku;
    Serial.print("    vyska_radku:");
    Serial.print(menu_vyska_radku);
    Serial.print("   - celkem:");
    Serial.print(y);
    Serial.print("   pruchod:");
    Serial.print(pruchod);
    Serial.print("  cursorPosition:");
    Serial.println(cursorPosition);

    if(pruchod == cursorPosition) {
      TFTscreen.setTextColor(Display_Menu_Button_Color);
      TFTscreen.print(kurzor);
    } else {
      TFTscreen.setTextColor(Display_Color_Black);
      TFTscreen.print(kurzor);
    }
    pruchod++;
  }
}

void menuDown(){
  cursorPosition = cursorPosition-1;
  rollMenu();
  //delay(pauza);
}

void menuUp(){
  cursorPosition = cursorPosition+1;
  rollMenu();
  //delay(pauza);
}

void rollMenu(){
  Serial.print("rollMenu() : cursorPosition:");
  Serial.print(cursorPosition);
  if(cursorPosition > pocet_polozek_menu-1){
    cursorPosition=0;
  }
  if(cursorPosition < 0){
    cursorPosition = pocet_polozek_menu-1;
  }
  Serial.print("  nastaveno:");
  Serial.println(cursorPosition);
}

void setMenuTlacitka(String tl_1_txt, String tl_2_txt, String tl_3_txt, String tl_4_txt) {
  byte y=116;
  Serial.print("TL  1-");
  if(!tl_1_txt.equals("")) {
    Serial.print("povoleno");
    tl_1_active=true;
  } else {
    Serial.print("zakazano");
    tl_1_active=false;
  }
  
  Serial.print("  2-");
  if(!tl_2_txt.equals("")) {
    Serial.print("povoleno");
    tl_2_active=true;
  } else {
    Serial.print("zakazano");
    tl_2_active=false;
  }

  Serial.print("  3-");
  if(!tl_3_txt.equals("")) {
    Serial.print("povoleno");
    tl_3_active=true;
  } else {
    Serial.print("zakazano");
    tl_3_active=false;
  }

  Serial.print("  4-");
  if(!tl_4_txt.equals("")) {
    Serial.print("povoleno");
    tl_4_active=true;
  } else {
    Serial.print("zakazano");
    tl_4_active=false;
  }
  Serial.println();

  zobrazTlacitkaMenu();
  TFTscreen.setTextColor(Display_Menu_Button_Color);
  //TFTscreen.setFont(&FreeSerif9pt7b);
  //TFTscreen.setFont();
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

void zobrazTlacitkaMenu() {
  byte sirka_tlacitka = 39;
  byte vyska_tlacitka = 15;
  byte poziceTlacitka = 1;
  byte odskok_y = 113;
  boolean povoleno = true;
  for(int i = 1; i <= 4; i++) {
    if(i==1) {povoleno = tl_1_active;}
    if(i==2) {povoleno = tl_2_active;}
    if(i==3) {povoleno = tl_3_active;}
    if(i==4) {povoleno = tl_4_active;}
    if(povoleno) {
      TFTscreen.fillRect(poziceTlacitka, odskok_y, sirka_tlacitka, vyska_tlacitka, Display_Text_Color);
    } else {
      TFTscreen.fillRect(poziceTlacitka, odskok_y, sirka_tlacitka, vyska_tlacitka, Display_Backround_Color);
    }
    poziceTlacitka = poziceTlacitka+1+sirka_tlacitka;
    Serial.print("poziceTlacitka : ");
    Serial.println(poziceTlacitka);
   }
}


void zobrazZahlavi(String text){
  TFTscreen.setFont();
  TFTscreen.setTextSize(text_size);
  TFTscreen.setCursor(30, 10);
  TFTscreen.setTextColor(Display_Text_Color);
  TFTscreen.drawFastHLine(5, 30, 150, Display_Text_Color);
  TFTscreen.drawFastHLine(5, 31, 150, Display_Text_Color);
  TFTscreen.drawFastHLine(5, 32, 150, Display_Text_Color);
  TFTscreen.print(text);
}

menuVolby testMenuBtn(byte pauza) {
  menuVolby stisk;
  //byte pauza = 250;
  if(tl_1_active && getValBtnZpet() == LOW) {
    delay(pauza);
    stisk=ZPET;
  } else if(tl_2_active && getValBtnMinus() == LOW) {
    delay(pauza);
    stisk=MINUS;
  } else if(tl_3_active && getValBtnPlus() == LOW) {
    delay(pauza);
    stisk=PLUS;
  } else if(tl_4_active && getValBtnMenu() == LOW) {
    delay(pauza);
    if (!operace[operaceId].equals("VAZENI")) {
      stisk = OK;
    } else {
      stisk = MENU;
    }
  } else {
    stisk=null;
  }
  return stisk;
}

byte indexOfOperace(String hledanaHodnota){
  byte pozice = 0;
  boolean nalezeno=false;
  for(String hodnota : operace) {
    if(hodnota==hledanaHodnota){
      nalezeno=true;
      break;
    }
    pozice++;
  }
  if(nalezeno) {
    return pozice;
  } else {
    return null;
  }
}

void vymazZahlavi() {
  TFTscreen.fillRect(0, 0, 160, 29, Display_Color_Black);
}
void vymazVahu() {
  TFTscreen.fillRect(0, 33, 160, 120, Display_Color_Black);
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
