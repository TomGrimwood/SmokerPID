#include <Arduino.h>
#include <ArdGuino.hpp>

MenuEntry tempDir("Temp Values");

MenuEntry s_tempDir1("M_PROBE TEMP");
MenuEntry s_tempDir2("S_PROBE TEMP");

MenuEntry confDir("Configuration");

MenuEntry s_confDir1("M_PROBE PIN");
MenuEntry s_confDir2("S_PROBE PIN");

MenuEntry pwmDir("PWM Settings");

MenuEntry s_pwmDir1("PWM PIN");

MenuEntry pidDir("PID Settings");

MenuEntry s_pidDir1("P Value");
MenuEntry s_pidDir2("I Value");
MenuEntry s_pidDir3("D Value");

MenuEntry rootDir("Root");

Runner test(&rootDir);

bool flip;

void setup()
{
  noInterrupts();
  Serial.begin(9600);
  test.lcd.begin(16, 2);

  //TIMER 1
  TCCR1A = 0;                            //ALL OFF
  TCCR1B |= (1 << CS12);                 //Set clock prescaler to 256
  TCCR1B &= ~(1 << CS11) & ~(1 << CS10); //set clock prescaler to 256
  //TCNT1 = 3036;                          //set clock to 3036 (2^16-3036)/(16*10^10/256) = 1
  //OCR1A = 0;                             //intitial trigger value = 0
  TIMSK1 |= (1 << TOIE1); //set what to do when reaching trigger Max

  tempDir.addSub(&s_tempDir1);
  tempDir.addSub(&s_tempDir2);

  confDir.addSub(&s_confDir1);
  confDir.addSub(&s_confDir2);

  pwmDir.addSub(&s_pwmDir1);

  pidDir.addSub(&s_pidDir1);
  pidDir.addSub(&s_pidDir2);
  pidDir.addSub(&s_pidDir3);

  rootDir.addSub(&tempDir);
  rootDir.addSub(&confDir);
  rootDir.addSub(&pidDir);
  rootDir.addSub(&pwmDir);

  rootDir.previous = &rootDir;


  test.dirBrowser(0);
  interrupts();
}

void loop()
{

  switch (test.waitForInput())
  {
  case DOWN:
    test.setIndex(test.incrementIndex());
    test.dirBrowser(0);
    delay(400);
    break;

  case UP:
    test.setIndex(test.decrementIndex());
    test.dirBrowser(0);
    delay(400);
    break;

  case RIGHT:
    test.theCurrent = test.theCurrent->nexts[test.theCurrent->index];
    test.setIndex(0);
    test.dirBrowser(0);
    delay(400);
    break;

  case LEFT:
    test.theCurrent = test.theCurrent->previous;
    
    test.dirBrowser(0);
    delay(400);
    break;

  default:
    break;
  }

}

ISR(TIMER1_OVF_vect) //16 bit TIMER overflow trigger 256*1/(16*10^10)*(2^16-3036) = 1
{
  if (flip)
  {
    test.lcd.setCursor(0, 0);
    test.lcd.print("-");
  }
  else
  {
    test.lcd.setCursor(0, 0);
    test.lcd.print(" ");
  }
  flip = !flip;
}