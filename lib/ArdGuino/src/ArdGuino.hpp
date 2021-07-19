/*
  ArdGuino.h - library for creating a GUI for 16x2 LCD.
  Created by Tom Grimwood June 2021.
*/
#ifndef ArdGuino_h
#define ArdGuino_h

#include "Arduino.h"
#include <LiquidCrystal.h>

#define SELECT 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define NEUTRAL 5
// #define SELECT_STR "Select"
// #define LEFT_STR "Left"
// #define DOWN_STR "Down"
// #define UP_STR "Up"
// #define RIGHT_STR "Right"
// #define NEUTRAL_STR "Neutral"
#define CALIBRATE 1

// struct node {
//   String name;
//   node *next[];
// };

class MenuEntry
{
public:
  
  MenuEntry(String name = "Unitialised");
  void addSub(MenuEntry *directory);
  String getOutputStr();
  int index = 0;
  int numberOfEntries = 0;
  MenuEntry *nexts[5];
  MenuEntry *previous;

private:
  String _name;
};

class MenuTree
{

  MenuTree(MenuEntry root);
};

 class Runner
{
  public:
    LiquidCrystal lcd;
    
    struct buttonID
  {
    int analogValue;
    String buttonName;
  };


  Runner();
  Runner(MenuEntry *root);
  void init();
  void runMenu();
  void dirBrowser(int input);
  void calibrate();
  void drawScreen();
  int incrementIndex();
  int decrementIndex();
  void setIndex(int input);
  int waitForInput();

  buttonID buttonIDList[6];
  int readPin = A0;
  MenuEntry *theRoot;
  MenuEntry *theCurrent;

};

class ProbeEntry : public MenuEntry
{

};
#endif