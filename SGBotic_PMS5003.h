/*********************************************************** 
  This is a library for our PMS5003 PM2.5 Air Quality Sensor

  These sensor uses TTL Serial to communicate, 

 ***********************************************************/

#include "Arduino.h"
#ifdef __AVR__
#include <SoftwareSerial.h>
#endif

//#define PMS5003_DEBUG 

#define PMS5003_STARTBYTE   0x42
#define data_size         15

#define pm10_standard       1
#define pm25_standard       2
#define pm100_standard      3
#define pm10_env            4
#define pm25_env            5
#define pm100_env           6
#define particles_03um      7
#define particles_05um       8
#define particles_10um      9
#define particles_25um      10
#define particles_50um      11
#define particles_100um     12
#define checksum            14

class SGBotic_PMS5003 {
    public:    
    
#ifdef __AVR__
    SGBotic_PMS5003(SoftwareSerial *);
#endif 
    SGBotic_PMS5003(HardwareSerial *);
    void begin(uint16_t baud);
    uint8_t readPMS(uint16_t buffer_u16[15]);   

    private: 

    Stream *mySerial;
#ifdef __AVR__
    SoftwareSerial *swSerial;
#endif
    HardwareSerial *hwSerial;
};
