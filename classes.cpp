#include "classes.h"

MazeCtrl::MazeCtrl(Adafruit_NeoPixel *_strip) {
  strip = _strip;

  for (byte i = 0; i < 63; i++) {
    leds[i] = new MazeLED(_strip, i);
  }

  for (int i = 0; i < 63; i++) {
    cells[i] = new MazeCell(leds, floor(i / 3), i % 3);
  }
}

MazeCell *MazeCtrl::getCell(byte _rAdr, byte _dAdr) {
  return cells[CELL_ADR[_rAdr][_dAdr]];
}

void MazeCtrl::calculateNeighbours() {

  for (int i = 0; i < 11; i++) {

    for (int j = 0; j < 6; j++) {
      if (i == 10 && (j > 3))
        continue;
      MazeCell *cell = getCell(i, j);
      // outside, CW, CCW, inside

      // outside
      if (j == 0) cell->neighbours[0] = 99; 
    }
  }
}

MazeCell::MazeCell(MazeLED *_LEDArr[63], byte _rAdr, byte _dAdr) {
  led = _LEDArr[CELL_ADR[_rAdr][_dAdr]];
  rAdr = _rAdr;
  dAdr = _dAdr;
}

MazeLED::MazeLED(Adafruit_NeoPixel *_strip, byte _adr) {
  strip = _strip;
  adr = _adr;
}