#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// http://wiibrew.org/wiki/U16_colors

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = 0x9341;


  tft.begin(identifier);

  Serial.println(F("Benchmark                Time (microseconds)"));


  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, WHITE));
  delay(500);

  Serial.println(F("Done!"));
  tft.fillScreen(BLACK);
}

void loop(void) {
  uint8_t rotation = 0;
  tft.setRotation(rotation);


  while (Serial.available() == 0)
   /* just wait */ ;

  Serial.println("\n..waiting for input---\n");
  String input;
  //if (Serial.available() > 0) {
  //Serial.println(">> Serial is available");
  input = Serial.readString();

  if(input){
  Serial.println("input: " + input);
  if (strcmp(input.c_str(), "circle") == 0){
    uint8_t x, y, radius;
    uint16_t color;
    
    Serial.print("\n x >> ");
    x = readString();

    Serial.print("\n y >> ");
    y = readString();

    Serial.print("\n radius >> ");
    radius = readString();

    Serial.print("\n color (yes | -) >> ");
    String response = readInput();
    Serial.print(response);
    if(strcmp(response.c_str(), "yes") == 0){
      color = readColor();
      draw_circle(x, y, radius, color);
    } else {
      draw_circle(x, y, radius, YELLOW);
    }
  } else if (strcmp(input.c_str(), "rectangle") == 0){
    uint8_t x, y, width, height;
    uint16_t color;
  
    Serial.print("\n x >> ");
    x = readString();

    Serial.print("\n y >> ");
    y = readString();

    Serial.print("\n width >> ");
    width = readString();

    Serial.print("\n height >> ");
    height = readString();

    Serial.print("\n color (yes | -) >> ");
    String response = readInput();
    Serial.print(response);
    if(strcmp(response.c_str(), "yes") == 0){
      color = readColor();
      draw_rectangle(x, y, width, height, color);
    } else {
      draw_rectangle(x, y, width, height, YELLOW);
    }
    
  } else if (strcmp(input.c_str(), "line") == 0){
    uint8_t x1, y1, x2, y2;
    uint16_t color;
  
    Serial.print("\n x1 >> ");
    x1 = readString();

    Serial.print("\n y1 >> ");
    y1 = readString();

    Serial.print("\n x2 >> ");
    x2 = readString();

    Serial.print("\n y2 >> ");
    y2 = readString();

    Serial.print("\n color (yes | -) >> ");
    String response = readInput();
    Serial.print(response);
    if(strcmp(response.c_str(), "yes") == 0){
      color = readColor();
      draw_line(x1, y1, x2, y2, color);
    } else {
      draw_line(x1, y1, x2, y2, YELLOW);
    }

  } else if (strcmp(input.c_str(), "triangle") == 0){
    uint8_t x1, y1, x2, y2, x3, y3;
    uint16_t color;
  
    Serial.print("\n x1 >> ");
    x1 = readString();

    Serial.print("\n y1 >> ");
    y1 = readString();

    Serial.print("\n x2 >> ");
    x2 = readString();

    Serial.print("\n y2 >> ");
    y2 = readString();

    Serial.print("\n x3 >> ");
    x3 = readString();

    Serial.print("\n y3 >> ");
    y3 = readString();

    Serial.print("\n color (yes | -) >> ");
    String response = readInput();
    Serial.print(response);
    if(strcmp(response.c_str(), "yes") == 0){
      color = readColor();
      draw_triangle(x1, y1, x2, y2, x3, y3, color);
    } else {
      draw_triangle(x1, y1, x2, y2, x3, y3, YELLOW);
    }

  } else if (strcmp(input.c_str(), "car") == 0){
    Serial.println("Car drawn");
    draw_car();
    
  } else if (strcmp(input.c_str(), "house") == 0){
    Serial.println("House drawn");
    draw_house();
    
  } else if (strcmp(input.c_str(), "clear") == 0){
    Serial.println("Screen will be cleared");
    Serial.println("...................................");
    tft.fillScreen(BLACK);
  }

  } //end if(input)

  //}
  /*for(uint8_t rotation=0; rotation<4; rotation++) {
  tft.setRotation(rotation);
  delay(2000);
  }*/
}

String readInput(){
  while (Serial.available() == 0)
   /* just wait */ ;
  String input = Serial.readString();

  return input;
}

uint8_t readString(){
  while (Serial.available() == 0)
   /* just wait */ ;
   
  String input = Serial.readString();
  //byte buf[31];
  //input.StringToCharArray(buf,30);
  Serial.print(input);

  //return buf;
  return (uint8_t *) atoi(input.c_str());
}

uint16_t readColor(){
  int R, G, B;
  String temp;

  while (Serial.available() == 0)
   /* just wait */ ;

  Serial.println(" >> col > R: ");
  temp = Serial.readString();
  R = atoi(temp.c_str());
  Serial.print(R);


  while (Serial.available() == 0)
   /* just wait */ ;

  Serial.println(" >> col > G: ");
  temp = Serial.readString();
  G = atoi(temp.c_str());
  Serial.print(G);

  while (Serial.available() == 0)
   /* just wait */ ;
  
  Serial.println(" >> col > B: ");
  temp = Serial.readString();
  B = atoi(temp.c_str());
  Serial.print(B);

  return tft.color565((uint8_t *) R, (uint8_t *) G, (uint8_t *) B);
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
  for(y=radius; y<h; y+=r2) {
    tft.fillCircle(x, y, radius, color);
  }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
        w = tft.width()  + radius,
        h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long draw_circle(uint8_t x, uint8_t y, uint8_t radius, uint16_t color) {
  Serial.println("\n\tDrawing circle with params: x="); 
  /*Serial.print(x);
  Serial.print(", y="); Serial.print(y);
  Serial.print(", radius= "); Serial.print(radius);
  Serial.print(", color="); Serial.print(color);*/
  tft.drawCircle(x, y, radius, color);
}

//rectangle(x,y,width,height,color) - 1pt
unsigned long draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color) {
  tft.drawRect(x, y, width, height, color);
}

//line(x1,y1,x2,y2,color) - 2pt
unsigned long draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color) {
  tft.drawLine(x1, y1, x2, y2, color);
}

//triangle(x1,y1,x2,y2,x3,y3,color) - 1pt
unsigned long draw_triangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint16_t color) {
  tft.drawTriangle(
    x1, y1, // peak
    x2, y2, // bottom left
    x3, y3, // bottom right
    color
  );
}

void draw_car(){
  int xPos = 50;

    draw_circle(xPos, 200, 30, RED);
    draw_circle(xPos+60, 200, 30, RED);
    
    draw_circle(xPos, 200, 10, WHITE);
    draw_circle(xPos+60, 200, 10, WHITE);
    
    draw_rectangle(xPos-10, 200-60+10, 60+20, 50, CYAN);
    
    draw_rectangle(xPos+40, 200-60+10, 30, 25, WHITE);
}

void draw_house(){
  int xPos = 50;

    draw_rectangle(xPos, 100, 60+20, 50, CYAN);
    draw_triangle(xPos, 100, xPos+80, 100, (xPos+130)/2, 60, CYAN);
    
    draw_rectangle(xPos+50, 70, 15, 25, RED);
    
    draw_rectangle(xPos+10, 110, 15, 15, WHITE);
    draw_rectangle(xPos+55, 110, 15, 15, WHITE);
    
    draw_rectangle(xPos+35, 110, 15, 35, WHITE);
}
