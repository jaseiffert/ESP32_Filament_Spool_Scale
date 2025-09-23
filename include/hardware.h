#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <Preferences.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_PN532.h>
#include "HX711.h"

#include "globals.h"
#include "utilities.h"
#include "wifi_helper.h"

// Define I2C pins (default for ESP32)
// You can change these if needed, but GPIO 21 and 22 are common defaults.
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

// HX711 Load Cell Pins
#define HX711_DATA 18
#define HX711_CLK 5


// Load Cell Max Load, 1kg, 2kg, 5kg, 10kg, 20kg
#define LOAD_CELL 5

#define TARE_BUTTON 26
#define CALABRATE_BUTTON 25

extern Preferences appPrefs;
// Create an instance of the prepared class.

namespace Hardware
{
    // Methods
    void setupHardware();

    void readScale();

    void calibrateScale();

    void tareScale();

    void buttonCalibrateScale();

    void readNFC();

} // namespace Hardware

#endif
