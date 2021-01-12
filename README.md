# WIO-Terminal-SevenSegDisp

Slanting Seven Segment Display for Arduino/WIO-Terminal.

Includes classes for individual characterc and a Group of N characters.

Includes options for displaying 0..9 A..F and a colon.

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

At the top of the file there is a
```C++
//#define TEST_SMALL__ X
```
As it is it will display the MEDIUM display. If you remove the '//' at the start of the line it will display the SMALL display.

You can use both MEDIUM and SMALL displays in the same application. Simply include both SEG_S.h and SEG_M.h

## Usage
Simply copy the SEG_S.h and SEG_S.cpp (and/or SEG_M.h and SEG_M.cpp) files in to your project dir.

I am looking to set this up as a library module but have not had time yet.

Both MEDIUM and SMALL have the same code but they are kept separate to reduce the size if only one is used.

# API
## SegmentDisplaySmall &  SegmentDisplayMedium

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

There are get?() and set?() methods for colour and position attributes.

## ClockDisplaySmall &  ClockDisplayMedium

```C++
void init(TFT_eSPI tft, int x, int y, int fg, int bg, int digitCount, const int digitOffset[]);
```
Define an N digit display.
* TFT_eSPI tft - Is the display object. This can be the TFT_eSPI class or a sprite class.
* int x - The x position of the first (Left character)
* int y - The y position of the first (Left character)
* int fg - The foreground colour, displayed when a segment is ON.
* int bg - The background colour, displayed when a segment is OFF.
* int digitCount - The number of characters in the display 1..5
* int digitOffset[] - A list of offsets. The first is the gap between the first and second character. Negative values can be used to cause an overlap.
  * digitOffset[0] - gap between the first and second
  * digitOffset[1] - gap between the second and third
  * digitOffset[2] - gap between the third and forth
  * digitOffset[2] - gap between the forth and fith
  * etc.

```C++
    void setValue(int pos, int val);
```
Set the value of a specific digit.
* int pos - The specific digit. First is 0, this is range checked and is ignored if not in range.
* int val - This is the same value as drawSegment(int value).

```C++
    int getValue(int pos);
```
Get the value of a specific digit.
* int pos - The specific digit. First is 0, this is range checked and is -1 if not in range.

```C++
    bool setColon(int pos, bool val);
```
This sets the specific character value as a Colon ':'.

* int pos - The specific digit. First is 0, this is range checked and is ignored if not in range.
* bool val - true will set the colon ON, false will set the colon OFF.

Returns: The inverted value (!val).

# BITMAPS
To edit the basic shapes for each segment:

## Export
Export a section to a 'xbm' file. The following example is from the SEG_S.h file and is segment 4 from the small characters.

```c++
#define SEG_S_4_width 31
#define SEG_S_4_height 8
const unsigned char SEG_S_4_bits[] = {
    0xe0, 0x00, 0x80, 0x03, 0xf0, 0x03, 0xe0, 0x07, 0xf8, 0xff, 0xff, 0x0f,
    0xfc, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x7f,
    0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x1f};
```
```txt
   ----01----
   |        |
   06       02
   |        |
   ----07----
   |        |
   05       03
   |        |
   ----04---- <-- SEG_S_4
```

All segment names start with SEG_ followed by M_ or S_ (for Medium or Small) followed by the segment number.

SEG_S_8 is the Colon bitmap.

Each segment has 2 #defines
* SEG_x_n_width
* SEG_x_n_height

and a
* const unsigned char' array SEG_x_n_bits[]

You need to include all 3 in your export:

* SEG_S_4_width
* SEG_S_4_height
* SEG_S_4_bits[]

So create a file called SEG_S_4.xbm and paste the values in to it.

## Edit

Open the file in Gimp.

```bash
gimp SEG_S_4.xbm
```

Edit the bits. Note this is Black and White. No colour just 1 bit per pixel.

Don't do 'File save'

You need to **Export** the file as a xbm file or gimp will save it in it's own internal gimp file format.

Use 'File Export as' or File Overwrite'

## Import
Open the saved xbm file in a text editor!

Copy the text and replace the original text you exported in the SEG_S.h (or SEG_M.h) file.

## Finally

Gimp exports the bitmaps as a 'static unsigned char' value. This should be 'const unsigned char'.

Change:
```c++
#define SEG_S_4_width 31
#define SEG_S_4_height 8
static unsigned char SEG_S_4_bits[] = {
    0xe0, 0x00, 0x80, 0x03, 0xf0, 0x03, 0xe0, 0x07, 0xf8, 0xff, 0xff, 0x0f,
    0xfc, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x7f,
    0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x1f};
```
To:
```c++
#define SEG_S_4_width 31
#define SEG_S_4_height 8
const unsigned char SEG_S_4_bits[] = {
    0xe0, 0x00, 0x80, 0x03, 0xf0, 0x03, 0xe0, 0x07, 0xf8, 0xff, 0xff, 0x0f,
    0xfc, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x7f,
    0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x1f};
```