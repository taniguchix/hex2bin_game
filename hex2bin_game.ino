// HEX2BIN GAME
// taniguchi kotaro
// https://www.youtube.com/c/kotarotaniguchix
#include <EEPROM.h>
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 display;
ArduboyPlaytune tunes(display.audio.enabled);

void setup() {
  display.begin();

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
  // if not a DevKit
  tunes.initChannel(PIN_SPEAKER_2);
#else
  // if it's a DevKit
  tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
  tunes.toneMutesScore(true);       // mute the score when a tone is sounding
#endif
}

#define EEPROM_SCORES EEPROM_STORAGE_SPACE_START

#define ONPU_HI_16    0
#define ONPU_LO_16   64
#define ONPU_HI_8     0
#define ONPU_LO_8   128
#define ONPU_HI_53    0
#define ONPU_LO_53  192
#define ONPU_HI_4     1
#define ONPU_LO_4     0
#define ONPU_HI_26    1
#define ONPU_LO_26  128
#define ONPU_HI_2     2
#define ONPU_LO_2     0
#define ONPU_HI_1     4
#define ONPU_LO_1     0

PROGMEM const byte saruoto_11 [] = {
  0x90, 74, ONPU_HI_8, ONPU_LO_8,
  0x90, 79, ONPU_HI_4, ONPU_LO_4,
  0x90, 76, ONPU_HI_8, ONPU_LO_8,
  0x90, 78, ONPU_HI_53, ONPU_LO_53,
  0x90, 74, ONPU_HI_53, ONPU_LO_53,
  0x90, 81, ONPU_HI_8, ONPU_LO_8,
  0x90, 79, ONPU_HI_1, ONPU_LO_1,
  0x80, 0xf0
};

PROGMEM const unsigned char bmp_input[16 + 2][51] = {
  {
    0x80, 0xe0, 0x78, 0x1c, 0x06, 0x06, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x06, 0x0e, 0x1c, 0xf8, 0xe0,
    0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x03, 0x0f, 0x1c, 0x38, 0x30,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30, 0x1c,
    0x0f, 0x03, 0x00,
  },
  {
    0x00, 0x00, 0x00, 0xc0, 0xe0, 0x70, 0x30, 0x38,
    0x1c, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60,
  },
  {
    0x00, 0x00, 0x70, 0x7c, 0x0e, 0x06, 0x07, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x06, 0x06, 0x1c, 0xf8,
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1e,
    0x0f, 0x03, 0x00, 0x60, 0x70, 0x78, 0x78, 0x7c,
    0x6e, 0x67, 0x63, 0x63, 0x61, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60,
  },
  {
    0x00, 0x10, 0x38, 0x1c, 0x0e, 0x06, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x07, 0x06, 0x0e, 0xfc, 0xf0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0e, 0x1e, 0x3f, 0x73,
    0xe0, 0xc0, 0x04, 0x0e, 0x1c, 0x38, 0x30, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30,
    0x1c, 0x0f, 0x07,
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0,
    0x78, 0x1e, 0x07, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xe0, 0x70, 0x1c, 0x0f, 0x03,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x7f, 0x7f, 0x03,
    0x03, 0x03, 0x03,
  },
  {
    0x00, 0xc0, 0xff, 0x3f, 0x03, 0x03, 0x83, 0x83,
    0x83, 0x83, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x00, 0x0f, 0x0f, 0x06, 0x07, 0x03, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x0e,
    0xfc, 0xf0, 0x04, 0x0e, 0x1c, 0x38, 0x30, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30, 0x18,
    0x1e, 0x0f, 0x03,
  },
  {
    0x00, 0x00, 0xe0, 0xf8, 0x1c, 0x0e, 0x06, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x0e, 0x1c,
    0x08, 0x00, 0xff, 0xff, 0xf0, 0x1c, 0x0e, 0x06,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x0e, 0x1c,
    0xf8, 0xe0, 0x00, 0x00, 0x07, 0x0f, 0x1c, 0x30,
    0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x38,
    0x1c, 0x0f, 0x03,
  },
  {
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x83, 0xe3, 0x73, 0x3b, 0x0f, 0x07, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
    0xf8, 0x3e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c,
    0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
  },
  {
    0x00, 0xf0, 0xfc, 0x8e, 0x06, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x06, 0x8e, 0xfc, 0xf8,
    0x00, 0x80, 0xc0, 0x63, 0x37, 0x17, 0x1e, 0x0e,
    0x0c, 0x0c, 0x0c, 0x1e, 0x1e, 0x3b, 0x3b, 0x71,
    0xe0, 0x80, 0x07, 0x1f, 0x18, 0x30, 0x30, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30,
    0x18, 0x0f, 0x07,
  },
  {
    0xe0, 0xf8, 0x1c, 0x0e, 0x06, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x06, 0x06, 0x0c, 0xf8, 0xf0,
    0x80, 0x03, 0x0f, 0x1c, 0x38, 0x30, 0x70, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x30, 0x38, 0x1c, 0x8f,
    0xff, 0x7f, 0x00, 0x08, 0x1c, 0x38, 0x30, 0x70,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x38, 0x1c,
    0x0f, 0x03, 0x00,
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x3f,
    0x07, 0x3f, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xf0, 0xfe, 0xcf, 0xc1,
    0xc0, 0xc0, 0xc0, 0xc1, 0xcf, 0xfe, 0xf0, 0x80,
    0x00, 0x00, 0x60, 0x7c, 0x1f, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x1f, 0x7c, 0x60,
  },
  {
    0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x07, 0x0e, 0xfc, 0xf8,
    0x00, 0x00, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1a, 0x1b, 0x71,
    0xe0, 0xc0, 0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30,
    0x38, 0x1f, 0x07,
  },
  {
    0x00, 0x00, 0xe0, 0xf0, 0x38, 0x0c, 0x0c, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x0c, 0x1c, 0x78, 0xf0,
    0xc0, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1c, 0x38,
    0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x38,
    0x1e, 0x0f, 0x03,
  },
  {
    0x00, 0xfe, 0xfe, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x0e, 0x0c, 0x1c, 0x38, 0xf0, 0xc0,
    0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x70, 0x30, 0x38, 0x1c,
    0x0f, 0x03, 0x00,
  },
  {
    0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x00, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x00,
  },
  {
    0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
  },
  { //x
    0x00, 0x00, 0x10, 0x30, 0xe0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0xe0, 0x30, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xf7,
    0x3e, 0x3e, 0xf7, 0xc1, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x18, 0x0e, 0x07, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0e, 0x18,
    0x10, 0x00, 0x00,
  },
  { //点
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
  }
};

