/** 
  mapovani od 0
   0 - xxxxxxxxxxxxxxxxxxxxxxxx     - delka long  (32 bit - 4*8 byty) - pozice  0  1  2 3   - 4  volna
   4 - kalibracniHodnota            - delka float (32 bit - 4*8 byty) - pozice  5  6  7 8   - 9  volna
   8 - kalibracniZnamaVaha          - delka int   (16 bit - 2*8 byty) - pozice 10 11        - 12 volna
  13 - priznak provedene kalibrace  - delka byte  ( 8 bit - 1*8 byty) - pozice 13

*/
void setKalibracniHodnota(float kalibracniHodnota) {
  Serial.print("Zapis hodnoty do EEPROM - setKalibracniHodnota:");
  Serial.println(kalibracniHodnota);
  EEPROM.put(5, kalibracniHodnota);
  delay(100);
}

float getKalibracniHodnota() {
  Serial.print("Nacitani dat z EEPROM - getKalibracniHodnota:");
  float value;
  EEPROM.get(5, value);
  if (isnan(value)) {
    value = 0;
  }
  Serial.println(value);
  return value;
}

void setKalibracniVaha(int kalibracniHodnota) {
  Serial.print("Zapis hodnoty do EEPROM - setKalibracniVaha:");
  Serial.println(kalibracniHodnota);
  EEPROM.put(10, kalibracniHodnota);
  delay(100);
}

float getKalibracniVaha() {
  Serial.print("Nacitani dat z EEPROM - getKalibracniVaha:");
  int value;
  EEPROM.get(10, value);
  if (isnan(value)) {
    value = 0;
  }
  Serial.println(float(value));
  return float(value);
}

void setKalibrovano(boolean kalibrovano) {
  Serial.print("Zapis hodnoty do EEPROM - kalibrovano:");
  Serial.println(kalibrovano);
  EEPROM.put(13, kalibrovano);
  delay(100);
}

boolean getKalibrovano() {
  Serial.print("Nacitani dat z EEPROM - getKalibrovano:");
  int value;
  EEPROM.get(13, value);
  if (isnan(value)) {
    value = 0;
  }
  Serial.println(value);
  return value;
}
