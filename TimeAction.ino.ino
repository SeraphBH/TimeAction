#include <TimedAction.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
int valeurLue = 0;
float tension;


void blink();
void lheur();
void potar();
 
//this initializes a TimedAction class that will change the state of an LED every second.


TimedAction timedled = TimedAction(100,blink);
TimedAction timedheur = TimedAction(100,lheur);
TimedAction timedpotar = TimedAction(100,potar);

//pin pour led
#define ledPin 10
boolean ledState = false;

// pin pour LCD
RTC_DS1307 RTC;
LiquidCrystal lcd(15, 14, 7, 6, 5, 4);


 
 
void setup(){
  //setup pour led
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);
  //setup pour LCD
  Wire.begin();
  RTC.begin();
  lcd.begin(16, 2);
  //RTC.adjust(DateTime(__DATE__, __TIME__)); 
}
 
void loop(){
  timedled.check();
  timedheur.check();
  timedpotar.check();
}
 
void blink(){
  ledState ? ledState=false : ledState=true;
  digitalWrite(ledPin,ledState);
}

void potar(){
  
  // Voltage Pin A2
  lcd.setCursor(9, 0);
  valeurLue = analogRead(2);
  tension = valeurLue * 5.0 / 1023;
  lcd.print(" "); 
  lcd.print(tension);
  lcd.print("V");
  
}

void lheur() {
  DateTime now = RTC.now();
   
  // l'heure sur la premiêre ligne du LCD
  lcd.setCursor(0, 0);
  if (now.hour() < 10 ) { lcd.print(0); }
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second());
  

  
  // la date sur la deuxième ligne du LCD
  lcd.setCursor(0, 1); 
  lcd.print(now.day()); 
  lcd.print(" "); 

  switch (now.month()) {
  case 1:
    lcd.print("janvier");
    break;
  case 2:
    lcd.print("fevrier");
    break;
  case 3:
    lcd.print("mars");
    break;
  case 4:
    lcd.print("avril");
    break;
  case 5:
    lcd.print("mai");
    break;
  case 6:
    lcd.print("juin");
    break;
  case 7:
    lcd.print("juillet");
    break;
  case 8:
    lcd.print("aout");
    break;
  case 9:
    lcd.print("septembre");
    break;
  case 10:
    lcd.print("octobre");
    break;
  case 11:
    lcd.print("novembre");
    break;
  case 12:
    lcd.print("decembre");
    break;
  }
  lcd.print(" "); 
  lcd.print(now.year()); 
  delay(100);
  //lcd.clear();

}
