#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Sensor 8 
#define LED 2 
#define Buzzer 4

void setup() {
pinMode(Sensor, INPUT);
pinMode(LED, OUTPUT);
pinMode(Buzzer, OUTPUT);
lcd.init();
lcd.backlight();
Serial.begin(9600);
}

void loop(){
  int motion = digitalRead(Sensor);
  lcd.setCursor(0, 0); 
  lcd.print("Motion Alarm Sysetem");

  if (motion == HIGH){
    digitalWrite(LED, HIGH);
    tone(Buzzer, 1000);
    delay(200);
    tone(Buzzer, 500);
    delay(200);
    tone(Buzzer, 1000);
    Serial.println("Motion Derected!");
    lcd.setCursor(0,1);
    lcd.print("Motion Detected!");
  }
  else {
    digitalWrite(LED, LOW);
    noTone(Buzzer);
    Serial.println("No Motion Detected!");
    lcd.setCursor(0,1);
    lcd.print("No Motion Detected!");
  }
delay(500);
}
