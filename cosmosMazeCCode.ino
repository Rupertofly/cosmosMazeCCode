#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "classes.h"
int count = 0;
auto strip = Adafruit_NeoPixel(63, 3, NEO_GRBW);
extern const uint8_t gamma8[];
void setup() {
  strip.begin();
  strip.setBrightness(32);
  strip.gamma8(9);
  Serial.begin(9600);
  auto b = MazeCtrl(&strip);
}
void loop() {

}
String spaceIt(String _toSpace, int _digits) {
  String working = _toSpace;
  while (working.length() < _digits)
    working = "0" + working;
  return working;
}