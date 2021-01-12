/*
 * Copyright (C) 2020 Stuart Davies
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SEG_M.h
 * SEG_M.cpp
 *
 * Created on 13 December 2020
 *
 * @file SEG_M.cpp
*/

#ifndef SEVEN_SEG_MED_CPP__
#define SEVEN_SEG_MED_CPP__

#include "SEG_M.h"

static TFT_eSPI _tft;

ClockDisplayMedium::ClockDisplayMedium() {
}
ClockDisplayMedium::~ClockDisplayMedium() {
}

SegmentDisplayMedium::SegmentDisplayMedium() {
}
SegmentDisplayMedium::~SegmentDisplayMedium() {
}

void ClockDisplayMedium::init(TFT_eSPI tft, int x, int y, int fg, int bg, int digitCount, const int digitOffset[]) {
    setTFT(tft);
    if (digitCount >= SEGMENT_COUNT) {
        digits = SEGMENT_COUNT;
    } else {
        digits = digitCount;
    }

    for (int i = 0; i < SEGMENT_COUNT; i++) {
        values[i] = SEGMENT_UNDEFINED;
        currentValues[i] = SEGMENT_UNDEFINED;
    }
    int xPos = x;
    for (int i = 0; i < digits; i++) {
        values[i] = SEGMENT_DEFAULT;
        currentValues[i] = SEGMENT_UPDATE;
        segments[i] = SegmentDisplayMedium();
        segments[i].init(tft, xPos, y, fg, bg);
        xPos = xPos + (SEGMENT_WIDTH + digitOffset[i]);
    }
}

int ClockDisplayMedium::update() {
    int count = 0;
    for (int i = 0; i < digits; i++) {
        if (values[i] != currentValues[i]) {
            currentValues[i] = values[i];
            segments[i].drawSegment(currentValues[i]);
            count++;
        }
    }
    return count;
}

void ClockDisplayMedium::setTFT(TFT_eSPI tft) {
    _tft = tft;
}

TFT_eSPI ClockDisplayMedium::getTFT() {
    return _tft;
}

void ClockDisplayMedium::setValue(int pos, int val) {
    if ((pos >= 0) && (pos < digits)) {
        values[pos] = val;
    }
}

int ClockDisplayMedium::getValue(int pos) {
    if ((pos >= 0) && (pos < digits)) {
        return values[pos];
    }
    return -1;
}

bool ClockDisplayMedium::setColon(int pos, bool val) {
    if ((pos >= 0) && (pos < digits)) {
        values[pos] = val ? SEGMENT_COLON_ON : SEGMENT_COLON_OFF;
        return !val;
    }
    return false;
}

void SegmentDisplayMedium::init(TFT_eSPI tft, int x, int y, int fg, int bg) {
    setTFT(tft);
    setFgColor(fg);
    setBgColor(bg);
    setPosition(x, y);
}

void SegmentDisplayMedium::drawSegmentInternal(int mask) {
    _tft.drawXBitmap(xPos + SEG_M_1_X, yPos + SEG_M_1_Y, SEG_M_1_bits, SEG_M_1_width, SEG_M_1_height, ((mask & 0x01) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_2_X, yPos + SEG_M_2_Y, SEG_M_2_bits, SEG_M_2_width, SEG_M_2_height, ((mask & 0x02) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_3_X, yPos + SEG_M_3_Y, SEG_M_3_bits, SEG_M_3_width, SEG_M_3_height, ((mask & 0x04) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_4_X, yPos + SEG_M_4_Y, SEG_M_4_bits, SEG_M_4_width, SEG_M_4_height, ((mask & 0x08) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_5_X, yPos + SEG_M_5_Y, SEG_M_5_bits, SEG_M_5_width, SEG_M_5_height, ((mask & 0x10) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_6_X, yPos + SEG_M_6_Y, SEG_M_6_bits, SEG_M_6_width, SEG_M_6_height, ((mask & 0x20) != 0) ? fgColor : bgColor);
    _tft.drawXBitmap(xPos + SEG_M_7_X, yPos + SEG_M_7_Y, SEG_M_7_bits, SEG_M_7_width, SEG_M_7_height, ((mask & 0x40) != 0) ? fgColor : bgColor);
}

void SegmentDisplayMedium::drawSegment(int value) {
    switch (value) {
    case SEGMENT_COLON_ON:
        _tft.drawXBitmap(xPos + SEG_M_8_X, yPos + SEG_M_8_Y, SEG_M_8_bits, SEG_M_8_width, SEG_M_8_height, fgColor);
        break;
    case SEGMENT_COLON_OFF:
        _tft.drawXBitmap(xPos + SEG_M_8_X, yPos + SEG_M_8_Y, SEG_M_8_bits, SEG_M_8_width, SEG_M_8_height, bgColor);
        break;
    case SEGMENT_ALL_OFF:
        drawSegmentInternal(0);
        break;
    default:
        if ((value >= 0) && (value < SEVEN_SEG_MAP_MAX)) {
            drawSegmentInternal(sevenSegmentMap[value]);
        } else {
            drawSegmentInternal(SEVEN_SEG_MAP_ERR);
        }
    }
}

void SegmentDisplayMedium::setTFT(TFT_eSPI tft) {
    _tft = tft;
}

TFT_eSPI SegmentDisplayMedium::getTFT() {
    return _tft;
}

int SegmentDisplayMedium::setFgColor(int color) {
    fgColor = color;
    return getFgColor();
}

int SegmentDisplayMedium::setBgColor(int color) {
    bgColor = color;
    return getBgColor();
}

int SegmentDisplayMedium::getFgColor() {
    return fgColor;
}

int SegmentDisplayMedium::getBgColor() {
    return bgColor;
}

int SegmentDisplayMedium::getXPos() {
    return xPos;
}

int SegmentDisplayMedium::getYPos() {
    return yPos;
}

void SegmentDisplayMedium::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
}

#endif
