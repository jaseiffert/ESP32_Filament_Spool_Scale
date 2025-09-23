## ESP32 Filament Scale

I did the project code using Visual Studio Code and pioarduino to use the latest version of Arduino core for the ESP32 (version 3).

The include/configuration.h file has some of the settings needed to be set for the program.

The include/hardware.h file has the pins for the GPIO's used. If you use different pins they will need to be changed here.

The include/secrets.h has all the passwords that need to be set.

Currently it is stand alone and WiFi is not active and neither is the NFC Reader.

The Wifi and NFC code is in the code but disabled at the moment.
<br>

### Operation:

First time you will have to calibrate the scale with a known weight. 10g to 100g.

Press and hold the Calibrate button till the screen changes.
> Remove all weight from scale
> 
> Press Calibrate Button when ready
 
Press Calibrate button.

> Determine zero weight offset
> Offset: 
>
> Place a weight on the scale then press the Calibrate Button when ready
 
Press Calibrate button.

> Enter the weight in (whole) grams by pressing the Calibrate Button (+10)

(Weight starts with 10)

> Weight: 10 (press the calibrate button to add 10g each time to get to the size of the known weight)

(If you have a 50g weight then press it 4 times to get to 50)

Press Tare button to select the weight displayed.

> Calibration weight: 50
	
There will be a delay as it calculates the calibration data and will display some data before going back to measuring weight. It should be 0 G when it's done or 50 G if you left the test weight on the scale.

If you mess up just try it again.

While you shouldn't need the Tear button once calibrated if you use the scale for something else it may come in handy to zero a container that you want to measure the contents.

The calibration data should be saved in memory so it should be good when you turn it back on.

Normal Operation once calibrated is place weight on scale and give it a few seconds to settle to the weight. Anything over 100g will not show only whole numbers, no decimal places. Mine does jump around a bit by .2 - .3 g. Not sure why.

