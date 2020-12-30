#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define PIN_A 2
#define PIN_B 3
#define SWITCH 4

LiquidCrystal_I2C lcd(0x27, 20, 4);

int previousPinAState;
int counter = 0;
bool clockwise = true;
bool rotated = false;

void setup()
{
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(SWITCH, INPUT);

  previousPinAState = digitalRead(PIN_A);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("** Rotary Encoder **");

  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.setCursor(6, 1);
  lcd.print("B: ");
  lcd.setCursor(12, 1);
  lcd.print("SW: ");

  lcd.setCursor(0, 2);
  lcd.print("Direction: ");

  lcd.setCursor(0, 3);
  lcd.print("Counter: ");
}

void loop()
{
  int aState = digitalRead(PIN_A);
  int bState = digitalRead(PIN_B);
  int switchState = digitalRead(SWITCH);

  rotated = aState != previousPinAState;

  lcd.setCursor(2, 1);
  if (aState == HIGH)
  {
    lcd.print(" ON");
  }
  else
  {
    lcd.print("OFF");
  }

  lcd.setCursor(8, 1);
  if (bState == HIGH)
  {
    lcd.print(" ON");
  }
  else
  {
    lcd.print("OFF");
  }

  lcd.setCursor(15, 1);
  if (switchState == LOW)
  {
    lcd.print(" ON");
  }
  else
  {
    lcd.print("OFF");
  }

  if (rotated)
  {
      lcd.setCursor(11, 2);
    if (bState != aState){
      lcd.print("Clockwise");
      counter++;
    } else {
      lcd.print("Counter  ");
      counter--;
    }

    lcd.setCursor(9, 3);
    lcd.print(counter);
    lcd.print("     ");
  }
}
