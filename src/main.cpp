#include <Arduino.h>
#include <SPI.h>
#include <adafruit_ST7735.h> 
#include <adafruit_GFX.h>

#define TFT_CS     15
#define TFT_RST    4
#define TFT_DC     2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB); 
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
  tft.setCursor(4, 6);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
  tft.println("Cleverino32 2026.1");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();

    char buf[64];
    input.toCharArray(buf, sizeof(buf));

    char* comd = strtok(buf, " ");
    char* arg1 = strtok(NULL, " ");
    char* arg2 = strtok(NULL, " ");

    if (comd == NULL) return;
    String cmd = String(comd);

    tft.fillRect(0, 16, 160, 144, ST77XX_BLACK);
    tft.setCursor(0, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(">");
    tft.println(input);
    tft.println("");
   
    if (cmd == "help") {
      tft.print("classic: READ HELP ON README");
    } else {
      tft.print("unknow command");
    }
  }
}