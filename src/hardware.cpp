#include "hardware.h"
#include "lcd_display.h"

namespace Hardware
{
    Adafruit_PN532 nfc(I2C_SDA_PIN, I2C_SCL_PIN);

    HX711 scale;

    uint8_t dataPin = HX711_DATA;
    uint8_t clockPin = HX711_CLK;
    float loadCellFactor = 0;
    int32_t scale_offset = 0;
    // use scale.set_offset(397); and scale.set_scale(-0.024500);

    void setupHardware()
    {
        debugpln("-------------Setup Hardware ---------------");

        appPrefs.begin("scalePrefs", true); // open (or create and then open if it does not yet exist) the namespace "scalePrefs" in RW mode.

        if (appPrefs.isKey("scale"))
        {
            loadCellFactor = appPrefs.getFloat("scale");
            scale_offset = appPrefs.getInt("offset");
            debugpln(loadCellFactor);
            debugpln(scale_offset);
        }
        else
        {
            debugpln("app Prefs not available");
        }
        //appPrefs.end();

        debugpln("------------- Buttons ---------------");
        pinMode(TARE_BUTTON, INPUT_PULLDOWN);
        pinMode(CALABRATE_BUTTON, INPUT_PULLDOWN);

        debugpln("------------- HX711 Load Cell Info ---------------");
        scale.begin(dataPin, clockPin, false);
        debugpln(scale.is_ready());
        if (loadCellFactor != 0)
        {
            // load cell factor 5kg
            scale.set_scale(loadCellFactor);
            scale.set_offset(scale_offset);

            // reset the scale to zero = 0
            // scale.tare(20);
        }
        else
        {
            // Run Calibration
            // calibrateScale();
        }

        debugpln("-------------Initializing PN532 ---------------");
        nfc.begin();

        uint32_t version = nfc.getFirmwareVersion();
        if (!version)
        {
            debugpln("Didn't find PN532 board");
            while (1)
                ;
        }
        else
        {
            debugp("NFC Firmware Ver: ");
            debugpln((String)version);
            nfc.SAMConfig();
            debugpln("PN532 initialized!");
        }
    } // void setupHardware()

    void calibrateScale()
    {
        debugpln("\n\nCALIBRATION\n===========");
        debugpln("remove all weight from the loadcell");
        //  flush Serial input
        while (Serial.available())
            Serial.read();

        debugpln("and press enter\n");
        while (Serial.available() == 0)
            ;

        debugpln("Determine zero weight offset");
        //  average 20 measurements.
        scale.tare(20);
        int32_t offset = scale.get_offset();

        debugp("OFFSET: ");
        debugpln(offset);
        debugpln();

        debugpln("place a weight on the loadcell");
        //  flush Serial input
        while (Serial.available())
            Serial.read();

        debugpln("enter the weight in (whole) grams and press enter");
        uint32_t weight = 0;
        while (Serial.peek() != '\n')
        {
            if (Serial.available())
            {
                char ch = Serial.read();
                if (isdigit(ch))
                {
                    weight *= 10;
                    weight = weight + (ch - '0');
                }
            }
        }
        debugp("WEIGHT: ");
        debugpln(weight);
        scale.calibrate_scale(weight, 20);
        float scaleFactor = scale.get_scale();

        debugp("SCALE:  ");
        debugpln(scaleFactor, 6);

        debugp("\nuse scale.set_offset(");
        debugp(offset);
        debugp("); and scale.set_scale(");
        debugp(scaleFactor, 6);
        debugp(");\n");
        debugpln("in the setup of your project");

        debugpln("\n\n");
    } // void calibrate()

    void readScale()
    {
        if (scale.is_ready())
        {
            float reading = scale.get_units(5);
            debugp("HX711 reading: ");
            debugpln(reading);
            LcdDisplay::displayWeight(reading);
        }
        else
        {
            debugpln("HX711 not found.");
            LcdDisplay::displayMsg("HX711 not found.");
        }
    }

    void tareScale()
    {
        // reset the scale to zero = 0
        scale.tare(20);
        LcdDisplay::displayMsg("Tare Complete.");
    }

