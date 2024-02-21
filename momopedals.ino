
#include "MegaJoy.h"

const int analogPinGas = A0;

const int analogPinBrake = A1;
int valueGas;      //variables to store analog raw reads
int valueBrake;    
int valueCombined;    //variable to compose the combined pedal
int valueAxis;
int minVal = 500;
int maxVal = 1400;

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins

}

megaJoyControllerData_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins

  controllerData.analogAxisArray[3] = valueAxis;

  
  // And return the data!
  return controllerData;
}

void setup(){
  setupPins();
  setupMegaJoy();
}

void loop(){
  valueGas = analogRead(analogPinGas);          //Read analog raws
   valueBrake = analogRead(analogPinBrake);
   valueCombined = -valueGas-valueBrake;           //Combine axis


  valueCombined = -valueCombined;
  if (valueCombined < minVal) {minVal = valueCombined;}
  if (valueCombined > maxVal) {maxVal = valueCombined;}
  valueAxis = map(valueCombined, minVal, maxVal, 0, 1023);
  //Serial.println(valueAxis);
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);
}

