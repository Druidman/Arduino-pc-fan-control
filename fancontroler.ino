#define FAN_PIN 4
#define LED_PIN 5

#define LED_MODE_FULLWHITE 20
int current_led_mode = 0;

void setup() {
  pinMode(FAN_PIN,OUTPUT);
  pinMode(LED_PIN,OUTPUT);

  while(current_led_mode++ < LED_MODE_FULLWHITE) {
    digitalWrite(LED_PIN,HIGH); delay(100); 
    digitalWrite(LED_PIN,LOW); delay(310); 
  }


  digitalWrite(FAN_PIN,HIGH);
  delay(3000);
  digitalWrite(FAN_PIN,LOW);
}

int fan_poweron_milis = 300;
int fan_poweroff_milis = 900;

void loop() {
  digitalWrite(FAN_PIN,HIGH);
  delay(fan_poweron_milis);
  digitalWrite(FAN_PIN,LOW);
  delay(fan_poweroff_milis);
}
