/*

BTN1 Long Press (.5sec)
- switch modes RUNNER|CORP

MODES
- RUNNER click tracker
  - BTN1 undo click or switch to WAITING
  - BTN2 spend clicks
- CORP click tracker or switch to WAITING
  - BTN1 undo click
  - BTN2 spend clicks

After last click, 5s delay, blank out for other player turn
  - BTN1 go to max_clicks (undo)
  - BTN2 reset (0 clicks)

Runner Click Tracker

  #       #             
 *#*     *#*         
**##*   **##*        
 *** #   *** #        
  * *#*   * *#*      
   **##*   **##*        
    ***     ***         
     *       *       

Corp Click Tracker

  #         #             
 *#*   #   *#*         
**##* *#* **##*        
 *** **##* ***          
  *   ***   *          
       *                

*/

#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Fonts/Picopixel.h>
#include <ezButton.h>

#define NUM_DISPLAYS 2
Adafruit_BicolorMatrix displays[2] = { Adafruit_BicolorMatrix(), Adafruit_BicolorMatrix() };

static const uint8_t PROGMEM
  runner_click0_d1_green[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click0_d2_green[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
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
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },
  runner_click0_d2_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },

  runner_click1_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click1_d2_green[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click1_d1_red[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
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
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },
  runner_click1_d2_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
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
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click2_d1_red[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
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
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },
  runner_click2_d2_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
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
      B00011001,
      B00001110,
      B00000100 },
  runner_click3_d1_red[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click3_d2_red[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00100000,
      B00000000,
      B00000000,
      B00000000 },
  runner_click3_d1_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },
  runner_click3_d2_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
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
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click4_d2_red[] =
    { B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00101010,
      B00011001,
      B00001110,
      B00000100 },
  runner_click4_d1_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },
  runner_click4_d2_yellow[] =
    { B00100000,
      B00100000,
      B00110000,
      B00000100,
      B00000100,
      B00000110,
      B00000000,
      B00000000 },

  corp_click0_d1_green[] =
    { B00000000,
      B00000000,
      B01010000,
      B11001010,
      B01110110,
      B00100011,
      B00000001,
      B00000000 },
  corp_click0_d2_green[] =
    { B00000000,
      B00000000,
      B00010100,
      B10110010,
      B01011100,
      B10001000,
      B00000000,
      B00000000 },
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
    { B00000000,
      B00100000,
      B00100001,
      B00110001,
      B00000001,
      B00000000,
      B00000000,
      B00000000 },
  corp_click0_d2_yellow[] =
    { B00000000,
      B00001000,
      B00001000,
      B00001100,
      B10000000,
      B00000000,
      B00000000,
      B00000000 },

  corp_click1_d1_green[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000010,
      B00000110,
      B00000011,
      B00000001,
      B00000000 },
  corp_click1_d2_green[] =
    { B00000000,
      B00000000,
      B00010100,
      B10110010,
      B01011100,
      B10001000,
      B00000000,
      B00000000 },
  corp_click1_d1_red[] =
    { B00000000,
      B00000000,
      B01010000,
      B11001000,
      B01110000,
      B00100000,
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
    { B00000000,
      B00100000,
      B00100001,
      B00110001,
      B00000001,
      B00000000,
      B00000000,
      B00000000 },
  corp_click1_d2_yellow[] =
    { B00000000,
      B00001000,
      B00001000,
      B00001100,
      B10000000,
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
    { B00000000,
      B00000000,
      B00010100,
      B00110010,
      B00011100,
      B00001000,
      B00000000,
      B00000000 },
  corp_click2_d1_red[] =
    { B00000000,
      B00000000,
      B01010000,
      B11001010,
      B01110110,
      B00100011,
      B00000001,
      B00000000 },
  corp_click2_d2_red[] =
    { B00000000,
      B00000000,
      B00000000,
      B10000000,
      B01000000,
      B10000000,
      B00000000,
      B00000000 },
  corp_click2_d1_yellow[] =
    { B00000000,
      B00100000,
      B00100001,
      B00110001,
      B00000001,
      B00000000,
      B00000000,
      B00000000 },
  corp_click2_d2_yellow[] =
    { B00000000,
      B00001000,
      B00001000,
      B00001100,
      B10000000,
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
    { B00000000,
      B00000000,
      B01010000,
      B11001010,
      B01110110,
      B00100011,
      B00000001,
      B00000000 },
  corp_click3_d2_red[] =
    { B00000000,
      B00000000,
      B00010100,
      B10110010,
      B01011100,
      B10001000,
      B00000000,
      B00000000 },
  corp_click3_d1_yellow[] =
    { B00000000,
      B00100000,
      B00100001,
      B00110001,
      B00000001,
      B00000000,
      B00000000,
      B00000000 },
  corp_click3_d2_yellow[] =
    { B00000000,
      B00001000,
      B00001000,
      B00001100,
      B10000000,
      B00000000,
      B00000000,
      B00000000 };

// states
#define INIT 0
#define RUNNER 1
#define CORP 2
#define WAITING 3

// Num Clicks
#define RUNNER_CLICKS 4
#define CORP_CLICKS 3

// UI
#define BUTTON_COUNT 2
#define BTN_1_PIN 8
#define BTN_1_LED 6
#define BTN_2_PIN 9
#define BTN_2_LED 7

ezButton btn1(BTN_1_PIN);
ezButton btn2(BTN_2_PIN);

int currentClick = 0;
int state = INIT;
const int debounceDelay = 50;

unsigned long PSEUDO_INFINITY;

const unsigned long switchModeHoldTime = 500; // ms
unsigned long switchModeTimer;

const int lastClickDelay = 5000; // ms
unsigned long lastClickDelayMs;

void setup() {
  Serial.begin(9600);

  PSEUDO_INFINITY = millis() + 3600000; // 10 hrs
  switchModeTimer = PSEUDO_INFINITY;
  lastClickDelayMs = PSEUDO_INFINITY;

  displays[0].begin(0x70);
  displays[1].begin(0x71);

  pinMode(BTN_1_LED, OUTPUT);
  pinMode(BTN_2_LED, OUTPUT);

  for (int i = 0, l = NUM_DISPLAYS; i < l; i++) {
    displays[i].setFont(&Picopixel);
    displays[i].setTextWrap(false);
    displays[i].setTextSize(1);
    displays[i].setRotation(3);
  }

  btn1.setDebounceTime(debounceDelay);
  btn2.setDebounceTime(debounceDelay);

  _init();
  Serial.print("Ready, on 9600\n");
}

void clearDisplays() {
  for (int i = 0; i < NUM_DISPLAYS; i++) {
    displays[i].clear();
    displays[i].writeDisplay();
  }
}

void handleButtons() {
  btn1.loop();
  btn2.loop();

  if (btn1.isPressed()) {
    switchModeTimer = millis()+switchModeHoldTime;
    lastClickClearTimer();
  } else if (btn1.isReleased()) {
    if (millis() >= switchModeTimer) {
      cycleModes();
    } else {
      clickDown();
      animateLed(0);
    }
    switchModeTimer = PSEUDO_INFINITY;
  } else if (btn2.isPressed()) {
    lastClickClearTimer();
    clickUp();
    animateLed(1);
  }
}

void setState(int _state) {
  state = _state;
  currentClick = 0;
  if (state == CORP) {
    renderCorpClick();
  } else if (state == RUNNER){
    renderRunnerClick();
  }
}

// delay, then blank out
void lastClickReset() {
  lastClickDelayMs = millis()+lastClickDelay;
}
void lastClickClearTimer() {
  lastClickDelayMs = PSEUDO_INFINITY;
}
void lastClickResetTimeout() {
  displays[0].clear();
  displays[0].writeDisplay();
  displays[1].clear();
  displays[1].writeDisplay();
  currentClick = 0;
}

void clickUp() {
  switch (state) {
    case CORP:
      currentClick = (currentClick + 1) % (CORP_CLICKS + 1);
      renderCorpClick();
      if (currentClick == CORP_CLICKS) {
        lastClickReset();
        return;
      }
      break;
    case RUNNER:
      currentClick = (currentClick + 1) % (RUNNER_CLICKS + 1);
      renderRunnerClick();
      if (currentClick == RUNNER_CLICKS) {
        lastClickReset();
        return;
      }
      break;
  }
}

void clickDown() {
  switch (state) {
    case CORP:
      if (currentClick > 0) {
        currentClick = (currentClick - 1) % (CORP_CLICKS + 1);
      }
      renderCorpClick();
      break;
    case RUNNER:
      if (currentClick > 0) {
        currentClick = (currentClick - 1) % (RUNNER_CLICKS + 1);
      }
      renderRunnerClick();
      break;
  }
}

void cycleModes() {
  switch (state) {
    case CORP:
      setState(RUNNER);
      break;
    case RUNNER:
      setState(CORP);
      break;
  }
  animateLed(0);
  animateLed(1);
}

const int ledAnimateSpeed = 35; // ticks between flashes
const int ledAnimationDuration = 175;
int ledPins[2] = { BTN_1_LED, BTN_2_LED };
int ledAnimations[2] = { 0, 0 };
int ledAnimateState[2] = { LOW, LOW };

void animateLed(int ledIdx) {
  ledAnimations[ledIdx] = ledAnimationDuration;
}

void handleLedAnimations() {
  for (int i = 0; i < 2; i++) {
    if (ledAnimations[i] > 0) {
      ledAnimations[i]--;
      delay(1);
      if ( (ledAnimations[i] / ledAnimateSpeed) % 2 == 0) {
        if ( ledAnimateState[i] == LOW ) {
          digitalWrite(ledPins[i], HIGH);
          ledAnimateState[i] = HIGH;
        }
      } else {
        if ( ledAnimateState[i] == HIGH ) {
          digitalWrite(ledPins[i], LOW);
          ledAnimateState[i] = LOW;
        }
      }
    } else if ( ledAnimateState[i] == HIGH ) {
        digitalWrite(ledPins[i], LOW);
        ledAnimateState[i] = LOW;
    }
  }
}

void handleTimers() {
  if (lastClickDelayMs != PSEUDO_INFINITY) {
    unsigned long now = millis();

    if (now >= lastClickDelayMs) {
      lastClickResetTimeout();
      lastClickDelayMs = PSEUDO_INFINITY;
    }
  }
}

void _init() {
  setState(RUNNER);
}

void loop() {
  handleButtons();
  handleLedAnimations();
  handleTimers();
}

void renderRunnerClick() {
  switch (currentClick) {
    case 0: 
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
      break;
    case 1:
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
      break;
    case 2:
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
      break;
    case 3:
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
      break;
    case 4:
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
      break;
  }
}

void renderCorpClick() {
  switch (currentClick) {
    case 0: 
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
      break;
    case 1:
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
      break;
    case 2:
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
      break;
    case 3:
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
      break;
  }

}

void displayText(int displayNum, String text, int color=LED_GREEN) {
  int pos[2] = { text.length() > 1 ? 0 : 2, 5};

  displays[displayNum].setTextColor(color);
  displays[displayNum].clear();
  displays[displayNum].setCursor(pos[0], pos[1]);
  displays[displayNum].print(text);
  displays[displayNum].writeDisplay();
}

