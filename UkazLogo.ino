//#include <Fonts/FreeSerif9pt7b.h>
//#include <Fonts/FreeSerifBold12pt7b.h>
//#include <Fonts/FreeSerifBold18pt7b.h>

void showLogo() {
  //Serial.println("Zobrazeni loga .....");
  TFTscreen.fillRect(0, 0, 160, 128, Display_Color_Black);
  TFTscreen.setTextColor(Display_Backround_Color);
  TFTscreen.setCursor(0, 0);
  TFTscreen.fillRect(0, 10, 110, 30, Display_Color_Blue);
  TFTscreen.setTextSize(1);

  //TFTscreen.setFont(&FreeSerifBold18pt7b);
  TFTscreen.setTextColor(Display_Color_White);
  TFTscreen.setCursor(10, 35);
  TFTscreen.print("indigo");

  //TFTscreen.setFont(&FreeSerifBold12pt7b);
  TFTscreen.setTextColor(Display_Color_Blue);
  TFTscreen.setCursor(110, 35);
  TFTscreen.print("NET");

  TFTscreen.setCursor(5, 60);
  TFTscreen.setTextColor(Display_Color_White);
  //TFTscreen.setFont(&FreeSerif9pt7b);
  TFTscreen.print("IndigoNet spol. s.r.o.");
  
  TFTscreen.setCursor(30, 80);
  TFTscreen.setTextColor(Display_Color_White);
  //TFTscreen.setFont(&FreeSerif9pt7b);
  TFTscreen.print("Petr Vajner\n tel: 603 715 413");

  TFTscreen.setFont();
  TFTscreen.fillRect(0, 0, 160, 128, Display_Color_Black);
}