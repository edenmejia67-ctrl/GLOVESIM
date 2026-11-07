// Sign Language Glove - fixed version
// Nano: A0-A3 flex (with 10k to GND), A4/A5 I2C LCD, D3 TX -> VC-02 RX via 1k/2k divider, D13 LED
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial vc(2, 3);                 // RX, TX
const int TH[4] = {150, 200, 150, 130};  // same thresholds as the original
const char* WORD[4] = {"WASHROOM", "DRINK WATER", "FOOD", "FRUIT"};
LiquidCrystal_I2C* lcd;
int shown = -2, cand = -2;
byte stable = 0;
unsigned long last = 0;

byte findLcd() {                         // auto-detect 0x27 or 0x3F
  byte a[2] = {0x27, 0x3F};
  for (byte i = 0; i < 2; i++) {
    Wire.beginTransmission(a[i]);
    if (Wire.endTransmission() == 0) return a[i];
  }
  return 0x27;
}
void show(const char* t) {
  lcd->setCursor(0, 1);
  lcd->print("                ");
  lcd->setCursor((16 - strlen(t)) / 2, 1);
  lcd->print(t);
}
void setup() {
  Serial.begin(9600);
  vc.begin(9600);
  Wire.begin();
  lcd = new LiquidCrystal_I2C(findLcd(), 16, 2);
  lcd->init();
  lcd->backlight();
  lcd->setCursor(1, 0);
  lcd->print("SIGN LANGUAGE");
  pinMode(13, OUTPUT);
  show("READY");
}
void loop() {
  if (millis() - last < 50) return;      // no delay(): never blocks
  last = millis();
  int p = -1;
  for (int i = 0; i < 4; i++) if (analogRead(A0 + i) < TH[i]) { p = i; break; }
  if (p == cand) { if (stable < 255) stable++; } else { cand = p; stable = 0; }
  if (stable == 3 && p != shown) {       // stable for 150 ms
    shown = p;
    digitalWrite(13, p >= 0);
    if (p >= 0) { show(WORD[p]); vc.write('1' + p); Serial.println(WORD[p]); }
    else show("READY");
  }
}
