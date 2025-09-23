#include <Arduino.h>
#include <Preferences.h>
#include "soc/rtc.h"
#include "rom/ets_sys.h"
// External Libraries

// Local Include Files
#include "globals.h"
#include "hardware.h"
#include "lcd_display.h"
#include "wifi_helper.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint32_t Freq = 0;
int buttonState = 0;

// Read HX711 Timer
hw_timer_t *timer1 = NULL;

unsigned long button_time = 0;
unsigned long last_button_time = 0;

Preferences appPrefs;

// put function declarations here:
void ARDUINO_ISR_ATTR scaleReadTimer();
void setupLCD();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    // Slow down CPU
    setCpuFrequencyMhz(80);

    pinMode(22, OUTPUT);

    // Open Preferences with my-app namespace. Each application module, library, etc
    // has to use a namespace name to prevent key name collisions. We will open storage in
    // RW-mode (second parameter has to be false).
    // Note: Namespace name is limited to 15 chars.
    appPrefs.begin("my-app", false);

    delay(1000);
    Freq = getCpuFrequencyMhz();
    debugp("CPU Freq = ");
    debugp(Freq);
    debugpln(" MHz");
    Freq = getXtalFrequencyMhz();
    debugp("XTAL Freq = ");
    debugp(Freq);
    debugpln(" MHz");
    Freq = getApbFrequency();
    debugp("APB Freq = ");
    debugp(Freq);
    debugpln(" Hz");
    debugpln("Setup Starting...");
    delay(1000);

    // Set timer frequency to 1Mhz
    timer1 = timerBegin(1000000);

    // Attach onTimer function to our timer.
    timerAttachInterrupt(timer1, &scaleReadTimer);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
    // timerAlarm(timer1, 2000000, true, 0);

    // Init LCD Display
    setupLCD();

    // Init Wifi
    // WifiHelper::setupWiFi();

    // Init Hardware
    Hardware::setupHardware();

    // Hardware::calibrateScale();
}

void loop()
{
    // Tare Scale
    buttonState = digitalRead(TARE_BUTTON);

    if (buttonState == HIGH)
    {
        button_time = millis();
        if (button_time - last_button_time > 250)
        {
            Hardware::tareScale();
            last_button_time = button_time;
        }
    }

    // Calibrate Scale
    buttonState = digitalRead(CALABRATE_BUTTON);

    if (buttonState == HIGH)
    {
        button_time = millis();
        if (button_time - last_button_time > 250)
        {
            Hardware::buttonCalibrateScale();
            last_button_time = button_time;

            // Change display title back to what it was
            display.fillRect(0, 0, display.width() - 0, display.height() - 0, SSD1306_BLACK);
            display.setCursor(0, 0); // Start at top-left corner
            display.println(F("Filament Scale"));
            display.display();
        }
    }

    Hardware::readScale();
    delay(1000);
    // Hardware::readNFC();
    // delay(1000);
}

// put function definitions here:

void ARDUINO_ISR_ATTR scaleReadTimer()
{
}

void setupLCD()
{
    debugpln("------------- SSD1306 LCD --------------");

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        debugpln(F("SSD1306 allocation failed"));
        // for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2

    // Clear the buffer
    display.clearDisplay();

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(F(DISPLAY_TITLE));
    display.display();
}
