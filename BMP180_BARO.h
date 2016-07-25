#ifndef BMP_BARO_H
#define BMP_BARO_H
 
#include <Arduino.h>
#include <Wire.h>
#include "global_def.h"

 
class BMP_BARO {
public:
        BMP_BARO();
        ~BMP_BARO();
        void BMP180_T_H(float BMP180_TEMP,int BMP180_PRES);
        void BMP180start(void);
        short bmp180GetTemperature(unsigned int ut);
        long bmp180GetPressure(unsigned long up);
        int bmp180Read(unsigned char address);
        int bmp180ReadDate(unsigned char address);
        unsigned int bmp180ReadUT(void);
        unsigned long bmp180ReadUP(void);

};
 
#endif
