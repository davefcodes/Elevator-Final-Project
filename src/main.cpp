#include <Stepper.h>
#include <Arduino.h>
//#include <LibPrintf.h>

#define STEPPER_PIN_1 10
#define STEPPER_PIN_2 11
#define STEPPER_PIN_3 12
#define STEPPER_PIN_4 13

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3

#define SWITCH_PIN_1 6
#define SWITCH_PIN_2 7

const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
bool isElevatorRising = false;
bool isElevatorLowering = false;
void setup()
{
  // Set the pins for the buttons as inputs
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);

  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("Setting Speed 0");
  myStepper.setSpeed(10);
  Serial.println("Setup Complete");
  delay(500);
 
  // while(!digitalRead(SWITCH_PIN_2))
  // {
  //   myStepper.step(1);
  // }
  //   myStepper.step(3*-stepsPerRevolution);
 }


void loop()
{
  // Read the state of the buttons
  bool lowerElevator = !digitalRead(BUTTON_PIN_1); //clockwise to lower elevator 
  bool raiseElevator = !digitalRead(BUTTON_PIN_2); //counterclockwise to raise elevator 

  bool upperMicroswitch = digitalRead(SWITCH_PIN_1);
  bool lowerMicroswitch = digitalRead(SWITCH_PIN_2);

  // Check if the first button is pressed
  if (lowerElevator)
  {
  isElevatorLowering = true;
  isElevatorRising = false;
  }

  // Check if the second button is pressed
  if (raiseElevator) 
  {
  isElevatorLowering = false;
  isElevatorRising = true;
  }
  
  if (isElevatorLowering && !lowerMicroswitch)
  {
    myStepper.setSpeed(10);
    myStepper.step(1);
  }
  else if (isElevatorLowering && lowerMicroswitch)
  {
    isElevatorLowering = false;
  }

  if (isElevatorRising && !upperMicroswitch)
  {
    myStepper.setSpeed(10);
    myStepper.step(-1);
  }
  else if (isElevatorRising && upperMicroswitch)
  {
    isElevatorRising = false;
  }
  if(!isElevatorRising && !isElevatorLowering)
  {
  //myStepper.setSpeed(0);
  }
}