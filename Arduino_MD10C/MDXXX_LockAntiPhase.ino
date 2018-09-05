/*
 Controlling a MD13S/MD10C/MD30C motor driver from Arduino with a potentiometer (variable resistor)
 This example is based on Locked AntiPhase method. Where the PWM signal is ejected to DIR pin of Motor driver. 
 With this example, please connect:
 
 Arduino UNO/Maker UNO        Motor Driver
 GND ------------------------ GND
 D6  ------------------------ PWM
 D5  ------------------------ DIR

 You will also need a potentiometer/variable resistor. Connect it in this way:
 Arduino UNO/Maker UNO          Potentiometer/Variable Resistor     
 5V                             One of the side pin (Right)
 A0                             Center pin
 GND                            Another side pin (Left)
 
 If you are using MD30C, please ensure the jumper at JP4 is place to EXT_PWM
 
 by Ober Choo 

MD13S: https://www.cytron.io/p-md13s
MD10C: https://www.cytron.io/p-md10c
MD30C: https://www.cytron.io/p-md30c

Check out the video:
MD13S: https://youtu.be/IXaNO6wflRk
MD10C: https://youtu.be/kA38GhkUOso
*/

int potpin = 0; // analog pin used to connect the potentiometer
int potval;     // variable to read the value from the analog pin
int tempval = 0;  //variable to keep adc value after mapping
int PWM = 6 ;   // PWM of Motor driver connect to D6
int DIR = 5;    // DIR of Motor driver connect to D5

void setup() {
  pinMode(potpin, INPUT);
  pinMode(PWM, OUTPUT); //PWM output
  digitalWrite(PWM,LOW);  //ensure the PWM is LOW at initial stage
  pinMode(DIR, OUTPUT); //DIR output
  digitalWrite(DIR, LOW); //ensure the DIR is LOW at initial stage  
}

void loop() {
  potval = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  digitalWrite(PWM, HIGH);                //Enable the motor driver
  // Locked Antiphase method, uses DIR of Motor driver to control both direction and speed of motor, this example will change the PWM output from Arduino based on potentiometer
  tempval = map(potval, 0, 1023, 0, 255); // scale the analog reading (10-bit) to PWM output(8-bit)
  analogWrite(DIR, tempval);              // Output the PWM signal at DIR pin
  delay(15);                              // delay for a short time
}

