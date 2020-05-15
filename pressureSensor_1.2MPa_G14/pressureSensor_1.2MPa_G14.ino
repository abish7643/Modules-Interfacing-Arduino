#include <LiquidCrystal.h>
#define sensorPin A1
#define valvePin 1
int analogOutputRange[2] = {0, 1023};
int sensorReading;
const int rs = 12, en = 11; // 16*2 LCD Display | RS - 42, Enable - 44, Data - 5, 4, 3, 2 (R/W - GND)
LiquidCrystal lcd(rs, en, 5, 4, 3, 2);

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); //Use an LED to Check ValveLogic
  pinMode(valvePin, OUTPUT);
  //Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

}

void loop() {
  sensorReading = analogRead(sensorPin); //Values from 0 to 1023
  calculatePascal(sensorReading);
  delay(500);
}

void calculatePascal(float reading){
  //Assuming VCC and Vout in scale of 0 to 1
  float actualPascalOutput = ((reading/analogOutputRange[1]) - 0.1)/0.75;
  float  covertedPsiOutput = pascalToPsiCoversion(actualPascalOutput);
  //if(actualPascalOutput <=0){
  //  actualPascalOutput = 0;  
  //}
  checkExecuteValve(actualPascalOutput, covertedPsiOutput);
  printPressure(actualPascalOutput, covertedPsiOutput);
}

float pascalToPsiCoversion(float pascal){
  return pascal * 145.037738; //1MPa = 145.037738Psi
}


void printPressure(float pascal, float psi){
  //Serial.print(pascal);
  //Serial.print("MPa ");
  //Serial.print(psi);
  //Serial.print("Psi");
  //Serial.println("");
  lcd.setCursor(0, 0);
  lcd.print(pascal);
  lcd.print(" MPa");
  lcd.setCursor(1, 0);
  lcd.print(psi);
  lcd.print(" Psi");
}

void checkExecuteValve(float pascal, float psi){
  if (pascal <= 0.0233){
    digitalWrite(valvePin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println("Turned On Valve");
    lcd.setCursor(1, 0);
    lcd.print("Turned On Valve");
    delay(2000);
    lcd.clear();
  }
  if (pascal >= 0.0333){
    digitalWrite(valvePin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.println("Turned Off Valve");
    lcd.setCursor(1, 0);
    lcd.print("Turned Off Valve");
    delay(2000);
    lcd.clear();
  }
}
