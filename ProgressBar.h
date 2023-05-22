#ifndef __PROGRESS_BAR_H__
#define __PROGRESS_BAR_H__

#include <LiquidCrystal_I2C.h>

#define SECTION_SIZE 5
#define MIDDLE_SECTION_0 0
#define MIDDLE_SECTION_1 1
#define MIDDLE_SECTION_2 2
#define MIDDLE_SECTION_3 3
#define MIDDLE_SECTION_4 4
#define MIDDLE_SECTION_5 5
#define LEFT_END 6
#define RIGHT_END 7

uint8_t load_bar_left_end[8] = {
                        0b00000111,
                        0b00000110,
                        0b00000110,
                        0b00000110,
                        0b00000110,
                        0b00000110,
                        0b00000110,
                        0b00000111,
                      };
                    
uint8_t load_bar_middle_0[8] = {
                        0b00011111,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_middle_1[8] = {
                        0b00011111,
                        0b00000000,
                        0b00010000,
                        0b00010000,
                        0b00010000,
                        0b00010000,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_middle_2[8] = {
                        0b00011111,
                        0b00000000,
                        0b00011000,
                        0b00011000,
                        0b00011000,
                        0b00011000,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_middle_3[8] = {
                        0b00011111,
                        0b00000000,
                        0b00011100,
                        0b00011100,
                        0b00011100,
                        0b00011100,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_middle_4[8] = {
                        0b00011111,
                        0b00000000,
                        0b00011110,
                        0b00011110,
                        0b00011110,
                        0b00011110,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_middle_5[8] = {
                        0b00011111,
                        0b00000000,
                        0b00011111,
                        0b00011111,
                        0b00011111,
                        0b00011111,
                        0b00000000,
                        0b00011111,
                      };

uint8_t load_bar_right_end[8] = {
                        0b00011100,
                        0b00001100,
                        0b00001100,
                        0b00001100,
                        0b00001100,
                        0b00001100,
                        0b00001100,
                        0b00011100,
                      };

class ProgressBar {

  private:
    uint8_t number_of_middle_sections;
    uint8_t column;
    uint8_t row;
    LiquidCrystal_I2C* lcd;

    void LoadCustomCharacters() {
      this->lcd->createChar(MIDDLE_SECTION_0, load_bar_middle_0);
      this->lcd->createChar(MIDDLE_SECTION_1, load_bar_middle_1);
      this->lcd->createChar(MIDDLE_SECTION_2, load_bar_middle_2);
      this->lcd->createChar(MIDDLE_SECTION_3, load_bar_middle_3);
      this->lcd->createChar(MIDDLE_SECTION_4, load_bar_middle_4);
      this->lcd->createChar(MIDDLE_SECTION_5, load_bar_middle_5);
      this->lcd->createChar(LEFT_END, load_bar_left_end);
      this->lcd->createChar(RIGHT_END, load_bar_right_end);
    }

  public:
    ProgressBar(LiquidCrystal_I2C* lcd, uint8_t column, uint8_t row, uint8_t sections)
    {
      this->lcd = lcd;
      this->number_of_middle_sections = sections;
      this->column = column;
      this->LoadCustomCharacters();
    }

    void SetProgressIndex(uint8_t progress_index) {

      uint8_t full_sections = progress_index / SECTION_SIZE;
      uint8_t leftover_sections = progress_index % SECTION_SIZE;

      this->lcd->setCursor(this->column, this->row);
      this->lcd->write(LEFT_END);
      for (uint8_t section = 0; section < number_of_middle_sections; section++) {
        if (section < full_sections) {
          this->lcd->write(MIDDLE_SECTION_5);
        } else if (section == full_sections) {
          this->lcd->write(leftover_sections);
        } else {
          this->lcd->write(MIDDLE_SECTION_0);
        }
      }
      this->lcd->write(RIGHT_END);
    }
};

#endif