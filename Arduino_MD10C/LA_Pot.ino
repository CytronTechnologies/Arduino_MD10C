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
  //Control motor with potentiometer

int localKey;                          //initialization
int pwm_value;
int reading = 0;				
int prev_reading = 0;
int output = 0;

lcd.setCursor(0,0);			//LCD display on beginning
lcd.print("PWM:");
lcd.print(digitalRead(pwm));
lcd.setCursor(0,1);
lcd.print("DIR:");
lcd.print(output);

while(1){
   localKey = keypad.getKey();

    reading = 0;                    			//get average five consecutive analog readings
    for(int i =0;i<5;i++)				//from A1 pin (pot)
    reading += analogRead(pot);

    reading/=5;
  
    output=reading*0.2493;           //convert from range 1024 to 256
    
  if(reading!=prev_reading){        //update LCD data if only the reading changes
    lcd.print("       ");		//prevent reading on LCD blinking
    lcd.setCursor(0,0);
    lcd.print(“PWM: “);
    lcd.print(digitalRead(pwm));
    lcd.setCursor(0,1);
    lcd.print("DIR:");
    lcd.print(output);
    
    prev_reading = reading;
 }
    
    analogWrite(dir,output);
}
}

