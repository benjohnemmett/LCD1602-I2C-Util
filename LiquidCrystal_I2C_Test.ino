#include <LiquidCrystal_I2C.h>
#include "CustomSymbols.h"
#include "ProgressBar.h"

#define LCD_ADDRESS 0x27
#define COLUMNS 16
#define ROWS 2
#define PIXEL_COLS_PER_CELL 5

LiquidCrystal_I2C lcd(LCD_ADDRESS, COLUMNS, ROWS);

void setup()
{
  lcd.init();
  lcd.backlight();

  demoTwoLinePrint();
  demoToggleDisplay();
  demoToggleBacklight();
  demoCursorOptions();
  demoScroll();
  demoPrintDirections();
  demoCustomChars();
  demoProgressBarClass();
}

void loop()
{ 
}

void demoTwoLinePrint() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("First Line");
  delay(800);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Second Line");
  delay(800);
}

void demoToggleDisplay() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Toggle");
  lcd.setCursor(0,1);
  lcd.print("Display");
  for (uint8_t i = 0; i < 3; i++) {
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
  }
}

void demoToggleBacklight() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Toggle");
  lcd.setCursor(0,1);
  lcd.print("Backlight");
  for (uint8_t i = 0; i < 3; i++) {
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(500);
  }
}

void demoCursorOptions() {
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("With cursor");
  lcd.cursor();
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.blink();
  lcd.print("Blinking cursor");
  delay(2000);
  lcd.clear();

  lcd.noBlink();
  lcd.setCursor(0,1);
  lcd.print("No Cursor");
  lcd.noCursor();
  delay(2000);
}

void demoScroll() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scroll Right");
  for (uint8_t i = 0; i < 5; i++) {
    lcd.scrollDisplayRight();
    delay(300);
  }
  lcd.clear();

  lcd.setCursor(6, 1);
  lcd.print("Scroll Left");
  for (uint8_t i = 0; i < 5; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.clear();
}

void demoPrintDirections() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Left to Right");
  lcd.setCursor(13, 1);
  lcd.rightToLeft();
  lcd.print("Right To Left");
  delay(2000);
  lcd.clear();
}

void demoCustomChars() {
  lcd.clear();
  lcd.createChar(0, checker);
  lcd.createChar(1, box);
  lcd.createChar(2, whale1);
  lcd.createChar(3, whale2);
  
  lcd.home();
  lcd.print("Whale - ");
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.print("Box - ");
  lcd.write(1);
  delay(1000);
}

void demoProgressBarClass() {
  uint8_t bar_column = 2;
  uint8_t bar_row = 1;
  uint8_t bar_sections = 10;
  ProgressBar bar(&lcd, bar_column, bar_row, bar_sections);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Loading...");
  for (uint8_t index = 0; index <= bar_sections * PIXEL_COLS_PER_CELL;index++) {
    bar.SetProgressIndex(index);
    delay(100);
  }
  delay(1000);
}
