#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
   display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
   Serial.begin(9600);
   display.clearDisplay();
  
   display.setTextSize(1);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(0, 2);
   display.setTextWrap(true);

   display.print("clever.ino 2026.1");
   display.display();
}


void loop() {

 

   if (Serial.available() > 0)   
   {
     String input = Serial.readString();
     input.trim();

     
     display.fillRect(0, 19, 128, 45 , SSD1306_BLACK);
     display.setCursor(0, 20);
     display.print(">");
     display.println(input); 

   

     if (input == "rst") {
           
          display.clearDisplay();
          display.setCursor(0, 30);
          display.println("restarting");
          display.display();
          delay(5000);
          void(* resetF) (void) = 0; 
          resetF();  

     } else if (input == "invo") {
        display.invertDisplay(true);
     } else if (input == "invf") {
        display.invertDisplay(false);
     } else if (input == "rand") {
        display.println(random(1, 101));
     } else if (input == "help") {
        display.println("see help on README");
     } else if (input == "utime") {
        display.println(millis() / 1000);
     } else if (input == "mtrx") {
        for (int i = 0; i < 40;i++) {
            display.print(random(0, 2));
            display.print(" ");
        }
     } else {
        display.println("Unknow command");
     } 
     
     
     
     


     display.display();
   }
   
}

