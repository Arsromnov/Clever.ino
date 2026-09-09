# Clever.ino
Simple FakeOs for Arduino/ESP32 

![ESP32](https://img.shields.io/badge/Tested%20on-ESP32-green?style=flat&logo=espressif&logoColor=white)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=flat&logo=arduino)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat&logo=cplusplus)
![Версия Проекта](https://img.shields.io/badge/Clever.ino32-2026.1-yellow?style=fla)

> [!NOTE]
> Project has 2 version, legacy(for uno, and SSD1306) / 32(for ESP32 and TFT with ST7735 128x160, 1.8")


### How to setup?
1.Install libaries
>esp32 by Espressif Systems
>
>Adafruit ST7735 and ST7789 Library
>
>Adafruit GFX Library
>
>Adafruit BusIO

2.Connect the display 
>VCC -> 3V3
>
>GND -> GND
>
>CS -> GPIO 15
>
>RESET -> GPIO 4
>
>A0 -> GPIO 2
>
>SDA -> GPIO 23
>
>SCK -> GPIO 18
>
>LED -> 3V3

3.Open clever.ino file on arduino IDE and run it


### Commands

| Command | Action | Arguments |
| :--- | :--- | :--- |
| `help` | Displays the text "see help on readme" (essentially a debug command) | |
| `rst` | Board reboot | |
| `inv` | Inversion control (enable/disable) | `1` (true) / `0` (false) |
| `ram` | Show RAM information | |
| `utime` | Display of the time elapsed since firmware execution began | |
| `rand` | Generating random int | `<int>` (min) / `<int>` (max) |
| `cpu` | Show CPU information | |
| `tftoff` | Screen control (enable/disable) | `1` (true) / `0` (false) |
| `flash` | Show information about flash | |
| `wifi` | WiFi functions | `mac` (show MAC address) / `scan` (scan networks) |
| `sdk` | Show SDK version | |
| `tempr` | Display of temperature from the built-in ESP32 sensor | `<int>` (< 15) |
| `rot` | Set screen rotation | `<int>` (1, 2, 3, 4) |


