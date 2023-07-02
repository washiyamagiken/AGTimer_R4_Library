/*
  blink_AGTimerR4
  toggles an LED on and off repeatedly.
*/

#include "AGTimerR4.h"

void timerCallback() {
  static bool led_stat = false;

  digitalWrite(LED_BUILTIN, led_stat ? HIGH : LOW);
  led_stat = !led_stat;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  AGTimer.init(500000, timerCallback); //  500ms
  AGTimer.start();
}

void loop() {
}