/** Sharp distance sensor
alternative: https://playground.arduino.cc/Main/SharpIR
**/

//wpin - sensor pin
int wpin = 0;
int i;
int val;

void setup (){
  pinMode(wpin,OUTPUT);
  Serial.begin(9600);
}

void loop (){
  i = analogRead(wpin);

  //some formula for distance in cm
  val = (6762/(i-9))-4;
  Serial.println(val);
  
  //delay should be maintained such that the serial will not be blocked
  //otherwise, arduino would continously send data and raspberry would get blocked
  delay(1000);
}
