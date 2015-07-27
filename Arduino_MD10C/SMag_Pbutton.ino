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
  //SIGN MAGNITUDE MODE  
  //Controlling motor speed with push button
   
   int localKey;                        //initialize
   int pwm_value;
   
  while(1)
  {
   localKey = keypad.getKey();		//scanning for which button on keypad shield being pressed
   
   if(localKey==Left){			//toggle motor direction if LEFT button pressed
     digitalWrite(dir,!digitalRead(dir));
     delay(200);}

   if(localKey==Up){			//increase motor speed if UP button pressed
     pwm_value++;
     delay(200);
     lcd.clear();}
   
   else if(localKey==Down){		//decrease motor speed if DOWN button pressed
     pwm_value--;
     delay(200);
     lcd.clear();}
   
   if(pwm_value>255)			//ensure speed limit as PWM value ranges from 0 to 255
     pwm_value= 255; 
   else if(pwm_value<0)
     pwm_value= 0;
   
   analogWrite(pwm,pwm_value);
   
   lcd.setCursor(0,0);			//LCD display
   lcd.print("PWM:");
   lcd.print(pwm_value);
   lcd.setCursor(0,1);
   lcd.print("DIR:");
   lcd.print(digitalRead(dir));
  }
}

