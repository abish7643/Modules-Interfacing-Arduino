#define sensorPin A1
int analogOutputRange[2] = {0, 1023};
int sensorReading;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
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
  printPressure(actualPascalOutput, covertedPsiOutput);
}

float pascalToPsiCoversion(float pascal){
  return pascal * 145.037738; //1MPa = 145.037738Psi
}


void printPressure(float pascal, float psi){
  Serial.print(pascal);
  Serial.print("MPa ");
  Serial.print(psi);
  Serial.print("Psi");
  Serial.println("");}
