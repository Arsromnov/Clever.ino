#include <Arduino.h>
#include <Wire.h>
#include <adafruit_GFX.h>
#include <adafruit_SSD1306.h>

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

   display.print(F("clever.ino 2026.3"));
   display.display();
}


void loop() {

 

   if (Serial.available() > 0)   
   {
     String input = Serial.readString();
     input.trim();
     

     char buf[64];
     input.toCharArray(buf, sizeof(buf));

     char* comd = strtok(buf, " ");

     char* arg1 = strtok(NULL, " ");
     char* arg2 = strtok(NULL, " ");

     String cmd = String(comd);
     

     
     display.fillRect(0, 19, 128, 45 , SSD1306_BLACK);
     display.setCursor(0, 20);
     display.print(F(">"));
     display.println(input); 

   

     if (cmd == "rst") {
           
          display.clearDisplay();
          display.setCursor(0, 30);
          display.println(F("restarting"));
          display.display();
         
          delay(5000);
          void(* resetF) (void) = 0; 
          resetF();  

     } else if (cmd == "inv") {
         if (arg1 != NULL) {
            int val = atoi(arg1);
            display.invertDisplay(val);
        } else {
            display.println(F("use the 1(true)/0(false) arguments"));
        }
     } else if (cmd == "rand") {
        if (arg1 != NULL && arg2 != NULL) {
           display.println(random(atol(arg1), atol(arg2)));
        } else {
           display.println(F("use the int/int arguments"));
        }
     } else if (cmd == "help") {
        display.println(F("see help on README"));
     } else if (cmd == "utime") {
        display.println(millis() / 1000);
     } else if (cmd == "mtrx") {
        for (int i = 0; i < 40;i++) {
            display.print(random(0, 2));
            display.print(" ");
        }
     } else if (cmd == "fram") {
        char top;
        extern char *__brkval;
        extern char __bss_end;
        display.print((int)(&top - (__brkval == 0 ? &__bss_end : __brkval)));
        display.println("B");
     } else if (cmd == "dim") {
        if (arg1 != NULL) {
            int val = atoi(arg1);
            display.dim(val);
        } else {
            display.println(F("use the 1(true)/0(false) arguments"));
        }


     } else if (cmd == "cpu")  {
        #ifdef F_CPU
           display.print(F_CPU / 1000000);
           display.println(F("MHz"));
        #endif   
     } else {
        display.println(F("Unknow command"));
     } 

     display.display();
   }
   
}

