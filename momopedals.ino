const int analogPinGas = A0;

const int analogPinBrake = A1;
int valueGas;      //variables to store analog raw reads

int valueBrake;    

 

int valueCombined;    //variable to compose the combined pedal
int valueAxis;
int minVal = 500;
int maxVal = 1400;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   valueGas = analogRead(analogPinGas);          //Read analog raws
   valueBrake = analogRead(analogPinBrake);
   valueCombined = -valueGas-valueBrake;           //Combine axis

//if (valueCombined<-990 and valueCombined>-1036){      //Dead zone
//  valueCombined=-1023;
//  }
  
  valueCombined = -valueCombined;
  if (valueCombined < minVal) {minVal = valueCombined;}
  if (valueCombined > maxVal) {maxVal = valueCombined;}
  valueAxis = map(valueCombined, minVal, maxVal, 0, 1023);
  
  Serial.print(minVal);
  Serial.print(",");
  Serial.print(maxVal);
  Serial.print(",");
  Serial.print(valueCombined);
  Serial.print(",");
  Serial.println(valueAxis); 
}
