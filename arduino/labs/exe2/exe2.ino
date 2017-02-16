/* 2.
Aceeasi problema a mai sus dar tinand shiledul invers (180 de grade). Evident, cifrele trebuie sa fie afisate corect - 4pt
*/

//acelasi cod dar schimbam mappingul segmentelor pentru a afisa corect intors la 180 grade

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
//const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_MAP[] = {0xC0,0xCF,0xA4,0x86,0x8B,0x92,0x90,0xC7,0X80,0x82}; //mappingul segmentelor inversat pentru afisare cifre intoarse la 180 de grade
/* Byte maps to select digit 1 to 4 */
//const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
const byte SEGMENT_SELECT[] = {0xF8,0xF4,0xF2,0xF1}; //mappingul cifrelor inversat pentru afisarea ordinii corecte a cifrelor
int epochs = 0;

void setup ()
{
/* Set DIO pins to outputs */
pinMode(LATCH_DIO,OUTPUT);
pinMode(CLK_DIO,OUTPUT);
pinMode(DATA_DIO,OUTPUT);
}
 
/* Main program */
void loop()
{
 
/* Update the display with the current counter value */

int counter = millis()/100 - epochs * 10000; //speed can be set here

if (counter < 10) //first digits
{
  WriteNumberToSegment(3 , counter);
}
else if (counter<100) //2nd digits
{
  WriteNumberToSegment(3 , (counter)%10);
  WriteNumberToSegment(2 , ((counter)/10)%10);
}
else if (counter<1000) //3rd digits
{
  WriteNumberToSegment(3 , (counter)%10);
  WriteNumberToSegment(2 , ((counter)/10)%10);
  WriteNumberToSegment(1 , ((counter)/100)%10);
}
else if (counter<10000) //4th digits
{
  WriteNumberToSegment(3 , (counter)%10);
  WriteNumberToSegment(2 , ((counter)/10)%10);
  WriteNumberToSegment(1 , ((counter)/100)%10);
  WriteNumberToSegment(0 , ((counter)/1000)%10);
}
else if (counter==10000) //if we reached 9999 we reset it from 1
  epochs++;
  


}
 
/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
digitalWrite(LATCH_DIO,LOW);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
digitalWrite(LATCH_DIO,HIGH);
}