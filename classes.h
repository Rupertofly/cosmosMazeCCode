#include <Adafruit_NeoPixel.h>
#include <Arduino.h>




const uint8_t CELL_ADR[11][6] = {
    {2, 3, 4, 5, 6, 7},       {8, 9, 10, 11, 12, 13},
    {14, 15, 16, 17, 18, 19}, {20, 21, 22, 23, 24, 25},
    {26, 27, 28, 29, 30, 31}, {32, 33, 34, 35, 36, 37},
    {38, 39, 40, 41, 42, 43}, {44, 45, 46, 47, 48, 49},
    {50, 51, 52, 53, 54, 55}, {56, 57, 58, 59, 60, 61},
    {0, 1, 62, 99, 99, 99}};
extern Adafruit_NeoPixel strip;
class MazeLED {
 public:
  MazeLED(Adafruit_NeoPixel* _strip, byte _adr);
  Adafruit_NeoPixel* Astrip;
  byte adr;
  bool isActive;
  bool isAccessable;
  bool isPath;

  bool dirty;
  void update();
};
class MazeCell {
 public:
  MazeCell(MazeLED* _LEDArr[], byte _rAdr, byte _dAdr);
  MazeLED* led;
  byte rAdr;
  byte dAdr;
  byte adr;
  bool isActive;
  bool isAccessable;
  bool isPath;

  void update();
};
class MazeCtrl {
 public:
  MazeCtrl(Adafruit_NeoPixel* _strip);
  Adafruit_NeoPixel* Astrip;
  MazeCell* cells[63];
  MazeLED* leds[63];
  void updateIn(byte in[10][6]);
  void updateIn(MazeCell* cell, bool val);
  void updateIn(byte adr, bool val);
  void update();
  void calculateNeighbours();
  void calculatePath();
  void updateAll();
  bool isSolvable;
  byte neighbours[63][4] = {
      {99, 99, 99, 1},  {0, 2, 56, 99},   {99, 8, 1, 3},    {2, 9, 99, 4},
      {3, 10, 99, 5},   {4, 11, 99, 6},   {5, 12, 99, 7},   {6, 13, 99, 62},
      {99, 14, 2, 9},   {8, 15, 3, 10},   {9, 16, 4, 11},   {10, 17, 5, 12},
      {11, 18, 6, 13},  {12, 19, 7, 62},  {99, 20, 8, 15},  {14, 21, 9, 16},
      {15, 22, 10, 17}, {16, 23, 11, 18}, {17, 24, 12, 19}, {18, 25, 13, 62},
      {99, 26, 14, 21}, {20, 27, 15, 22}, {21, 28, 16, 23}, {22, 29, 17, 24},
      {23, 30, 18, 25}, {24, 31, 19, 62}, {99, 32, 20, 27}, {26, 33, 21, 28},
      {27, 34, 22, 29}, {28, 35, 23, 30}, {29, 36, 24, 31}, {30, 37, 25, 62},
      {99, 38, 26, 33}, {32, 39, 27, 34}, {33, 40, 28, 35}, {34, 41, 29, 36},
      {35, 42, 30, 37}, {36, 43, 31, 62}, {99, 44, 32, 39}, {38, 45, 33, 40},
      {39, 46, 34, 41}, {40, 47, 35, 42}, {41, 48, 36, 43}, {42, 49, 37, 62},
      {99, 50, 38, 45}, {44, 51, 39, 46}, {45, 52, 40, 47}, {46, 53, 41, 48},
      {47, 54, 42, 49}, {48, 55, 43, 62}, {99, 56, 44, 51}, {50, 57, 45, 52},
      {51, 58, 46, 53}, {52, 59, 47, 54}, {53, 60, 48, 55}, {54, 61, 49, 62},
      {99, 1, 50, 57},  {56, 99, 57, 58}, {57, 99, 58, 59}, {58, 99, 59, 60},
      {59, 99, 60, 61}, {60, 99, 61, 62}};

 private:
  MazeCell* getCell(byte _rAdr, byte _dAdr);
};
class MyQueue {
  public:
   int myArray[128];
   int front = 0;
   int rear = -1;
   int itemCount = 0;
   bool isEmpty();
   void enqueue(int data);
   int dequeue();
};