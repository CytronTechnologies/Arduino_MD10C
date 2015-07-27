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
  
  cli();                   	//stop interrupts

  TCCR0A = 0;  			// set entire TCCR0A and TCCR0B register to 0
  TCCR0B = 0;  				
  TIMSK0 &= ~(1<<TOIE0);  	//disable timer overflow interrupt  
  OCR0A  = 0;  			//initialize counter value to 0
  
  TCCR0A |= (1 << WGM01);	// no prescaler
  TCCR0B |= (1<<CS00);  	
  TIMSK0 |= (1 << OCIE0A);	// enable timer compare interrupt

  sei();                  	//enable interrupt

}

void loop()
{
  //DIY PWM

  digitalWrite(dir,HIGH);               //set direction of motor
  
  while(1){
   pwm_val = analogRead(pot)*0.2493;	//read and convert analog value from
                                        // from 10 bit to 8 bit
   lcd.home();                          //LCD display
   lcd.setCursor(0,0);
   lcd.print("PWM:"); 
   lcd.print(pwm_val);
   lcd.print(" ");
   lcd.setCursor(0,1);
   lcd.print("DIR:"); 
   lcd.print(digitalRead(dir));
  }

}

ISR(TIMER0_COMPA_vect){			//interrupt routine
						//PWM generation			
  if(pwm_val ==0)
    digitalWrite(diy_pwm,LOW);

  else{
  count++;
  
  if(count==255){  
    digitalWrite(diy_pwm,HIGH);
    count = -1;
  }
  
  else if(count==pwm_val)
    digitalWrite(diy_pwm,LOW);
    
  }
  
}

