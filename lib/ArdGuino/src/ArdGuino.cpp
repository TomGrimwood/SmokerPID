/*
  ArdGuino.cpp - library for creating a GUI for 16x2 LCD.
  Created by Tom Grimwood June 2021.
*/

#include "Arduino.h"
#include "ArdGuino.hpp"

MenuEntry::MenuEntry(String name)
{

  _name = name;
}

String MenuEntry::getOutputStr()
{

  return _name;
}

void MenuEntry::addSub(MenuEntry *directory)
{
  if (numberOfEntries > 5)
  {
    return;
  }

  directory->previous = this;
  nexts[numberOfEntries] = directory;
  numberOfEntries++;
  return;
}

Runner::Runner(MenuEntry *root)
{
  theRoot = root;
  theCurrent = root;

  init();
}

Runner::Runner()
{
  init();
}

void Runner::init()
{
  buttonIDList[SELECT] = buttonID{639, "SELECT"};
  buttonIDList[UP] = buttonID{100, "UP"};
  buttonIDList[DOWN] = buttonID{255, "DOWN"};
  buttonIDList[LEFT] = buttonID{408, "LEFT"};
  buttonIDList[RIGHT] = buttonID{0, "RIGHT"};
  buttonIDList[NEUTRAL] = buttonID{1023, "NEUTRAL"};
}

void Runner::runMenu()
{
}
/*  CODE COMMENTED OUT FOR TESTING DIR BROWSER
  calibrate();

  while (1)
  {
    lcd.setCursor(0, 0);
    int input = waitForInput();
    lcd.setCursor(0, 0);
    lcd.print(&buttonIDList[input].buttonName[0]);
    lcd.print(" PRESSED     ");
  }

  */

void Runner::calibrate()
{

  buttonIDList[NEUTRAL].analogValue = analogRead(readPin);
  lcd.print("Calibrating...");
  delay(600);
  for (uint8_t i = SELECT; i < NEUTRAL; i++)
  {
    lcd.setCursor(0, 0);
    lcd.print("Press ");
    lcd.print(&buttonIDList[i].buttonName[0]);

    do
    {
      buttonIDList[i].analogValue = analogRead(readPin);

    } while (buttonIDList[i].analogValue > buttonIDList[NEUTRAL].analogValue - 10 &&
             buttonIDList[i].analogValue < buttonIDList[NEUTRAL].analogValue + 10);

    lcd.clear();
    lcd.print(&buttonIDList[i].buttonName[0]);
    lcd.print(" set to");
    lcd.setCursor(0, 1);
    lcd.print("value of ");
    lcd.print(buttonIDList[i].analogValue);
    delay(1000);

    lcd.clear();
  }
}

int Runner::waitForInput()
{

  while (1)
  {
    int input = analogRead(readPin);
    for (size_t i = 0; i < 6; i++)
    {
      if (input > buttonIDList[i].analogValue - 10 &&
          input < buttonIDList[i].analogValue + 10)
      {
        return i;
      }
    }
  }
}

void Runner::dirBrowser(int input = 0)
{
  //lcd.clear();
  lcd.setCursor(1, 0);
  //lcd.print("  ");
  lcd.print(&theCurrent->nexts[theCurrent->index]->getOutputStr()[0]);
  Serial.println(&theCurrent->nexts[theCurrent->index]->getOutputStr()[0]);
  lcd.print("          ");
  lcd.setCursor(1, 1);

  if (theCurrent->numberOfEntries > 1)
  {
    lcd.print(&theCurrent->nexts[incrementIndex()]->getOutputStr()[0]);
    Serial.println(&theCurrent->nexts[incrementIndex()]->getOutputStr()[0]);
    lcd.print("          ");
  }
  
  else
  {
    lcd.print("             ");
  }
}
void Runner::setIndex(int input)
{

  theCurrent->index = input;
}

int Runner::incrementIndex()
{

  if (theCurrent->index + 1 < theCurrent->numberOfEntries)
  {
    return theCurrent->index + 1;
  }
  else
  {
    return 0;
  }
}

int Runner::decrementIndex()

{

  if (theCurrent->index == 0)
  {
    return theCurrent->numberOfEntries - 1;
  }
  else
  {
    return theCurrent->index - 1;
  }
}

String ProbeEntry::getOutputStr()
{
  return "Inheritance";
}