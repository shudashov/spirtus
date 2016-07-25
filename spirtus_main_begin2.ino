

#include <avr/sleep.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h> // Lib for LCD 2x16 I2C display
LiquidCrystal_I2C lcd(0x20, 16, 2); // set the LCD address to 0x20 for a 16 chars and 2 line display

#include "global_def.h"
#include "RTC_TIME.h"
#include "BMP180_BARO.h"


char LCDString_1[16]; //1 line of LCD display
char LCDString_2[16]; //2 line of LCD display

int wakePin = 2;                 // pin used for waking up INT0
int sleepStatus = 0;             // variable to store a request for sleep



int  RTC_current_date[20]; //array for current sec[0], min[1], hour[2], weekday[3] date[4] month [5] year[6] registers [7-19]
RTC_TIME TIME; //init RTC_TIME class


float BMP180_TEMP;   //global Temperature from BMP180
int BMP180_PRES;    //global Pressure from BMP180 in mm/Hg
//BMP_BARO BMP180;    // init BMP_BARO class


void setup()
{
  Wire.begin();
  Serial.begin(9600);

  pinMode(wakePin, INPUT); //uttach interrupt pin declare

  lcd.init();
  lcd.backlight();
  lcd.noBacklight();



}

void loop()
{
  lcd.backlight();
  for ( int i = 0; i < 50; i++)
  {
    TIME.RTC_read(RTC_current_date);  //Read the Real-time Clock
//    BMP180.BMP180_T_H(BMP180_TEMP, BMP180_PRES); //Read Baro and Temperature BMP180

    snprintf(LCDString_1, sizeof(LCDString_1), "Time: %.2u:%.2u:%.2u", RTC_current_date[2], RTC_current_date[1], RTC_current_date[0]);
    snprintf(LCDString_2, sizeof(LCDString_2), "Temp: %5.2f P:%.3u", BMP180_TEMP, BMP180_PRES);
    Serial.println(LCDString_1);
    lcd.home();

    lcd.print(LCDString_1);

    delay(100);//延时1S
  }
  TIME.RTC_timer_on();
  lcd.noBacklight();
  sleepNow();

}


void sleepNow()         // here we put the arduino to sleep
{

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

  sleep_enable();          // enables the sleep bit in the mcucr register

  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
  // wakeUpNow when pin 2 gets LOW

  sleep_mode();            // here the device is actually put to sleep!!
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable();         // first thing after waking from sleep:
  // disable sleep...
  detachInterrupt(0);      // disables interrupt 0 on pin 2 so the
  // wakeUpNow code will not be executed
  // during normal running time.

}

void wakeUpNow()        // here the interrupt is handled after wakeup
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
}






