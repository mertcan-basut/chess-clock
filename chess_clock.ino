#include "src/TM1637/TM1637Display.h"
#include "src/Bugtton/Bugtton.h"

TM1637Display tmr1(2,3);
TM1637Display tmr2(4,5);
uint8_t pins[2] = {12,13};
Bugtton buttons(2, pins, 25);
long timee1 = 600000;
long timee2 = 600000;
bool plyr1 = true;
bool plyr2 = false;
long oldMillis = 0;
uint8_t data[4] = {0x00,0x00,0x00,0x00};

void setup() {
  // put your setup code here, to run once:
  tmr1.clear();
  tmr1.setBrightness(2);
  tmr1.setSegments(new(uint8_t[1]){0x80},1,1);
  tmr2.clear();
  tmr2.setBrightness(2);
  tmr2.setSegments(new(uint8_t[1]){0x80},1,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttons.update();
  if(plyr1) {
    displayTime(timee1-millis(), tmr1);
  } else {
    displayTime(timee2-millis(), tmr2);
  }
  
  if(buttons.rose(1) && !plyr1) {
    plyr1 = true;
    plyr2 = false;
    timee1 = timee1 + millis() - oldMillis;
    oldMillis = millis();
  }
  else if(buttons.rose(0) && !plyr2) {
    plyr2 = true;
    plyr1 = false;
    timee2 = timee2 + millis() - oldMillis;
    oldMillis = millis();
  }
}

void displayTime(long miliseconds, TM1637Display timer) {
  int seconds = miliseconds/1000;
  int minute = seconds/60;
  int second = seconds%60;
  
  data[3] = timer.encodeDigit(second%10);
  data[2] = timer.encodeDigit(second/10%10);
  data[1] = timer.encodeDigit(minute%10) | 0x80;
  data[0] = timer.encodeDigit(minute/10%10);
  
  timer.setSegments(data);
}