    void buttonCalibrateScale()
    {
        int buttonState = 0;
        unsigned long button_time = 0;
        unsigned long last_button_time = 0;
        bool exitLoop = false;

        debugpln("\n\nCALIBRATION\n===========");
        LcdDisplay::displayClear();
        LcdDisplay::displayMsg("Calibrating Scale...", 0, 0);
        debugpln("Remove all weight from scale");
        LcdDisplay::displayMsg("Remove all weight from scale", 0, 20);
        while(digitalRead(CALABRATE_BUTTON) == HIGH){
            delay(1000);
        }
        debugpln("Press Calibrate Button when ready\n");
        LcdDisplay::displayMsg("Press Calibrate Button when ready", 0, 40);
        while (exitLoop == false)
        {
            buttonState = digitalRead(CALABRATE_BUTTON);

            if (buttonState == HIGH)
            {
                button_time = millis();
                if (button_time - last_button_time > 250)
                {
                    last_button_time = button_time;
                    exitLoop = true;
                }
            }
        }

        last_button_time = 0;
        debugpln("Determine zero weight offset");
        LcdDisplay::displayMsg("Determine zero weight offset", 0, 20);
        //  average 20 measurements.
        scale.tare(20);
        int32_t offset = scale.get_offset();

        debugp("OFFSET: ");
        debugpln(offset);
        debugpln();
        LcdDisplay::displayMsg("Offset: ", 0, 30);
        debugpln("Place a weight on the scale then press the Calibrate Button when ready");
        LcdDisplay::displayMsg("Place a weight on the scale then press the Calibrate Button when ready", 0, 20);

        exitLoop = false;
        while (exitLoop == false)
        {
            buttonState = digitalRead(CALABRATE_BUTTON);

            if (buttonState == HIGH)
            {
                button_time = millis();
                if (button_time - last_button_time > 250)
                {
                    last_button_time = button_time;
                    exitLoop = true;
                }
            }
        }

        last_button_time = 0;
        debugpln("Enter the weight in (whole) grams by pressing the Calibrate Button (+10)");
        LcdDisplay::displayMsg("Enter the weight in (whole) grams by pressing the Calibrate Button (+10)", 0, 20);
        LcdDisplay::displayMsg("Press the Tare Button When finished", 0, 40);
        uint32_t weight = 0;

        while (digitalRead(TARE_BUTTON) == 0)
        {
            buttonState = digitalRead(CALABRATE_BUTTON);

            if (buttonState == HIGH)
            {
                button_time = millis();
                if (button_time - last_button_time > 250)
                {
                    weight += 10;
                    if (weight > 100)
                    {
                        weight = 0;
                    }
                    debugpln("Weight: " + weight);
                    LcdDisplay::displayMsg((String)weight + " g", 0, 20);
                    last_button_time = button_time;
                }
            }
        }
        debugp("WEIGHT: ");
        debugpln(weight);
        LcdDisplay::displayMsg("Calibration weight: " + (String)weight, 0, 20);

        scale.calibrate_scale(weight, 20);
        float scaleFactor = scale.get_scale();

        debugp("SCALE:  ");
        debugpln(scaleFactor, 6);

        // Saves Scale Calibration Settings
        appPrefs.begin("scalePrefs", false);
        appPrefs.putFloat("scale", scaleFactor);
        appPrefs.putInt("offset", offset);
        if (appPrefs.isKey("scale"))
        {
            if (appPrefs.getFloat("scale") == scaleFactor)
            {
                debugpln("Calibration Data Saved");
            }
        }
        else
        {
            debugpln("Error saving Calibration Data");
        }
        appPrefs.end();

        debugp("\nuse scale.set_offset(");
        debugp(offset);
        debugp("); and scale.set_scale(");
        debugp(scaleFactor, 6);
        debugp(");\n");
        debugpln("in the setup of your project");
        LcdDisplay::displayMsg("scale.set_offset(" + (String)offset + ") scale.set_scale(" + (String)scaleFactor + ")", 10, 30);
        debugpln("\n\n");
        delay(3000);
        LcdDisplay::displayClear();
        LcdDisplay::displayMsg(DISPLAY_TITLE,0,0);
    } // void buttonCalibrateScale()

    void readNFC()
    {
        debugpln("Waiting for NFC tag...");
        uint8_t uid[] = {0};
        uint8_t uidLength;

        if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength))
        {
            debugp("Found NFC tag with UID: ");
            for (uint8_t i = 0; i < uidLength; i++)
            {
                Serial.print(uid[i], HEX);
                debugp(" ");
            }
            debugpln();
        }
    } //  void readNFC()

} // namespace Hardware