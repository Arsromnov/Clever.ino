# Clever.ino Legacy
Simple FakeOs for Arduino/ESP32 

![Tested on](https://img.shields.io/badge/Tested_on-Arduino_Uno-purple?style=blue&logo=arduino)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=flat&logo=arduino)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat&logo=cplusplus)
![Версия Проекта](https://img.shields.io/badge/Clever.ino_Legacy-2026.3-yellow?style=fla)

> [!TIP]
> Project has 2 version, legacy(for uno, and SSD1306) / 32(for ESP32 and TFT with ST7735 128x160, 1.8")

> [!WARNING]
> Recommended for use on the Arduino Uno (probably works on other Arduino boards too.).


### How to setup?
1.Install libaries
>Adafruit SSD1306
>
>Adafruit GFX Library
>
>Adafruit BusIO

2.Connect the display 
>VCC -> 5V or 3V3
>
>GND -> GND
>
>SCL -> A5
>
>SDA -> A4
>


3.Open clever.ino file on arduino IDE and run it


### Commands

| Command | Action | Arguments |
| :--- | :--- | :--- |
| `help` | Displays the text "see help on readme" (essentially a debug command) | |
| `rst` | Board reboot | |
| `inv` | Inversion control (enable/disable) | `1` (true) / `0` (false) |
| `fram` | Show free RAM | |
| `utime` | Display of the time elapsed since firmware execution began | |
| `rand` | Generating random int | `<int>` (min) / `<int>` (max) |
| `cpu` | Show CPU Mhz | |
| `dim` | Display power-saving mode management(enable/disable) | `1` (true) / `0` (false) |
| `mtrx` | Simply outputting zeros and ones | |

