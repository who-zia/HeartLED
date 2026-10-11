#include <Adafruit_NeoPixel.h>
#define LED_PIN 0
#define BUTTON_PIN 3
#define NUM_LEDS 8

Adafruit_Neopixel strip(NUM_LEDS, LED_PIN, NEP_GRB+NEO_KHZ800);

int animationMode=0;
bool lastButtonState=HIGH;

void setup() {
    pinmode(BUTTON_PIN, INPUT_PULLUP);
    strip.begin();
    strip.show();
}

void loop() {
    bool currentButtonState=digitalRead(BUTTON_PIN);
    if(currentButtonState==LOW && lastButtonState==HIGH) {
        animationMode= (animationMode+1)%3;
        delay(50);
    }
    lastButtonState=currentButtonState;

    if (animationMode==0) {
        colorPulse(strip.Color(255, 20, 147). 20);    
    } else if (animationMode==1) {
        rainbowCycle(10);
    } else {
        chasePattern(strip.Color(255, 255, 255), 50);
    }
}

void colourPulse(uint32_t color, int wait) {
    for (int j=0, j<256; j++) {
        for (int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, color);
        }
        strip.setBrightness(j);
        strip.show();
        delay(wait);
        if (checkButtonBreak()) return;
    }
    for (int j=225; j>=0; j--) {
        for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, color);
        }
        strip.setBrightness(j);
        strip.show();
        delay(wait);
        if(checkButtonBreak()) return;
    }
}

void rainbowCycle(uint8_t wait) {
    uint16_t i, j;
    for(j=0; j<256*5; j++) {
        for(i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i*256/strip.numPixels()) +j) &255));
        }
        strip.setBrightness(100);
        strip.show();
        delay(wait);
        if (checkButtonBreak()) return;
    }
}

void chasePattern(uint32_t c, uint8_t wait) {
    for(int i=0; i<strip.numPixels(); i++) {
        strip.clear();
        strip.setPixelColor(i,c);
        strip.setBrightness(150);
        strip.show();
        delay(wait);
        if (checkButtonBreak()) return;
    }
}

bool checkButtonBreak() {
    bool state-digitalRead(BUTTON_PIN);
    if (state==LOW) {
        delay(50);
        animationMode=(animationMode+1)%3;
        return true;
    }
    return false;
}

uint32_t Wheel(byte WheelPos) {
    WheelPos=255-WheelPos;
    if (WheelPos<85) {
        return strip.Color(255-WheelPos*3,0,WheelPos*3);
    }
    if(WheelPos<170) {
        WheelPos-=85;
        return strip.Color(0, WheelPos*3, 255-WheelPos*3);
    }
    WheelPos-=170;
    return strip.Color(WheelPos*3, 255-WheelPos*3, 0);
}