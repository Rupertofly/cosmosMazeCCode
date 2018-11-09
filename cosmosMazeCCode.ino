#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "classes.h"
int count = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(63, 3, NEO_GRBW);
const int potPins[] = {A0, A1, A2, A3, A6, A8, A9, A10, A7};
const int potSwitchPin = 2;
MazeCtrl b = MazeCtrl(&strip);
extern const uint8_t gamma8[];
void setup() {
  strip.begin();
  strip.setBrightness(32);
  //Serial.begin(9600);
  delay(500);
  //Serial.println("running");
}
void loop() {
  delay(10);
  updateCells();
  strip.show();
}
String spaceIt(String _toSpace, int _digits) {
  String working = _toSpace;
  while (working.length() < _digits)
    working = "0" + working;
  return working;
}
void updateCells() {
  byte potValues[10][6];
  int startVal[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 10; i++) {
    if (i == 8) {
      digitalWrite(potSwitchPin, HIGH);
      startVal[8] = analogRead(A7);

      //Serial.println(i);
    }
    if (i == 9) {
      digitalWrite(potSwitchPin, LOW);
      startVal[9] = analogRead(A7);
      //Serial.println(i);
    }
    if (i < 8)
      startVal[i] = analogRead(potPins[i]);

    String s = String(map(startVal[i], 0, 1024, 0, 27), 3);
    if (s.length() == 2)
      s = "0" + s;
    else if (s.length() == 1)
      s = "00" + s;
    for (byte j = 0; j < 3; j++) {
      switch (s[j]) {
        case '0':
          potValues[i][j * 2] = false;
          potValues[i][(j * 2) + 1] = false;
          break;
        case '1':
          potValues[i][j * 2] = true;
          potValues[i][(j * 2) + 1] = false;
          break;
        case '2':
          potValues[i][j * 2] = true;
          potValues[i][(j * 2) + 1] = true;
          break;
        default:
          potValues[i][j * 2] = false;
          potValues[i][(j * 2) + 1] = false;
          break;
      }
    }
  }
  b.updateIn(potValues);
  strip.show();
  //Serial.println(b.cells[32]->isActive);
  //Serial.println("LED");
  //Serial.println(b.cells[32]->led->isActive);
  delay(100);

  // Serial.print("[ ");
  // for (int k = 0; k < 10; k++) {
  //   Serial.print("{");
  //   for (int l = 0; l < 6; l++) {
  //     Serial.print(String(potValues[k][l]) + ",");
  //   }
  //   Serial.print("}");
  // }
  // Serial.println(" ]");
  b.calculatePath();
  delay(50);
}