PROGMEM const unsigned char menu_cursol [] = {
  0b00111110,
  0b00011100,
  0b00001000,
};

enum game_state {
  state_help,
  state_menu,
  state_high_score,
  state_game,
  state_game_aft
};
enum game_state state = state_menu;

bool now_push = false;
bool now_push_b = false;

int input_cur = 0;
int input_bin[4] = {17, 17, 17, 17};
const int mondai_level[6][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15},
  {3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 12, 12, 12, 12, 12, 12},
  {5, 5, 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10, 10, 10},
  {1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8},
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
};
int mondai_hex[100] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int mondai_cur = 0;
const int mondai_max[6] = {10, 10, 10, 10, 10, 100};

bool start_flag = false;
int count_time = 0;
bool miss_flag = false;
int count = 0;

int level = 0;
int level_max = 1;
bool sound = true;
bool hi_score_update = false;
bool level_update = false;
int menu_select = 0;
unsigned int hi_score[6] = {0};

int help_count = 0;

unsigned long currTime;
unsigned long prevTime = 0;
#define FPSDELAY      1000/30

void loop() {

  bool data_reset = false;

  for (int i = 0; i < 6; i++) {
    hi_score[i] = EEPROM.read(i * 2 + EEPROM_SCORES);
    hi_score[i] <<= 8;
    hi_score[i] += EEPROM.read(i * 2 + 1 + EEPROM_SCORES);
    if (hi_score[i] > 1000) {
      data_reset = true;
      break;
    }
  }
  level_max = EEPROM.read(6 * 2 + EEPROM_SCORES);
  if (level_max > 6) {
    data_reset = true;
  }
  //data_reset = true;
  if (data_reset) {
    for (int i = 0; i < 6; i++) {
      hi_score[i] = 1000;
      EEPROM.update(i * 2 + EEPROM_SCORES,   ((hi_score[i]) >> 8 & 0xFF));
      EEPROM.update(i * 2 + 1 + EEPROM_SCORES, hi_score[i] & 0xFF);
    }
    level_max = 1;
    EEPROM.update(6 * 2 + EEPROM_SCORES, level_max & 0xFF);
  }
  level = level_max - 1;
  if (level > 4) {
    level = 4;
  }

  while (true) {
    currTime = millis();
    if ( currTime > prevTime + FPSDELAY ) {
      prevTime = currTime;
      byte input = display.buttonsState();
      display.clear();
      switch (state) {
        case state_help:
          if (input & (A_BUTTON | B_BUTTON)) {
            now_push = true;
          } else {
            if (now_push) {
              state = state_menu;
              now_push = false;
            }
          }
          if (level_max > 4) {
            display.setCursor(22, 0);     display.print(F("0=0000  8=1000"));
            display.setCursor(22, 8);     display.print(F("1=0001  9=1001"));
            display.setCursor(22, 8 * 2); display.print(F("2=0010  A=1010"));
            display.setCursor(22, 8 * 3); display.print(F("3=0011  B=1011"));
            display.setCursor(22, 8 * 4); display.print(F("4=0100  C=1100"));
            display.setCursor(22, 8 * 5); display.print(F("5=0101  D=1101"));
            display.setCursor(22, 8 * 6); display.print(F("6=0110  E=1110"));
            display.setCursor(22, 8 * 7); display.print(F("7=0111  F=1111"));
          } else {
            display.setCursor(22, 0);     display.print(F("0=0000  F=1111"));
            if (level_max > 1) {
              display.setCursor(22, 8);
              display.print(F("3=0011  C=1100"));
            }
            if (level_max > 2) {
              display.setCursor(22, 8 * 2);
              display.print(F("5=0101  A=1010"));
            }
            if (level_max > 3) {
              display.setCursor(22, 8 * 3); display.print(F("1=0001"));
              display.setCursor(22, 8 * 4); display.print(F("2=0010"));
              display.setCursor(22, 8 * 5); display.print(F("3=0100"));
              display.setCursor(22, 8 * 6); display.print(F("4=1000"));
            }
          }
          break;
        case state_menu:
          help_count++;
          if (help_count > 150) {
            help_count = 0;
            state = state_help;
            break;
          }
          if (input & (LEFT_BUTTON | RIGHT_BUTTON | UP_BUTTON | DOWN_BUTTON)) {
            help_count = 0;
            if (!now_push) {
              if (input & UP_BUTTON    && menu_select > 0) menu_select--;
              if (input & DOWN_BUTTON  && menu_select < 3) menu_select++;
              switch (menu_select) {
                case 0:
                  if (input & (LEFT_BUTTON | RIGHT_BUTTON)) level++;
                  if (level >= level_max) level = 0;
                  break;
                case 1:
                  if (input & (LEFT_BUTTON | RIGHT_BUTTON)) sound = !sound;
                  break;
              }
              now_push = true;
            }
          } else {
            now_push = false;
          }
          if (input & B_BUTTON) {
            help_count = 0;
            now_push_b = true;
          } else {
            if (now_push_b) {
              switch (menu_select) {
                case 0:
                case 1:
                  input_cur = 0;
                  input_bin[0] = 17;
                  input_bin[1] = 17;
                  input_bin[2] = 17;
                  input_bin[3] = 17;
                  mondai_cur = 0;
                  start_flag = false;
                  miss_flag = false;
                  count_time = 0;
                  randomSeed(currTime & 0xFF);
                  for (int i = 0; i < mondai_max[level]; i++) {
                    mondai_hex[i] = mondai_level[level][random(255) % 16];
                  }
                  state = state_game;
                  break;
                case 2:
                  state = state_high_score;
                  break;
                case 3:
                  state = state_help;
                  break;
                }
              now_push_b = false;
            }
          }
          display.setCursor(28, 8);  display.print(F("HEX2BIN GAME"));
          display.setCursor(28, 24); display.print(F("LEVEL:"));
          switch (level) {
            case 0: display.print(F("0/F")); break;
            case 1: display.print(F("3/C")); break;
            case 2: display.print(F("5/A")); break;
            case 3: display.print(F("1/2/4/8")); break;
            case 4: display.print(F("ALL")); break;
            case 5: display.print(F("ALL64")); break;
          }
          display.setCursor(28, 32); display.print(F("SOUND:"));
          if (sound) display.print(F("ON"));
          else       display.print(F("OFF"));
          display.setCursor(28, 48); display.print(F("HIGH SCORE"));
          display.setCursor(28, 56); display.print(F("HELP"));
          if (menu_select < 2) {
            display.drawBitmap(23, 24 + menu_select * 8, menu_cursol, 3, 8, 1);
          } else {
            display.drawBitmap(23, 32 + menu_select * 8, menu_cursol, 3, 8, 1);
          }
          break;
        case state_high_score:
          if (input & A_BUTTON) {
            state = state_menu;
            break;
          }
          display.setCursor(35, 0); display.print(F("HIGH SCORE"));
          display.setCursor(28, 15); display.print(F("0/F     :")); if (hi_score[0] < 1000) display.print(hi_score[0]);
          if (level_max > 1) {
            display.setCursor(28, 15 + 8);
            display.print(F("3/C     :"));
            if (hi_score[1] < 1000) display.print(hi_score[1]);
          }
          if (level_max > 2) {
            display.setCursor(28, 15 + 8 * 2);
            display.print(F("5/A     :"));
            if (hi_score[2] < 1000) display.print(hi_score[2]);
          }
          if (level_max > 3) {
            display.setCursor(28, 15 + 8 * 3);
            display.print(F("1/2/4/8 :"));
            if (hi_score[3] < 1000) display.print(hi_score[3]);
          }
          if (level_max > 4) {
            display.setCursor(28, 15 + 8 * 4);
            display.print(F("ALL     :"));
            if (hi_score[4] < 1000) display.print(hi_score[4]);
          }
          if (level_max > 5) {
            display.setCursor(28, 15 + 8 * 5);
            display.print(F("ALL64   :"));
            if (hi_score[5] < 1000) display.print(hi_score[5]);
          }
          break;
        case state_game:
          if (input & A_BUTTON) {
            if (!now_push) {
              now_push = true;
              input_bin[input_cur] = 0;
              if (start_flag == false) {
                start_flag = true;
                count = 0;
              }
            }
          } else if (input & B_BUTTON) {
            if (!now_push) {
              now_push = true;
              input_bin[input_cur] = 1;
              if (start_flag == false) {
                start_flag = true;
                count = 0;
              }
            }
          } else {
            if (now_push) {
              now_push = false;
              if (((mondai_hex[mondai_cur] >> (3 - input_cur)) & 1) != input_bin[input_cur]) {
                input_bin[input_cur] = 16;
                count_time += 10; //ペナルティ
                if (count_time >= 999) {
                  count_time = 999;
                }
                miss_flag = true;
                if (sound) tunes.tone(1046, 250);
              } else {
                input_cur++;
                if (input_cur >= 4) {
                  input_bin[0] = 17;
                  input_bin[1] = 17;
                  input_bin[2] = 17;
                  input_bin[3] = 17;
                  input_cur = 0;
                  mondai_cur++;
                }
                if (mondai_cur >= mondai_max[level]) {
                  if (sound) tunes.playScore(saruoto_11);
                  if (hi_score[level] > count_time) {
                    hi_score[level] = count_time;
                    hi_score_update = true;
                    EEPROM.update(level * 2 + EEPROM_SCORES,   ((hi_score[level]) >> 8 & 0xFF));
                    EEPROM.update(level * 2 + 1 + EEPROM_SCORES, hi_score[level] & 0xFF);
                    if (!miss_flag && level + 1 == level_max && level_max < 6) {
                      level_update = true;
                      EEPROM.update(6 * 2 + EEPROM_SCORES, (level_max + 1) & 0xFF);
                    }
                  }
                  state = state_game_aft;//クリア
                  break;
                }
              }
            }
          }
          display.setCursor(0, 0);  display.print(mondai_cur); display.print(F("/")); display.print(mondai_max[level]);
          display.setCursor(80, 0);  display.print(F("TIME:")); display.print(count_time);

          display.drawBitmap(12, 25, bmp_input[mondai_hex[mondai_cur]], 17, 23, 1);
          display.setCursor(38, 25 + 8);  display.print(F("="));
          display.drawBitmap(12 + 22 + 17  , 25, bmp_input[input_bin[0]], 17, 23, 1);
          display.drawBitmap(12 + 22 + 17 * 2, 25, bmp_input[input_bin[1]], 17, 23, 1);
          display.drawBitmap(12 + 22 + 17 * 3, 25, bmp_input[input_bin[2]], 17, 23, 1);
          display.drawBitmap(12 + 22 + 17 * 4, 25, bmp_input[input_bin[3]], 17, 23, 1);
          if (start_flag) {
            count++;
            if (count >= 30) {
              count = 0;
              if (count_time < 999) {
                if (sound) {
                  if (!tunes.playing()) tunes.tone(523, 100);
                }
                count_time++;
              }
            }
          }
          break;
        case state_game_aft:
          if (!tunes.playing()) {
            if (input & (A_BUTTON | B_BUTTON)) {
              now_push = true;
            } else {
              if (now_push) {
                now_push = false;
                if (hi_score_update) hi_score_update = false;
                else {
                  if (level_update) {
                    level_max++;
                    level = level_max - 1;
                    level_update = false;
                  }
                  state = state_high_score;
                  break;
                }
              }
            }
          }
          display.setCursor(0, 0);  display.print(mondai_cur); display.print(F("/")); display.print(mondai_max[level]);
          display.setCursor(80, 0);  display.print(F("TIME:")); display.print(count_time);
          if (hi_score_update) {
            display.setCursor(5, 30);   display.print(F("HIGH SCORE UPDATE !!"));
          } else {
            if (miss_flag) {
              display.setCursor(35, 30); display.print(F("GOOD JOB !!"));
            } else {
              display.setCursor(40, 30); display.print(F("PERFECT !!"));
            }
            if (level_update) {
              display.setCursor(5, 38); display.print(F("NEW LEVEL UNLOCKED!!"));
            }
          }
          break;
      }
      display.display();
    }
  }
}

