# WIO-Terminal-SevenSegDisp

Seven Segment (SS) Display for Arduino/WIO-Terminal.

Includes classes for individual SS displays and a Group of diaplays.

Includes data for display 0..9 A..F and a colon.

Includes a Clock display.

## Medium
A medium sized display.
### Includes
#include "SEG_M.h"
### Classes
SegmentDisplayMedium
ClockDisplayMedium

## Small
A smaller display
### Includes
#include "SEG_S.h"
### Classes
SegmentDisplaySmall
ClockDisplaySmall

## Example
SevenSegDisp.ino is an example of how it is used.

At the top of the file ther is a
```C++
//#define TEST_SMALL__ X
```
As it is it will display the MEDIUM display. If you remove the '//' at the start of the line it will display the SMALL display.

You can use both MEDIUM and SMALL displays in the same application. Simply include both SEG_S.h and SEG_M.h

## Usage
Simply copu the SEG_S.h and SEG_S.cpp (and/or SEG_M.h and SEG_M.cpp) files in to your project dir.

Both MEDIUM and SMALL have the same code but they are kept separate to reduce the size if only one is used.

## API
### SegmentDisplaySmall &  SegmentDisplayMedium

```C++
void init(TFT_eSPI tft, int x, int y, int fg, int bg);
```
Define an individual Seven Segment character.
* TFT_eSPI tft - Is the display object. This can be the TFT_eSPI class or a sprite class.
* int x - The x position
* int y - The y position
* int fg - The foreground colour, displayed when a segment is ON.
* int bg - The background colour, displayed when a segment is OFF.

```C++
void drawSegment(int value);
```
Draw an an individual Seven Segment character.
* int value - The character to draw:
  * 0..9 for decimal characters
  * 10..15 for hex characters A,B,C,D,E and F
  * SEGMENT_ALL_OFF (127) for ALL segments OFF
  * SEGMENT_COLON_ON (128) for the : character ON
  * SEGMENT_COLON_OFF (129) for the : character OFF
  * Unrecognised values are displayed as a '-'

Note - SEGMENT_ALL_OFF, SEGMENT_COLON_ON and SEGMENT_COLON_OFF are defined in both SEG_M.h and SEG_S.h.

