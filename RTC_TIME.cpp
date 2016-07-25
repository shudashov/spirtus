#include "RTC_TIME.h"


//<<constructor>> 
RTC_TIME::RTC_TIME(){
#define RTC_Address   0x32  //RTC_Address on I2C bus
}

//<<destructor>>
RTC_TIME::~RTC_TIME(){/*nothing to destruct*/
}




//Read the Real-time data register of SD2403 and write to global RTC_current_date[]
void RTC_TIME :: RTC_read(int RTC_current_date[20])
{
  int _n = 0;

  Wire.requestFrom(RTC_Address, 20);
  while (Wire.available())
  {
    RTC_current_date[_n++] = Wire.read();
  }
  delayMicroseconds(1);
  Wire.endTransmission();

  int _i;

  for (_i = 0; _i < 7; _i++)
  {
    if (_i != 2)
      RTC_current_date[_i] = (((RTC_current_date[_i] & 0xf0) >> 4) * 10) + (RTC_current_date[_i] & 0x0f);
    else
    {
      RTC_current_date[2] = (RTC_current_date[2] & 0x7f);
      RTC_current_date[2] = (((RTC_current_date[2] & 0xf0) >> 4) * 10) + (RTC_current_date[2] & 0x0f);
    }
  }
}


void RTC_TIME :: RTC_timer_on(void)
{

  WriteRTCOn(); // enable write

  //set countdown soursecloc
  Wire.beginTransmission(RTC_Address); //set countdown soursecloc
  Wire.write(RTC_CTR3);//Set the address for writing as 11H
  Wire.write(CTR3_TDS1);//Set count down to 1Hz
  Wire.endTransmission();


  //Set INTDF to 0
  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR1);//Set the address for writing as 0FH
  Wire.write(CTR1_WRTC3 | CTR1_WRTC2);//Set INTDF to 0
  Wire.endTransmission();

  //Set INTDe to 0
  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR2);//Set the address for writing as 10H
  Wire.write(CTR2_WRTC1 | RTC_INT_SET_TO_CNDWN);//Set INTDe to 0
  Wire.endTransmission();

  //Set count down to 04H
  Wire.beginTransmission(RTC_Address); //set countdown
  Wire.write(RTC_COUNT_DOWN);//Set the address for writing as 13H
  Wire.write(0x5);//Set count down to 04H
  Wire.endTransmission();


  //Set INTDe to 1
  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR2);//Set the address for writing as 10H
  Wire.write(CTR2_WRTC1 | RTC_INT_SET_TO_CNDWN | CTR2_INTDE);//Set INTDe to 1
  Wire.endTransmission();


  WriteRTCOff(); // disable write
}

//The program for allowing to write to SD2400
void RTC_TIME :: WriteRTCOn(void)
{
  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR2);//Set the address for writing as 10H
  Wire.write(0x80);//Set WRTC1=1
  Wire.endTransmission();

  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR1);//Set the address for writing as OFH
  Wire.write(0x84);//Set WRTC2=1,WRTC3=1
  Wire.endTransmission();
}

//The program for forbidding writing to SD2400
void RTC_TIME :: WriteRTCOff(void)
{
  Wire.beginTransmission(RTC_Address);
  Wire.write(RTC_CTR1);   //Set the address for writing as OFH
  Wire.write(byte(0));//Set WRTC2=0,WRTC3=0
  Wire.write(byte(0));//Set WRTC1=0
  Wire.endTransmission();

}






