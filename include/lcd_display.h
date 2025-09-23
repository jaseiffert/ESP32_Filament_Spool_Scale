#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

#include "globals.h"
#include "configuration.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

extern Adafruit_SSD1306 display;

// Create an instance of the prepared class.

namespace LcdDisplay
{
    void displayWeight(float weight);

    void displayMsg(String textMsg);

    void displayMsg(String textMsg, int16_t X, int16_t Y);

    void displayClear();

    void drawGradation(void);

    void printGridLines();

    void drawArea(int x, int y, int width, int height);

    void drawDate();

    void drawTime();

    void drawWiFiSignal(int8_t signal);

} // namespace LcdDisplay

#endif
