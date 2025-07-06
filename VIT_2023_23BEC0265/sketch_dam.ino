#include <Servo.h>  		//library servo
#include <LiquidCrystal.h>	//library LCD
const int trig = 2, echo = 3; 
int z; 
int red = A0, orange = A1, yellow = A2, green = A3;	 // Red, Orange, Yellow and Green LEDs connected to pins A0, A1, A2 and A3, respectively
int buzzer = 7; 
int duration, Distanceincm; 
Servo myservo;	// variable to store the data position
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);	
void setup() {
  lcd.begin(16, 2);	 //16 = Column, 2 = Line
  pinMode(trig, OUTPUT); //set the mode of the trig as OUTPUT
  pinMode(echo, INPUT);	 //set the mode of the echo as INPUT
  pinMode(red, OUTPUT);	 //set the mode from red as OUTPUT
  pinMode(yellow, OUTPUT);	//set the mode from yellow as OUTPUT
  pinMode(green, OUTPUT);	//set the mode from green as OUTPUT
  pinMode(orange, OUTPUT);	//set the mode from orange as OUTPUT
  digitalWrite(green, HIGH); //makes the green variable value HIGH
  myservo.attach(4);	//servo motor cable data signal is connected to pin 4 of the Arduino
}
void loop() {
  digitalWrite(trig, HIGH);	//make the value of the trig variable HIGH
  delay(15);	//time delay of 15 ms
  digitalWrite(trig, LOW);	//make the trig variable value LOW
  duration = pulseIn(echo, HIGH);	//pulseIn totals the waiting time of echo pin - when it is high, the waiting time will be stored in memory
  Distanceincm = (duration / 58.2);	//calculations to be made as the distance from the ultrasonic to the surface of the water
  z = 335-Distanceincm; //calculation of water level
  lcd.setCursor(0, 0);	//set at column 0 and row 0
  lcd.print("Height : ");	//write down "Height : "
  lcd.print(z); //write down the calculation results of the variable z
  delay(1000); //time delay of 1 second
  if (Distanceincm > 240) {
    lcd.clear();  //to clear the LCD screen
    lcd.setCursor(0, 1);	//set on column 0 and row 1
    lcd.print("Condn : Safe"); //writes "Condn : Safe"
    digitalWrite(red, LOW);
    digitalWrite(orange, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    noTone(buzzer);	//the buzzer does not sound
    myservo.write(0); //move the servo by 0 degrees
    delay(20);	//time delay of 20 ms
  }
  if (Distanceincm > 160 && Distanceincm <= 240 ) {
    lcd.clear(); //to clear the LCD screen
    lcd.setCursor(0, 1);	//set on column 0 and row 1
    lcd.print("Condn : Low");   //writes "Condn : Low"
    digitalWrite(red, LOW);
    digitalWrite(orange, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    noTone(buzzer);	//the buzzer does not sound
    myservo.write(30);	//move the servo by 30 degrees
    delay(20);	//time delay of 20 ms
  }
  if (Distanceincm > 80 && Distanceincm <= 160) { 
    lcd.clear();  //to clear the LCD screen
    lcd.setCursor(0, 1);   //set on column 0 and row 1
    lcd.print("Condn : Medium");  //writes "Condn : Medium"
    digitalWrite(red, LOW);
    digitalWrite(orange,HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    noTone(buzzer);  //the buzzer does not sound
    myservo.write(60);	//move the servo by 60 degrees
    delay(20);	//time delay of 20 ms
  }
  if (Distanceincm > 0 && Distanceincm <= 80) {
    lcd.clear(); //to clear the LCD screen
    lcd.setCursor(0, 1);	//set on column 0 and row 1
    lcd.print("Condn : DANGER!!");   //writes "Condn : DANGER!!"
    digitalWrite(red, HIGH);
    digitalWrite(orange,LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    buzz(); //go to label 'buzz' function to sound the buzzer
    myservo.write(90);	//move the servo by 90 degrees
    delay(20);	//time delay of 20 ms
  }
}
void buzz(){
  tone(buzzer,1000,500); //buzzer sound setting with a freq. 1000 Hz and a long time 500 ms
  delay(300);	//time delay of 300 ms
}

