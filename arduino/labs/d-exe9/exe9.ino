
const int button1Pin = 2;     // the number of the pushbutton pin
const int button2Pin = 3;     // the number of the pushbutton pin
const int button3Pin = 4;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status
int button3State = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
   
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);


  if (button1State == HIGH){
    Serial.println("1");
    
    delay(100);
  } else if(button2State == HIGH){
    Serial.println("2");
    
    delay(100);
  } else if(button3State == HIGH){
    Serial.println("3");
    
    delay(100);
  }
  // wait for new window to open:
  delay(1000);
  
}
