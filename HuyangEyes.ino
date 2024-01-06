#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

// Display constructor for primary hardware SPI connection -- the specific
// pins used for writing to the display are unique to each board and are not
// negotiable. "Soft" SPI (using any pins) is an option but performance is
// reduced; it's rarely used, see header file for syntax if needed.


//NOTE Screen 1 copies to screen 2

//Adafruit_GC9A01A::Adafruit_GC9A01A(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst, int8_t miso)


//ESP32 - Dev Board Pins to TFT Pins 
//                    CS  DC SDA SCL RST miso
Adafruit_GC9A01A  tft(22, 16, 23, 18, 4, -1); //first screen   .. miso unused. 
Adafruit_GC9A01A tft2(21, 16, 23, 18, 4, -1); //second screen


//Screen Res 240*240
#define sw 240 //screen width
#define sh 240 //screen height


void setup() {
  Serial.begin(9600); //For Debugging
  Serial.println("EYES Test!.. Booting");



  tft.begin();  
  digitalWrite(22, HIGH);//target one eye
  digitalWrite(21, LOW); //other is 'slaved' copies , which is which?? 
  booting();  
}

void loop(void) 
{
  
  MainEyes(); 
  int rnd = random(2000,5000); //delay 2 to 5 seconds
  delay(rnd);
  Blink(); //delay(100);

 
  //Not reliable!! ignore for now
  //BlinkLeft();delay(1000);
  //BlinkRight();delay(1000);
  
}

void booting()
{
  tft.fillScreen(GC9A01A_BLACK);
  tft.setCursor(100, 50);
  tft.setTextColor(GC9A01A_WHITE);  tft.setTextSize(1);
  tft.println("Booting...");
  tft.setTextColor(GC9A01A_YELLOW); tft.setTextSize(2);
  tft.println("Booting...");
  delay(500);  
  tft.fillScreen(GC9A01A_BLACK);
}

void MainEyes()
{ 
  tft.begin();  
  digitalWrite(22, HIGH);//target one eye
  digitalWrite(21, LOW); //other is 'slaved' copies , which is which?? 
  
  int x = sw/2;
  int y = sh/2;

  tft.fillCircle(x,y, sw,  tft.color565(255,255,0));    
  tft.drawCircle(x,y,50, tft.color565(0,0,0));  
  tft.drawCircle(x,y,49, tft.color565(0,0,0));  
  tft.drawCircle(x,y,48, tft.color565(0,0,0));    
  
  tft.drawCircle(x,y,18, tft.color565(0,0,0));  
  tft.drawCircle(x,y,16, tft.color565(0,0,0));  
  tft.drawCircle(x,y,17, tft.color565(0,0,0));
  

  int numOfLines = sw/7;
  for(int i=0;i<numOfLines;i++)
  {
    tft.drawFastVLine(i*numOfLines, 0, 240, tft.color565(0,0,0));
  }
 
  yield();  
}

void Blink()
{
  tft.fillScreen(GC9A01A_BLACK);  
  yield();
}

void BlinkLeft()
{
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);  
  yield();
  tft.fillScreen(GC9A01A_YELLOW);    
}


void BlinkRight()
{
  tft2.begin();
  tft2.fillScreen(GC9A01A_BLACK);  
  yield();
  tft2.fillScreen(GC9A01A_YELLOW);    
}

//just because...
int x = 20; int xv = 2;
int y = 50; int yv = 3;
void test()
{
   x+=xv;   
   y+=yv;

   int radius = 10;
   if(x<0||x>240-radius){xv*=-1;}
   if(y<0||y>240-radius){yv*=-1;}
   
   tft.fillCircle(x, y, radius, tft.color565(255, 255, 0));      
   yield(); 
   delay(10);    
   tft.fillCircle(x, y, radius, tft.color565(0, 0, 0));
   yield(); 
}
