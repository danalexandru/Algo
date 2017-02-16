int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;

int number = 0;

void setup()
{
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}
 
void loop()
{
  /*digitalWrite(led1, HIGH);
  
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  
  delay(1000);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  
  delay(1000);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);

  delay(1000);
  digitalWrite(led4, LOW);*/

/*
  if(number == 16){
    number = 0;
  }

  Serial.println(“led1 reading: “, byte(number)%10);
  Serial.println(“led2 reading: “, byte(number)%100);
  Serial.println(“led3 reading: “, byte(number)%1000);
  Serial.println("led4 reading: ", byte(number)%10000);

  
  digitalWrite(led1, byte(number)%10);
  digitalWrite(led2, byte(number)%100);
  digitalWrite(led3, byte(number)%1000);
  digitalWrite(led4, byte(number)%10000);

  number++;
  
  delay(1000);
  */
  int i1,i2,i3,i4;
  for (i4=0;i4<=1;i4++){
    for (i3=0;i3<=1;i3++){
      for (i2=0;i2<=1;i2++){
        for (i1=0;i1<=1;i1++){
          if(i1==1) digitalWrite(led1, LOW);
          if(i2==1) digitalWrite(led2, LOW);
          if(i3==1) digitalWrite(led3, LOW);
          if(i4==1) digitalWrite(led4, LOW);
          delay(1000);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          delay(1000);
        }
       }
      }
     }
  
  delay(1000);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  }
