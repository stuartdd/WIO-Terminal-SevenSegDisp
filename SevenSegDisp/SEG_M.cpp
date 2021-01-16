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
    _tft = tft;
    if (digitCount >= SEGMENT_COUNT) {
        digits = SEGMENT_COUNT;
    } else {
        digits = digitCount;
    }

    int xPos = x;
    for (int i = 0; i < digits; i++) {
        segments[i] = SegmentDisplayMedium();
        segments[i].init(tft, xPos, y, fg, bg);
        xPos = xPos + (SEGMENT_WIDTH + digitOffset[i]);
    }
}

int ClockDisplayMedium::invalidate() {
    for (int i = 0; i < digits; i++) {
        segments[i].invalidate();
    }
}

int ClockDisplayMedium::draw() {
    int count = 0;
    for (int i = 0; i < digits; i++) {
        count = count + segments[i].draw();
    }
    return count;
}

void ClockDisplayMedium::setFgColor(int c) {
    for (int i = 0; i < digits; i++) {
        segments[i].setFgColor(c);
    }
}

void ClockDisplayMedium::setBgColor(int c) {
    for (int i = 0; i < digits; i++) {
        segments[i].setBgColor(c);
    }
}

int ClockDisplayMedium::getFgColor() {
    return segments[0].getFgColor();
}

int ClockDisplayMedium::getBgColor() {
    return segments[0].getBgColor();
}

void ClockDisplayMedium::setValue(int pos, int val) {
    if ((pos >= 0) && (pos < digits)) {
        segments[pos].setValue(val);
    }
}

int ClockDisplayMedium::getValue(int pos) {
    if ((pos >= 0) && (pos < digits)) {
        return segments[pos].getValue();
    }
    return -1;
}

bool ClockDisplayMedium::setColon(int pos, bool val) {
    if ((pos >= 0) && (pos < digits)) {
        segments[pos].setValue(val ? SEGMENT_COLON_ON : SEGMENT_COLON_OFF);
    }
    return false;
}

void SegmentDisplayMedium::init(TFT_eSPI tft, int x, int y, int fg, int bg) {
    _tft = tft;
    setValue(SEGMENT_UNDEFINED);
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

int SegmentDisplayMedium::draw() {
    if ((segValue == segValueCurrent) || (segValue == SEGMENT_UNDEFINED)) {
        return 0;
    }
    segValueCurrent = segValue;
    switch (segValue) {
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
        if ((segValue >= 0) && (segValue < SEVEN_SEG_MAP_MAX)) {
            drawSegmentInternal(sevenSegmentMap[segValue]);
        } else {
            drawSegmentInternal(SEVEN_SEG_MAP_ERR);
        }
    }
    return 1;
}

int SegmentDisplayMedium::invalidate() {
    segValueCurrent = SEGMENT_UPDATE;
}

void SegmentDisplayMedium::setValue(int val) {
    segValue = val;
}

int SegmentDisplayMedium::getValue() {
    return segValue;
}

void SegmentDisplayMedium::setFgColor(int color) {
    fgColor = color;
    segValueCurrent = SEGMENT_UPDATE;
}

void SegmentDisplayMedium::setBgColor(int color) {
    bgColor = color;
    segValueCurrent = SEGMENT_UPDATE;
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
    segValueCurrent = SEGMENT_UPDATE;
}

#endif
