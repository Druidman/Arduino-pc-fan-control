#include <Arduino.h>
#include <ArduinoJson.h>

#define FAN_PIN 4
#define LED_PIN 5
const int LED_MODES = 28;
const int default_fan_spin_time = 500;
const int default_fan_roll_time = 3*default_fan_spin_time;

int FAN_SPIN_TIME = default_fan_spin_time;
int FAN_ROLL_TIME = default_fan_roll_time;

int default_led = 0;
int CURR_LED_MODE = default_led;
enum FANSTATE {
  SPINNING,
  ROLLING,
  STOPPED
};
FANSTATE fanState = STOPPED;
unsigned long fanSpinStartTime;
unsigned long fanRollStartTime;
unsigned long fanStopStartTime;
String message;
void parseMessage();
void clickLED();
void holdLED();
void switchToLedMode(int mode);
void handleFan();
void handleSpinningFan();
void handleRollingFan();
void handleStoppedFan();
void switchFanState(FANSTATE state);

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
  JsonDocument doc;
  const char jsonData[message.length()];
  message.toCharArray(jsonData, message.length());
  DeserializationError error = deserializeJson(doc,jsonData);

  int hold = doc["HOLD"];
  int click = doc["CLICK"];
  int doubleClick = doc["DOUBLECLICK"];
  int speed = doc["SPEED"];

  int led_mode = doc["LED_MODE"];

  if (hold){
    holdLED();
  }
  else if (click){
    clickLED();
  }
  else if (doubleClick){
    clickLED();
    delay(100);
    clickLED();
  }
  else if (speed){
    switchFanState(STOPPED);
    FAN_SPIN_TIME =  default_fan_spin_time * ((float)speed/100);
    
    switchFanState(SPINNING);
  }
  else if (led_mode){
    switchToLedMode(led_mode);
  }

  
}
void clickLED(){
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
  if (CURR_LED_MODE == LED_MODES){
    CURR_LED_MODE = 0;

  }
  CURR_LED_MODE += 1;
}
void holdLED(){
  digitalWrite(LED_PIN,HIGH);
  delay(2000);
  digitalWrite(LED_PIN,LOW);
}

void switchToLedMode(int mode){
  if (mode == CURR_LED_MODE || mode > LED_MODES){
    return ;
  }
  int to_click = 0; 
  if (mode > CURR_LED_MODE){
    to_click = mode - CURR_LED_MODE;
  }
  else {
    to_click = LED_MODES - CURR_LED_MODE + mode;
  }
  for (int i = 0; i<to_click;i++){
    clickLED();
    delay(500);
  }
  
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
  if (millis() - fanSpinStartTime < FAN_SPIN_TIME){
    return ;
  }
  switchFanState(ROLLING);
}

void handleRollingFan(){
  if (millis() - fanRollStartTime < FAN_ROLL_TIME){
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
