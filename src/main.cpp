#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define CLK 2
#define DT 3
#define SWITCH 4

LiquidCrystal_I2C lcd(0x27, 20, 4);

int previous;
int counter = 0;
int value;
bool clockwise = true;

void setup()
{
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SWITCH, INPUT_PULLUP);

  previous = digitalRead(CLK);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("** Rotary Encoder **");

  lcd.setCursor(0, 2);
  lcd.print("Direction: ");

  lcd.setCursor(0, 3);
  lcd.print("Counter: 0");
}

void loop() {  
  if (!digitalRead(SWITCH)) {
    counter = 0;

    lcd.setCursor(11, 2);
    lcd.print("          ");
    lcd.setCursor(9, 3);
    lcd.print("0         ");
  }

  value = digitalRead(CLK);
  if (value != previous){
    if (digitalRead(DT) != value) {
      counter++;
      clockwise = true;
    } else {
      clockwise = false;
      counter--;
    }

    lcd.setCursor(11, 2);
    if (clockwise) {
      lcd.print("Clockwise");
    } else {
      lcd.print("Counter  ");
    }

    lcd.setCursor(9, 3);
    lcd.print(counter);
    lcd.print("     ");
  }

  previous = value;
}
