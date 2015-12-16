/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./chronometer.h"

#include <sys/time.h>
#include <stdlib.h>


Chronometer::Chronometer() {
  Reset();
}

int Chronometer::SysTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec;
}

void Chronometer::Reset() {
  time_ = 0;
  begin_ = 0;
}

void Chronometer::Stop() {
  if (!begin_ == 0) {
    time_ += SysTime() - begin_;
    begin_ = 0;
  }
}

void Chronometer::Start() {
  if (begin_ == 0) {
    begin_ = SysTime();
  }
}

int Chronometer::Time() {
  if (begin_ == 0) {
    return time_;
  } else {
    return time_ + (SysTime() - begin_);
  }
}

uint64_t Chronometer::Value() {
  return Time() - time;
}

double Chronometer::dValue() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double ms = static_cast<double>(tv.tv_usec)/1000000.0;
  double val = (Time() - time) + ms;
  val = static_cast<int>(val*100) / 100.0;
  return val;
}
