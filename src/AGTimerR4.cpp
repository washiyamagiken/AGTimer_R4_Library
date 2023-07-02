/*
  AGTimerR4.cpp

  Copyright (c) 2023 washiyamagiken All Rights Reserved.

  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
*/

#include "AGTimerR4.h"

#define CLOCK_FREQ_DIV1 24000000.0f
#define CLOCK_FREQ_DIV2 12000000.0f
#define CLOCK_FREQ_DIV8 3000000.0f
#define CLOCK_FREQ_DIV64 32768.0f

#define FREQ_L_DIV1 ((int)(CLOCK_FREQ_DIV1 / 65535))
#define FREQ_L_DIV2 ((int)(CLOCK_FREQ_DIV2 / 65535))
#define FREQ_L_DIV8 ((int)(CLOCK_FREQ_DIV8 / 65535))

AGTimerR4 AGTimer;

void (*AGTimerR4::callback_func)();

void AGTimerR4::ourTimerCallback(timer_callback_args_t __attribute((unused)) * p_args) {
  AGTimerR4::callback_func();
}

void AGTimerR4::init(double freq_hz, void (*callback)()) {
  float clock_freq;
  timer_source_div_t sd;

  if (freq_hz > FREQ_L_DIV1) {
    sd = TIMER_SOURCE_DIV_1;
    clock_freq = CLOCK_FREQ_DIV1;
  } else if (freq_hz > FREQ_L_DIV2) {
    sd = TIMER_SOURCE_DIV_2;
    clock_freq = CLOCK_FREQ_DIV2;
  } else if (freq_hz > FREQ_L_DIV8) {
    sd = TIMER_SOURCE_DIV_8;
    clock_freq = CLOCK_FREQ_DIV8;
  } else {
    sd = TIMER_SOURCE_DIV_64;
    clock_freq = CLOCK_FREQ_DIV64;
  }
  int period = (int)(clock_freq / freq_hz);

  init(period, sd, callback);
}

void AGTimerR4::init(int period_us, void (*callback)()) {
  init(1.0f / (0.000001f * period_us), callback);
}

void AGTimerR4::init(int period, timer_source_div_t sd, void (*callback)()) {
  AGTimerR4::callback_func = callback;

  fsp_timer.begin(TIMER_MODE_PERIODIC, AGT_TIMER, 1, period, 1, sd, ourTimerCallback);
  IRQManager::getInstance().addPeripheral(IRQ_AGT, (void*)fsp_timer.get_cfg());
  fsp_timer.open();
}

bool AGTimerR4::start(void) {
  return fsp_timer.start();
}

bool AGTimerR4::stop(void) {
  return fsp_timer.stop();
}
