
#define RTC_Address   0x32  //RTC_Address on I2C bus


// RTC control registers
#define RTC_CTR1 0x0F
#define RTC_CTR2 0x10
#define RTC_CTR3 0x11
#define RTC_COUNT_DOWN 0x13

// flags
#define CTR1_WRTC3 0x80
#define CTR1_WRTC2 0x04

#define CTR2_WRTC1 0x80
#define CTR2_INTS1 0x10
#define CTR2_INTS0 0x20
#define CTR2_INTDE 0x04

#define CTR3_TDS1 0x20
#define CTR3_TDS0 0x10

// tds
#define TDS_4096 (0)
#define TDS_64 (CTR3_TDS0)
#define TDS_1 (CTR3_TDS1)
#define TDS_1divDIV60 (CTR3_TDS1 | CTR3_TDS0)

// ints
#define RTC_INT_SET_TO_CNDWN (CTR2_INTS1 | CTR2_INTS0) //hardware output set to Countdown timer
