/*

  update servo movement with something like this:
    for(pos = 45; pos <= 135; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 135; pos>=45; pos-=10)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  
*/
//servo

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position 

//dc motors
#define SERVO 11
#define BIN2 10
#define BIN1 9
#define TRIGGER 8
#define ECHO 7
#define AIN2 6
#define AIN1 5

//sonar
#define trigPin 8
#define echoPin 7
#define led 13

void setup() {
  //servo
 myservo.attach(11);  // attaches the servo on pin 9 to the servo object 

  //dc motors
 pinMode(BIN1, OUTPUT);
 pinMode(BIN2, OUTPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT); 

  //sonar
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void forward(){
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 0); 
}

void stall(){
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 0);
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 0); 
}

void back(){//ok ?
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 1);
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 1); 
}

int pulse(){
   long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return distance;
}

void loop() {
   myservo.write(90);

   long distance;
   distance = pulse();

  
  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
     stall();
     
     myservo.write(135); //check right
     distance = pulse();
     
     if(distance < 4){
       myservo.write(45); //checks left
       distance = pulse();
       
       if(distance < 4){
        Serial.println("obstacles front");
        //back();
        stall();
       }
       else{
         //turn left, if you have chassis
         Serial.println("turn left");
         digitalWrite(led,LOW);
        //forward(); //turn left - future
       }
     }
     else{ 
        //turn right, if you have chassis
        Serial.println("turn right");
        digitalWrite(led,LOW);
        //forward(); //turn right - future
     }
  }
  else {
    digitalWrite(led,LOW);
    forward();
  }
  
  if (distance >= 100000 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(200);

}
