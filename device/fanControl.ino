#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>

#define FAN_PIN 4
#define CASE_LED_PIN 5
#define AIO_LED_PIN 8
#define AIO_NUM_LEDS 34
const int CASE_FAN_MODES = 28;
const int default_fan_spin_time = 500;
const int default_fan_roll_time = 3*default_fan_spin_time;

int FAN_SPIN_TIME = default_fan_spin_time;
int FAN_ROLL_TIME = default_fan_roll_time;

int default_led = 0;
int CURR_CASE_FAN_LED_MODE = default_led;

CRGB aio_leds[AIO_NUM_LEDS];

CRGB aio_color = {0,0,0};

CRGB aio_last_color;
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

void changeAioColor(String aio_rgb);
void changeAioLedsToColor(CRGB color);

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN,OUTPUT);
  pinMode(CASE_LED_PIN,OUTPUT);
  handleStoppedFan();

  FastLED.addLeds<NEOPIXEL, AIO_LED_PIN> (aio_leds,AIO_NUM_LEDS);
  
  
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
  char jsonData[message.length()];
  message.toCharArray(jsonData, message.length());
  DeserializationError error = deserializeJson(doc,jsonData);

  int hold = doc["HOLD"];
  int click = doc["CLICK"];
  int doubleClick = doc["DOUBLECLICK"];
  int speed = doc["SPEED"];

  int case_fan_led_mode = doc["CASE_FAN_LED_MODE"];
  JsonObject aio_rgb = doc["AIO_RGB"];

  if (hold){
    if (aio_color.r == 0 && aio_color.g == 0 && aio_color.b ==0){
      changeAioLedsToColor(aio_last_color);
    }
    else{
      changeAioLedsToColor({0,0,0});
    }
    holdLED();
  
  }
  if (click){
    clickLED();

  }
  if (doubleClick){
    clickLED();
    delay(100);
    clickLED();

  }
  if (speed){
    switchFanState(STOPPED);
    FAN_SPIN_TIME =  default_fan_spin_time * ((float)speed/100);
    
    switchFanState(SPINNING);
    
  }
  if (case_fan_led_mode){
    switchToLedMode(case_fan_led_mode);
    
    
  }
  if (aio_rgb["r"]){
    changeAioColor(aio_rgb);
    
  }

  
}
void clickLED(){
  digitalWrite(CASE_LED_PIN,HIGH);
  delay(100);
  digitalWrite(CASE_LED_PIN,LOW);
  if (CURR_CASE_FAN_LED_MODE == CASE_FAN_MODES){
    CURR_CASE_FAN_LED_MODE = 0;

  }
  CURR_CASE_FAN_LED_MODE += 1;
}
void changeAioLedsToColor(CRGB color){
  
  aio_last_color.r = aio_leds[0].r;
  aio_last_color.g = aio_leds[0].g;
  aio_last_color.b = aio_leds[0].b;

  aio_color = color;


  for (int i=0; i<AIO_NUM_LEDS;i++){
    aio_leds[i] = color;
  }
  FastLED.show();
}

void changeAioColor(JsonObject aio_rgb){

  int r = aio_rgb["r"];
  int g = aio_rgb["g"];
  int b = aio_rgb["b"];
  changeAioLedsToColor({r,g,b});




}
void holdLED(){
  digitalWrite(CASE_LED_PIN,HIGH);
  delay(2000);
  digitalWrite(CASE_LED_PIN,LOW);
}

void switchToLedMode(int mode){
  if (mode == CURR_CASE_FAN_LED_MODE || mode > CASE_FAN_MODES){
    return ;
  }
  int to_click = 0; 
  if (mode > CURR_CASE_FAN_LED_MODE){
    to_click = mode - CURR_CASE_FAN_LED_MODE;
  }
  else {
    to_click = CASE_FAN_MODES - CURR_CASE_FAN_LED_MODE + mode;
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
