#include <Arduino.h>
#include <SPI.h>
#include <adafruit_ST7735.h>
#include <adafruit_GFX.h>
#include "esp_chip_info.h"
#include <WiFi.h>

#define TFT_CS 15
#define TFT_RST 4
#define TFT_DC 2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup()
{
  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
  tft.setCursor(4, 6);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
  tft.println("Clever.ino32 2026.1");
}

void loop()
{
  if (Serial.available() > 0)
  {
    String input = Serial.readString();
    input.trim();

    char buf[64];
    input.toCharArray(buf, sizeof(buf));

    char *comd = strtok(buf, " ");
    char *arg1 = strtok(NULL, " ");
    char *arg2 = strtok(NULL, " ");

    if (comd == NULL)
      return;
    String cmd = String(comd);

    tft.fillRect(0, 16, 160, 144, ST77XX_BLACK);
    tft.setCursor(0, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(">");
    tft.println(input);
    tft.println("");

    if (cmd == "help")
    {
      tft.print(F("READ HELP ON README"));
    }
    else if (cmd == "rst")
    {
      tft.fillRect(0, 16, 160, 144, ST77XX_BLACK);
      tft.setCursor(10, 20);
      tft.print(F("Restarting"));
      delay(2000);
      ESP.restart();
    }
    else if (cmd == "inv")
    {
      if (arg1 != NULL)
      {
        int val = atoi(arg1);
        tft.invertDisplay(val);
      }
      else
      {
        tft.println(F("use the 1(true)/0(false) arguments"));
      }
    }
    else if (cmd == "ram")
    {
      uint32_t fram = ESP.getFreeHeap();
      uint32_t tram = ESP.getHeapSize();
      uint32_t uram = tram - fram;

      tft.print(F("free KB "));
      tft.println(fram / 1024.0, 1);

      tft.print(F("total KB "));
      tft.println(tram / 1024.0, 1);

      tft.print(F("used KB "));
      tft.println(uram / 1024.0, 1);
    }
    else if (cmd == "utime")
    {
      tft.print(millis() / 100);
    }
    else if (cmd == "rand")
    {
      if (arg1 != NULL && arg2 != NULL)
      {
        tft.println(random(atol(arg1), atol(arg2)));
      }
      else
      {
        tft.println(F("use the <int>/<int> arguments"));
      }
    }
    else if (cmd == "cpu")
    {
      esp_chip_info_t cpu_inf;
      esp_chip_info(&cpu_inf);

      tft.print(F("model "));
      tft.println(ESP.getChipModel());

      tft.print(F("cores "));
      tft.println(cpu_inf.cores);

      tft.print(F("freq mhz "));
      tft.println(ESP.getCpuFreqMHz());

      tft.print(F("rev "));
      tft.println(ESP.getChipRevision());
    }
    else if (cmd == "tftoff")
    {
      if (arg1 != NULL)
      {
        int val = atoi(arg1);
        tft.enableDisplay(val);
      }
      else
      {
        tft.println(F("use the 1(true)/0(false) arguments"));
      }
    }
    else if (cmd == "flash")
    {
      uint32_t fsiz = ESP.getFlashChipSize();
      uint32_t fspd = ESP.getFlashChipSpeed();
      uint32_t skrt = ESP.getFreeSketchSpace();

      tft.print("flash size ");
      tft.println((float)fsiz / 1024.0, 1);

      tft.print("flash speed ");
      tft.println((float)fspd / 1000000.0, 1);

      tft.print("free scratch space ");
      tft.println((float)skrt / 1024.0, 1);
    }
    else if (cmd == "wifi")
    {
      if (arg1 != NULL)
      {
        if (strcmp(arg1, "scan") == 0)
        {
          tft.println("Please wait");
          tft.println("");
          WiFi.scanDelete();
          int n = WiFi.scanNetworks();

          if (n == 0)
          {
            tft.println("no networks found");
          }
          else
          {

            for (int i = 0; i < n; ++i)
            {
              tft.print(WiFi.SSID(i));
              tft.print(" ");
              tft.print(WiFi.RSSI(i));
              tft.print(" ");
              tft.println("dBm");
              tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " [O]" : " [W]");
            }
          }
        }
        else if (strcmp(arg1, "mac") == 0)
        {
          tft.print("MAC ");
          tft.println(WiFi.macAddress());
        }
        else
        {
          tft.print("use the <string> argument");
        }
      }
    }
    else if (cmd == "sdk")
    {
      tft.println(ESP.getSdkVersion());
    }
    else if (cmd == "tempr")
    {
      if (arg1 != NULL)
      {
        if (atol(arg1) < 16)
        {
          int x = atol(arg1);
          double prev = 0;
          double curr = 0;

          for (size_t i = 0; i < x; i++)
          {
            curr = temperatureRead();

            if (curr > prev)
            {
              tft.print(curr);
              tft.println("C   +");
            }
            else if (curr > prev)
            {
              tft.print(curr);
              tft.println("C   -");
            }
            else
            {
              tft.print(curr);
              tft.println("C   >");
            }
            prev = curr;
            delay(500);
          }
        }
        else
        {
          tft.println("use an argument less than 45");
        }
      }
      else
      {
        tft.println("use the <int> argument");
      }
      
    }
    else if (cmd == "rot")
    {
      if (arg1 != NULL)
      {
        if (atol(arg1) == 1)
        {
          tft.fillScreen(ST77XX_BLACK);
          tft.setRotation(0);
          tft.setCursor(4, 6);
          tft.setTextColor(ST77XX_GREEN);
          tft.setTextSize(1);
          tft.println("Clever.ino32 2026.1");
        }
        else if (atol(arg1) == 2)
        {
          tft.fillScreen(ST77XX_BLACK);
          tft.setRotation(1);
          tft.setCursor(4, 6);
          tft.setTextColor(ST77XX_GREEN);
          tft.setTextSize(1);
          tft.println("Clever.ino32 2026.1");
        }
        else if (atol(arg1) == 3)
        {
          tft.fillScreen(ST77XX_BLACK);
          tft.setRotation(2);
          tft.setCursor(4, 6);
          tft.setTextColor(ST77XX_GREEN);
          tft.setTextSize(1);
          tft.println("Clever.ino32 2026.1");
        }
        else if (atol(arg1) == 4)
        {
          tft.fillScreen(ST77XX_BLACK);
          tft.setRotation(3);
          tft.setCursor(4, 6);
          tft.setTextColor(ST77XX_GREEN);
          tft.setTextSize(1);
          tft.println("Clever.ino32 2026.1");
        }
      }
      else
      {
        tft.println("if you want to set custom rotation,  use the <int> argument");
      }
    }
    else
    {
      tft.print("unknown command");
    }
  }
}