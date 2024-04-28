#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int timer1;
int timer2;

float Time;

int flag1 = 0;
int flag2 = 0;

float distance = 5.0;
float speed;

int ir_s1 = 1;
int ir_s2 = 1;

int buzzer = 9;
int led1 = 2;
int led2 = 3;

const int trigPin = 6;
const int echoPin = 5;
long duration;
int distance1;
int i;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position
int poss = 0;

const int trigPin1 = 8;
const int echoPin1 = 7;
long duration1;
int distance2;
int j;
int state = 0;








void setup() {
  Serial.begin(115200);
  lcd.begin();  // Initializes the interface to the LCD screen
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15 ms for the servo to reach the position
  }


  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome To  My ");
  lcd.setCursor(0, 1);
  lcd.print("YouTube  Channel");
  delay(2000);
  lcd.clear();
}





// void ul1() {

// }



// void ul2() {

// }






void loop() {



  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);


  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);


  duration1 = pulseIn(echoPin1, HIGH);




  distance = duration * 0.034 / 2.000;
  i = distance;
  distance1 = duration1 * 0.034 / 2.000;
  j = distance1;


  //Serial.print(j);
  //Serial.print(i);

  if (j <= 8) {
    ir_s1 = 0;
    Serial.print(i);
    state = 1;
  } else {
    ir_s1 = 1;
  }





  // Write a pulse to the HC-SR04 Trigger Pin


  if (i <= 8 && state == 1) {

    Serial.println(j);
    ir_s2 = 0;

  } else {
    ir_s2 = 1;
  }













  if (ir_s1 == 0 && flag1 == 0) {
    timer1 = millis();
    flag1 = 1;
  }

  if (ir_s2 == 0 && flag2 == 0) {
    timer2 = millis();
    flag2 = 1;
  }

  if (flag1 == 1 && flag2 == 1) {
    if (timer1 > timer2) {
      Time = timer1 - timer2;
    } else if (timer2 > timer1) {
      Time = timer2 - timer1;
    }
    Time = Time / 1000;         //convert millisecond to second
    speed = (distance / Time);  //v=d/t
    speed = speed * 3600;       //multiply by seconds per hr
    speed = speed / 1000;       //division by meters per Km
  }

  if (speed == 0) {
    lcd.setCursor(0, 1);
    if (flag1 == 0 && flag2 == 0) {
      lcd.print("No car  detected");
    } else {
      lcd.print("Searching...    ");
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.print(speed, 1);
    lcd.print("Km/Hr  ");
    lcd.setCursor(0, 1);



    if (speed > 50) {
      lcd.print("  Over Speeding  ");
      for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(10);           // waits 15 ms for the servo to reach the position
      }
      digitalWrite(buzzer, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    } else {
      lcd.print("  Normal Speed   ");
    }
    delay(3000);


    for (poss = 180; poss >= 0; poss -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);
      pos--;      // tell servo to go to position in variable 'pos'
      delay(15);  // waits 15 ms for the servo to reach the position
    }

    digitalWrite(buzzer, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);



    speed = 0;
    flag1 = 0;
    flag2 = 0;
    Time = 0;
    timer1 = 0;
    timer2 = 0;
    state = 0;
  }
}
