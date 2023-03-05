/*

Runner Click Tracker

  #       #             
 *#*     *#*         
**#**   **#**        
 #** #   #** #        
  * *#*   * *#*      
   **#**   **#**        
    #**     #**         
     *       *       

Corp Click Tracker

  *#        *#  
 **#*      **#*
***#** *# ***#**
**#*****#***#***
 #******#**#***
  ** **#*** **
      #***
       **
*/

#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Fonts/Picopixel.h>

Adafruit_BicolorMatrix displays[2] = { Adafruit_BicolorMatrix(), Adafruit_BicolorMatrix() };

static const uint8_t PROGMEM
  runner_click0_d1_green[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click0_d2_green[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click0_d1_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click0_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click0_d1_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },
  runner_click0_d2_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },

  runner_click1_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click1_d2_green[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click1_d1_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00100000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click1_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click1_d1_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },
  runner_click1_d2_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },

  runner_click2_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click2_d2_green[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click2_d1_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click2_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click2_d1_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },
  runner_click2_d2_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },

  runner_click3_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click3_d2_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click3_d1_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click3_d2_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00100000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click3_d1_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },
  runner_click3_d2_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },

  runner_click4_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click4_d2_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click4_d1_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click4_d2_red[] =
    { B00000000,
      B01010000,
      B11011000,
      B00110000,
      B00101010,
      B00011011,
      B00000110,
      B00000100 },
  runner_click4_d1_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },
  runner_click4_d2_yellow[] =
    { B00100000,
      B00100000,
      B00100000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00000000 },

  corp_click0_d1_green[] =
    { B00100000,
      B01101000,
      B11101101,
      B11011111,
      B00111111,
      B00110110,
      B00000001,
      B00000001 },
  corp_click0_d2_green[] =
    { B00001000,
      B00011010,
      B00111011,
      B01110111,
      B01101110,
      B11101100,
      B11000000,
      B10000000 },
  corp_click0_d1_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click0_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click0_d1_yellow[] =
    { B00010000,
      B00010000,
      B00010000,
      B00100000,
      B01000000,
      B00000001,
      B00000010,
      B00000000 },
  corp_click0_d2_yellow[] =
    { B00000100,
      B00000100,
      B10000100,
      B10001000,
      B10010000,
      B00000000,
      B00000000,
      B00000000 },

  corp_click1_d1_green[] =
    { B00000000,
      B00000000,
      B00000001,
      B00000011,
      B00000111,
      B00000110,
      B00000001,
      B00000001 },
  corp_click1_d2_green[] =
    { B00001000,
      B00011010,
      B00111011,
      B01110111,
      B01101110,
      B11101100,
      B11000000,
      B10000000 },
  corp_click1_d1_red[] =
    { B00100000,
      B01101000,
      B11101100,
      B11011100,
      B00111000,
      B00110000,
      B00000000,
      B00000000 },
  corp_click1_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click1_d1_yellow[] =
    { B00010000,
      B00010000,
      B00010000,
      B00100000,
      B01000000,
      B00000001,
      B00000010,
      B00000000 },
  corp_click1_d2_yellow[] =
    { B00000100,
      B00000100,
      B10000100,
      B10001000,
      B10010000,
      B00000000,
      B00000000,
      B00000000 },

  corp_click2_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click2_d2_green[] =
    { B00001000,
      B00011010,
      B00111011,
      B00110111,
      B00001110,
      B00001100,
      B00000000,
      B00000000 },
  corp_click2_d1_red[] =
    { B00100000,
      B01101000,
      B11101101,
      B11011111,
      B00111111,
      B00110110,
      B00000001,
      B00000001 },
  corp_click2_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B01000000,
      B01100000,
      B11100000,
      B11000000,
      B10000000 },
  corp_click2_d1_yellow[] =
    { B00010000,
      B00010000,
      B00010000,
      B00100000,
      B01000000,
      B00000001,
      B00000010,
      B00000000 },
  corp_click2_d2_yellow[] =
    { B00000100,
      B00000100,
      B10000100,
      B10001000,
      B10010000,
      B00000000,
      B00000000,
      B00000000 },

  corp_click3_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click3_d2_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
  corp_click3_d1_red[] =
    { B00100000,
      B01101000,
      B11101101,
      B11011111,
      B00111111,
      B00110110,
      B00000001,
      B00000001 },
  corp_click3_d2_red[] =
    { B00001000,
      B00011010,
      B00111011,
      B01110111,
      B01101110,
      B11101100,
      B11000000,
      B10000000 },
  corp_click3_d1_yellow[] =
    { B00010000,
      B00010000,
      B00010000,
      B00100000,
      B01000000,
      B00000001,
      B00000010,
      B00000000 },
  corp_click3_d2_yellow[] =
    { B00000100,
      B00000100,
      B10000100,
      B10001000,
      B10010000,
      B00000000,
      B00000000,
      B00000000 };

