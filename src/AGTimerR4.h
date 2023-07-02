/*
  AGTimerR4.h

  Copyright (c) 2023 washiyamagiken All Rights Reserved.

  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
*/

#ifndef AGTIMERR4_h
#define AGTIMERR4_h

#include "Arduino.h"
#include "FspTimer.h"

class AGTimerR4 {
private:
  FspTimer fsp_timer;

  static void (*callback_func)();
  static void ourTimerCallback(timer_callback_args_t __attribute((unused)) * p_args);

public:
  void init(double freq_hz, void (*callback)());
  void init(int period_us, void (*callback)());
  void init(int period, timer_source_div_t sd, void (*callback)());
  bool start(void);
  bool stop(void);
};

extern AGTimerR4 AGTimer;
#endif
