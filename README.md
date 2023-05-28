# LCD1602-I2C-Util
Arduino code for LCD 1602 character display including loading bar class, custom character generation tool, and example code. 
This repo is intended to help jump start projects using Arduino with an LCD character display over I2C.

Requires the https://github.com/johnrickman/LiquidCrystal_I2C library be installed in Arduino IDE.

Developed and tested with an Arduino Uno and a 16x2 character LCD module with an I2C backpack.

# Example Code
LiquidCrystal_I2C_Test.ino contains a series of small demos using different features of the LiquidCrystal_I2C library. 

The progress bar shown in the demo is contained in a separate class for easy portability.

The custom smily face in the demo was generated with bitmapper.py with the following command.

`python bitmapper.py -i smile.jpg -n smile`

# Bitmapper.py
Requires opencv2 and numpy
