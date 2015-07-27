#include <LiquidCrystal.h>
#include <LCD_Key.h>

//define keycode
#define None     0
#define Select   1
#define Left     2
#define Up       3
#define Down     4
#define Right    5

//define pin name
#define diy_pwm  A2
#define pwm      2
#define dir      3
#define pot      A1

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LCD_Key keypad;
byte count = 0;
int pwm_val = 0;        //global variable for DIY PWM purpose

void setup(){

  lcd.begin(16, 2);
  lcd.clear();
  
  pinMode(pwm,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(diy_pwm,OUTPUT);
  pinMode(pot,INPUT);

}

void loop()
{
  // LOCKED ANTI-PHASE MODE
  //control motor with program set
  
   int i=0;
   lcd.setCursor(0,0);
   digitalWrite(pwm,HIGH);		// always set PWM to HIGH
   
   for(i=0;i<256;i++){		// increase speed in every 0.5 sec
   analogWrite(dir,i);
   delay(500);
   lcd.clear();				//display status of motor on LCD
   lcd.setCursor(0,1);
   lcd.print("DIR:");lcd.print(i);
   lcd.setCursor(0,0);
   lcd.print("PWM:");
   lcd.print(digitalRead(pwm));

   }
   
   while(1) continue;        //continue,avoid loop;
}