#define BUTTON_COUNT 2

// states
#define INIT 0
#define RUNNER 1
#define CORP 2

int currentClick = 0;
int state = INIT;
const int btnPin[BUTTON_COUNT] = { 9, 8 };
int btn[BUTTON_COUNT] = {0,0};
bool btnpressedLastVal[BUTTON_COUNT] = {false,false};
bool btnpressed[BUTTON_COUNT] = {false,false};


void setup() {
  Serial.begin(9600);
  displays[0].begin(0x71);
  displays[1].begin(0x70);

  Serial.print("Ready, on 9600");

  for (int i = 0, l = 2; i < l; i++) {
    displays[i].setFont(&Picopixel);
    displays[i].setTextWrap(false);
    displays[i].setTextSize(1);
    displays[i].setRotation(3);
  }

  _init();
}

void clearDisplays() {
  for (int i = 0; i < 2; i++) {
    displays[i].clear();
    displays[i].writeDisplay();
  }
}

const int debounceDelay = 200;
void handleButtons() {

  for (int i = 0, l = BUTTON_COUNT; i < l; i++) {
    btn[i] = digitalRead(btnPin[i]);

    if (!btnpressed[i] && btn[i] == HIGH) {
        /* Serial.print("PRESSED "); */
        /* Serial.println(i); */
        btnpressed[i] = true;
        if (state == CORP) {
          handleButtonCorp(i);
        } else if (state == RUNNER) {
          handleButtonRunner(i);
        }
    } else if(btnpressed[i] && btn[i] == LOW){
        btnpressed[i] = false;
        delay(debounceDelay);
    }

  }

}

void handleButtonCorp(int btnId) {
  switch (btnId) {
    case 0: return ;
    case 1: return ;
  }
}

void handleButtonRunner(int btnId) {
  switch (btnId) {
    case 0: return ;
    case 1: return ;
  }
}

void _init() {

}

void loop() {
//   handleButtons();


  displays[0].clear();
  displays[0].drawBitmap(0, 0, runner_click0_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, runner_click0_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, runner_click0_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();

  displays[1].clear();
  displays[1].drawBitmap(0, 0, runner_click0_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, runner_click0_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, runner_click0_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, runner_click1_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, runner_click1_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, runner_click1_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();

  displays[1].clear();
  displays[1].drawBitmap(0, 0, runner_click1_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, runner_click1_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, runner_click1_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, runner_click2_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, runner_click2_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, runner_click2_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();

  displays[1].clear();
  displays[1].drawBitmap(0, 0, runner_click2_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, runner_click2_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, runner_click2_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, runner_click3_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, runner_click3_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, runner_click3_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();

  displays[1].clear();
  displays[1].drawBitmap(0, 0, runner_click3_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, runner_click3_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, runner_click3_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, runner_click4_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, runner_click4_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, runner_click4_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();

  displays[1].clear();
  displays[1].drawBitmap(0, 0, runner_click4_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, runner_click4_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, runner_click4_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[1].clear();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, corp_click0_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, corp_click0_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, corp_click0_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();


  displays[1].clear();
  displays[1].drawBitmap(0, 0, corp_click0_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, corp_click0_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, corp_click0_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, corp_click1_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, corp_click1_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, corp_click1_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();


  displays[1].clear();
  displays[1].drawBitmap(0, 0, corp_click1_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, corp_click1_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, corp_click1_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, corp_click2_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, corp_click2_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, corp_click2_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();


  displays[1].clear();
  displays[1].drawBitmap(0, 0, corp_click2_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, corp_click2_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, corp_click2_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[0].drawBitmap(0, 0, corp_click3_d1_green,  8, 8, LED_GREEN);
  displays[0].drawBitmap(0, 0, corp_click3_d1_red,    8, 8, LED_RED);
  displays[0].drawBitmap(0, 0, corp_click3_d1_yellow, 8, 8, LED_YELLOW);
  displays[0].writeDisplay();


  displays[1].clear();
  displays[1].drawBitmap(0, 0, corp_click3_d2_green,  8, 8, LED_GREEN);
  displays[1].drawBitmap(0, 0, corp_click3_d2_red,    8, 8, LED_RED);
  displays[1].drawBitmap(0, 0, corp_click3_d2_yellow, 8, 8, LED_YELLOW);
  displays[1].writeDisplay();

  delay(1500);

  displays[0].clear();
  displays[1].clear();

  delay(1500);

}

void displayText(int displayNum, String text, int color=LED_GREEN) {
  int pos[2] = { text.length() > 1 ? 0 : 2, 5};

  displays[displayNum].setTextColor(color);
  displays[displayNum].clear();
  displays[displayNum].setCursor(pos[0], pos[1]);
  displays[displayNum].print(text);
  displays[displayNum].writeDisplay();
}

