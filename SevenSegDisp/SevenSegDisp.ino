//#define TEST_SMALL__ X

#include "Free_Fonts.h"
#include "TFT_eSPI.h"
#ifdef TEST_SMALL__
#include "SEG_S.h"
#else
#include "SEG_M.h"
#endif

long millisNow = 0;
long colonTimer = 0;
long updateTimer = 0;
long incTimer = 0;
bool colonOn = false;
int countMax = 0;
const int offsets[]{0, 0, -5, 0};

#ifdef TEST_SMALL__
ClockDisplaySmall clockDisplay = ClockDisplaySmall();
SegmentDisplaySmall colOn = SegmentDisplaySmall();
SegmentDisplaySmall colOff = SegmentDisplaySmall();
SegmentDisplaySmall segOff = SegmentDisplaySmall();
SegmentDisplaySmall segErr = SegmentDisplaySmall();
#else
ClockDisplayMedium clockDisplay = ClockDisplayMedium();
SegmentDisplayMedium colOn = SegmentDisplayMedium();
SegmentDisplayMedium colOff = SegmentDisplayMedium();
SegmentDisplayMedium segOff = SegmentDisplayMedium();
SegmentDisplayMedium segErr = SegmentDisplayMedium();
#endif

static TFT_eSPI dispBuffer;  // The screen (This should be a sprite but there is not enough memory)

int bgColor = dispBuffer.color565(0, 255, 255);
int fgColor = dispBuffer.color565(200, 0, 0);
int offColor = dispBuffer.color565(0, 200, 200);

void setup() {
    pinMode(WIO_LIGHT, INPUT);
    pinMode(WIO_KEY_A, INPUT_PULLUP);
    pinMode(WIO_KEY_B, INPUT_PULLUP);
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);
    pinMode(WIO_BUZZER, OUTPUT);
    dispBuffer.begin();
    dispBuffer.setRotation(3);
    dispBuffer.fillScreen(bgColor);
    dispBuffer.setTextColor(TFT_BLACK);
    dispBuffer.setFreeFont(FF28);

    clockDisplay.init(dispBuffer, 10, 10, fgColor, offColor, 5, offsets);
    clockDisplay.setValue(0, SEGMENT_ALL_OFF);
    clockDisplay.setValue(1, 0);
    clockDisplay.setColon(2, colonOn);
    clockDisplay.setValue(3, 0);
    clockDisplay.setValue(4, 0);

    clockDisplay.update();

    segErr.init(dispBuffer, 120, 120, fgColor, offColor);
    segErr.drawSegment(SEVEN_SEG_MAP_MAX);

    colOn.init(dispBuffer, 160, 120, fgColor, offColor);
    colOn.drawSegment(SEGMENT_COLON_ON);

    colOff.init(dispBuffer, 200, 120, fgColor, offColor);
    colOff.drawSegment(SEGMENT_COLON_OFF);

    segOff.init(dispBuffer, 250, 120, fgColor, offColor);
    segOff.drawSegment(SEGMENT_ALL_OFF);

}  // END setup

/*
   Mail loop. All processes need to be completed in here.
   Each process has a timer (unless it is required EVERY loop)

   For example Key Scan:
    Timer  = timerKeyScan (is a global long)
    Period = TIMER_KEY_SCAN (is a #define)

   To test if it is time:
    if (millisNow > timerKeyScan) {
   Then reset the timer:
     timerKeyScan = millisNow + TIMER_KEY_SCAN;

   Where millisNow == millis() (The time at the start of the loop).

   All timers are global and long.
*/
void loop() {
    //
    // Call millis() once to get the time at the start of the loop.
    //
    millisNow = millis();
    if (millisNow > colonTimer) {
        colonTimer = millisNow + 500;
        colonOn = clockDisplay.setColon(2, colonOn);
    }

    if (millisNow > incTimer) {
        incTimer = millisNow + 100;
        int v = clockDisplay.getValue(4);
        v = v + 1;
        if (v > 15) {
            clockDisplay.setValue(4, 0);
            v = clockDisplay.getValue(3);
            v = v + 1;
            if (v > 15) {
                clockDisplay.setValue(3, 0);
                v = clockDisplay.getValue(1);
                v = v + 1;
                if (v > 15) {
                    clockDisplay.setValue(1, 0);
                    countMax = 0;
                } else {
                    clockDisplay.setValue(1, v);
                }
            } else {
                clockDisplay.setValue(3, v);
            }
        } else {
            clockDisplay.setValue(4, v);
        }
    }

    if (millisNow > updateTimer) {
        updateTimer = millisNow + 100;
        int count = clockDisplay.update();
        if (count > countMax) {
            countMax = count;
        }
        dispBuffer.fillRect(10, 150, 50, 100, bgColor);
        dispBuffer.drawString(String(count), 10, 150);
        dispBuffer.drawString(String(countMax), 10, 190);
    }
    // **************************************************
    // Is it time to Scan the Keys (buttons)?
    // ***************************************************/

}  // END loop
