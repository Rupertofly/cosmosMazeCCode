#include "classes.h"

MazeCtrl::MazeCtrl(Adafruit_NeoPixel* _strip) {
  Astrip = _strip;

  for (int i = 0; i < 63; i++) {
    leds[i] = new MazeLED(Astrip, i);
  }

  cells[0] = new MazeCell(leds, 10, 0);
  cells[1] = new MazeCell(leds, 10, 1);
  cells[62] = new MazeCell(leds, 10, 2);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      cells[CELL_ADR[i][j]] = new MazeCell(leds, i, j);
    }
  }

  cells[0]->isActive = true;
  cells[0]->update();
  cells[1]->isActive = true;
  cells[1]->update();
  cells[62]->isActive = true;
  cells[62]->update();
}

MazeCell* MazeCtrl::getCell(byte _rAdr, byte _dAdr) {
  return cells[CELL_ADR[_rAdr][_dAdr]];
}

void MazeCtrl::updateIn(byte adr, bool val) {
  cells[adr]->isActive = val == 1;
  cells[adr]->update();
}
void MazeCtrl::updateIn(MazeCell* cell, bool val) {
  cell->isActive = val == 1;
  cell->update();
}
void MazeCtrl::updateIn(byte in[10][6]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      updateIn(getCell(i, j), in[i][j]);
    }
  }
}

MazeCell::MazeCell(MazeLED* _LEDArr[63], byte _rAdr, byte _dAdr) {
  led = _LEDArr[CELL_ADR[_rAdr][_dAdr]];
  rAdr = _rAdr;
  dAdr = _dAdr;
  adr = CELL_ADR[_rAdr][_dAdr];
  isAccessable = false;
  isActive = false;
  isPath = false;
}
void MazeCell::update() {
  led->isActive = isActive;
  led->isAccessable = isAccessable;
  led->isPath = isPath;
  led->update();
}
MazeLED::MazeLED(Adafruit_NeoPixel* _strip, byte _adr) {
  Astrip = _strip;
  adr = _adr;
  isAccessable = false;
  isActive = false;
  isPath = false;
}
void MazeLED::update() {
  int vals[4] = {0, 0, 0, 0};
  if (isActive) {
    vals[3] = 64;
  } else {
    vals[3] = 0;
  }
  if (isPath && isActive)
    vals[1] = 128;
  else
    vals[1] = 0;
  if (isAccessable && isActive)
    vals[2] = 128;
  else
    vals[2] = 0;
  if (!isActive)
    vals[0] = 16;
  strip.setPixelColor(adr, vals[0], vals[1], vals[2], vals[3]);
}
void MazeCtrl::updateAll() {
  for (int i = 0; i < 63; i++) {
    cells[i]->update();
  }
}
bool MyQueue::isEmpty() {
  return itemCount == 0;
}
void MyQueue::enqueue(int data) {
  if (rear == 128 - 1)
    rear = -1;
  myArray[++rear] = data;
  itemCount++;
}
int MyQueue::dequeue() {
  int data = myArray[front++];
  if (front == 128) {
    front = 0;
  }
  itemCount--;
  return data;
}
void MazeCtrl::calculatePath() {
  // Serial.println("bq");
  delay(50);
  MyQueue MazeQueue = MyQueue();
  byte visited[63];
  MazeQueue.enqueue(0);
  // Serial.println("start");
  for (byte i = 0; i < 63; i++) {
    visited[i] = 99;
    //   cells[i]->isAccessable = false;
    //   cells[i]->isPath = false;
    //   cells[i]->update();
  }
  bool freeze = false;
  // Serial.print(MazeQueue.itemCount);
  delay(20);
  byte moves = 0;
  // while (MazeQueue.itemCount > 0) {
  //   moves++;
  //   if (moves > 5)
  //     break;
  //   int c = MazeQueue.dequeue();
  //   if (c == 99) {
  //     continue;
  //   }
  //   int u = neighbours[c][0];
  //   int d = neighbours[c][3];
  //   int r = neighbours[c][1];
  //   int l = neighbours[c][2];
  //   if (u != 99) {
  //     if (visited[u] == 99) {
  //       MazeQueue.enqueue(u);
  //       visited[u] = c;
  //     }
  //   }
  //   if (d != 99) {
  //     if (visited[d] == 99) {
  //       MazeQueue.enqueue(d);
  //       visited[d] = c;
  //     }
  //   }
  //   if (r != 99) {
  //     if (visited[r] == 99) {
  //       MazeQueue.enqueue(r);
  //       visited[r] = c;
  //     }
  //   }
  //   if (l != 99) {
  //     if (visited[l] == 99) {
  //       MazeQueue.enqueue(l);
  //       visited[l] = c;
  //     }
  //   }
  //   moves++;
  // }

  // cells[c]->isAccessable = true;
  // cells[c]->update();
  // cells[c]->isAccessable = true;
  // for (int j = 0; j < 4; j++) {
  //   int n = neighbours[c][j];
  //   if (n == 99) {
  //     continue;
  //   }
  //   //Serial.println("I'm here");
  //   if (visited[n] == 99) {
  //     // MazeQueue.enqueue(n);
  //     visited[n] = c;
  //     break;
  //   }
  // }
}
// if (isSolvable) {
//   bool loo = true;
//   int thisCell = 62;
//   while (loo) {
//     if (thisCell == 0)
//       loo = false;
//     MazeCell* tC = cells[62];
//     tC->isPath = true;
//     int temp = visited[thisCell];
//     thisCell = temp;
//   }
// }