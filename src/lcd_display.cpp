#include "lcd_display.h"

namespace LcdDisplay {

    void displayWeight(float weight) {
        display.setTextSize(2);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.fillRect(0, 20, display.width(), display.height() - 20, SSD1306_BLACK);
        // display.display(); // Update screen with each newly-drawn rectangle
        display.setCursor(10, 30); // Start at top-left corner
        if (weight < 1) {
            display.print(round(weight));
        }
        else if (weight < 100 && weight > 1) {
            display.print(weight);
        }
        else if (weight > 100) {
            display.print(int(weight));
        }
        display.println(F(" G"));
        display.display();
    } // void displayWeight(float weight)

    void displayMsg(String textMsg) {
        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.fillRect(10, 30, display.width() - 10, 26, SSD1306_BLACK);
        // display.display(); // Update screen with each newly-drawn rectangle
        display.setCursor(10, 30); // Start at top-left corner
        display.println(textMsg);
        display.display();
    }

    void displayMsg(String textMsg, int16_t X, int16_t Y) {
        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.fillRect(X, Y, display.width() - X, display.height() - Y, SSD1306_BLACK);
        // display.display(); // Update screen with each newly-drawn rectangle
        display.setCursor(X, Y); // Start at top-left corner
        display.println(textMsg);
        display.display();
    }

    void displayClear() {
        display.clearDisplay(); // Clear the buffer
        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.setCursor(0, 0);             // Start at top-left corner
        display.display();

    }

    void drawGradation(void) {
        debugpln("Draw Gradiant");
        // Draw a gradient on the background
    } // void drawGradation(void)

    void printGridLines() {} // void printGridLines()

    void drawArea(int x, int y, int width, int height) {}

    void drawDate() {}

    void drawTime() {}

} // namespace LcdDisplay
