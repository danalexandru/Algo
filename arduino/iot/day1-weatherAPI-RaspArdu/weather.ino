
// Sharp distance sensor
int redpin = 0;
int i;
int val;

void setup (){
  pinMode(redpin,OUTPUT);
  Serial.begin(9600);
}

void loop (){
  i = analogRead(redpin);
  val = (6762/(i-9))-4;
  Serial.println(val);
  
  delay(1000);
}
