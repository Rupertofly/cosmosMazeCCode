#include "classes.h"

MazeCtrl::MazeCtrl(Adafruit_NeoPixel *_strip) {
  strip = _strip;

  for (byte i = 0; i < 63; i++) {
    leds[i] = new MazeLED(_strip, i);
  }

  for (int i = 0; i < 32; i++) {
    cells[i] = new MazeCell(leds, floor(i / 3), i % 3);
  }
}

MazeCell::MazeCell(MazeLED *_LEDArr[63], byte _rAdr, byte _dAdr) {
  path = _LEDArr[CELL_ADR[_rAdr][_dAdr][0]];
  wall = _LEDArr[CELL_ADR[_rAdr][_dAdr][1]];
  rAdr = _rAdr;
  dAdr = _dAdr;
}

MazeLED::MazeLED(Adafruit_NeoPixel *_strip, byte _adr) {
  strip = _strip;
  adr = _adr;
}