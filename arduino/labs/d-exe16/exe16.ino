//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int speedd = 10; //5000 ms

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 //Serial.println(adc_key_in);
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 260)  return btnDOWN; 
 if (adc_key_in < 450)  return btnLEFT; 
 if (adc_key_in < 650)  return btnSELECT;  
 

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/


 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Welcome to DSFUM Text LCD Lab !!!"); // print a simple message
 Serial.begin(9600);
}
 
void loop()
{
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.setCursor(0,1);            // move to the begining of the second line



Serial.println(speedd);
 for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();

   
    
    // wait a bit:
    speed_listener(5150 - speedd*500);
    
  }
  
}



void speed_listener(int delayy)
{
  for (int repetari;repetari<=delayy/50;repetari++)
  {
      lcd_key = read_LCD_buttons();  // read the buttons
      switch (lcd_key)               // depending on which button was pushed, we perform an action
     {
       case btnRIGHT:
         {
         if (speedd==10)
          break;
         speedd++;
         Serial.println(speedd);
         while(read_LCD_buttons()!=5);
         loop();
         //break;
         }
       case btnLEFT:
         {
         if (speedd==0)
          break;
         speedd--;
         Serial.println(speedd);
         while(read_LCD_buttons()!=5);
         loop();
         //break;
         }
     }
     delay(50);
  }
}


