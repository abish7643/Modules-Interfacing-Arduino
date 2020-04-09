// include the library code:
#include <LiquidCrystal.h>

// Associating any needed LCD interface pin to arduino pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//GasPin
const int gasPin=A0;

void setup() {
  pinMode(gasPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
}

void loop() {
  int gaspin = analogRead(gasPin);
  Serial.println(gaspin); //toSeriallyReadFromPi
  if (gaspin >= 195){
    lcd.setCursor(0, 0);
    lcd.print("Smoke Detected");
    lcd.setCursor(0, 1);
    lcd.print(gaspin);
    }
  else{
    lcd.setCursor(0, 0);
    lcd.print("Normal");
    lcd.setCursor(0, 1);
    lcd.print(gaspin);
    }
  delay(1000);
}
