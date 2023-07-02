# AGTimer R4

Arduino UNO R4 timer library.
Periodically generate an interrupt and call the function.

## Usage

```cpp
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
```

## API

### init(period_us, timerCallback)
timerCallback function will be called each period_us[microseconds].

### init(freq, timerCallback)
Initialize by specifying the frequency[Hz] of function calls.

### init(period, div, timerCallback)
Initialize with period and prescaler.

### start()
Start the timer.　Call the init() function first.

### stop()
Stop the timer.

## License
Copyright (c) 2023 washiyamagiken - MIT License