#include <IRremote.h>
#include "utils.h"

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //starts receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    // translateIR(results); 
    irrecv.resume(); // next value
  }
}
