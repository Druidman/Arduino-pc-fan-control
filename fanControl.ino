#include <Arduino.h>

#define FAN_PIN 4
#define LED_PIN 5

const int FAN_SPIN_TIME = 500;
const int FAN_ROLL_TIME = 1500;

enum FANSTATE {
  SPINNING,
  ROLLING,
  STOPPED
};
FANSTATE fanState = STOPPED;
int fanSpinStartTime;
int fanRollStartTime;
int fanStopStartTime;
String message;

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN,OUTPUT);
  pinMode(LED_PIN,OUTPUT);
  handleStoppedFan();
}

void loop() {
  handleFan();
  String receivedByte;
  if (Serial.available() > 0){
    receivedByte = String((char)Serial.read());
    if (receivedByte != "/"){
      message += receivedByte;
    }
  }
  
  if (receivedByte == "/"){
    parseMessage();
    message = "";
  }
}

void parseMessage(){
  if (message == "HOLD"){
      holdLED();
  }
  else if (message == "CLICK"){
    clickLED();
  }
  else if (message == "DOUBLECLICK"){
    clickLED();
    delay(100);
    clickLED();
  }
}
void clickLED(){
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
}
void holdLED(){
  digitalWrite(LED_PIN,HIGH);
  delay(2000);
  digitalWrite(LED_PIN,LOW);
}

void handleFan(){
  switch (fanState){
    case SPINNING:
      handleSpinningFan();
      break;
    case ROLLING:
      handleRollingFan();
      break;
    case STOPPED:
      handleStoppedFan();
      break;
  }
}

void handleSpinningFan(){
  if (millis() < fanSpinStartTime + FAN_SPIN_TIME){
    return ;
  }
  switchFanState(ROLLING);
}

void handleRollingFan(){
  if (millis() < fanRollStartTime + FAN_ROLL_TIME){
    return ;
  }
  switchFanState(SPINNING);
}

void handleStoppedFan(){
  switchFanState(SPINNING);
  return ;
}

void switchFanState(FANSTATE state){
  fanState = state;
  switch (fanState){
    case SPINNING:
      digitalWrite(FAN_PIN,HIGH);
      fanSpinStartTime = millis();
      break;
    case ROLLING:
      digitalWrite(FAN_PIN,LOW);
      fanRollStartTime = millis();
      break;
    case STOPPED:
      digitalWrite(FAN_PIN,LOW);
      fanStopStartTime = millis();
      break;
  }
}