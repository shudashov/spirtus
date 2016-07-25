#ifndef RTC_TIME_H
#define RTC_TIME_H
 
#include <Arduino.h>
#include <Wire.h>
#include "global_def.h"

 
class RTC_TIME {
public:
        RTC_TIME();
        ~RTC_TIME();
        void RTC_read(int RTC_current_date[]);
        void RTC_timer_on (void);
        void WriteRTCOn(void);
        void WriteRTCOff(void);
};
 
#endif
