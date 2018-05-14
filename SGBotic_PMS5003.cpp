/*********************************************************** 
  This is a library for our PMS5003 PM2.5 Air Quality Sensor

  These sensor uses TTL Serial to communicate, 

 ***********************************************************/

#include "SGBotic_PMS5003.h"
#ifdef __AVR__
#include <util/delay.h>
#include <SoftwareSerial.h>
#endif


#ifdef __AVR__
SGBotic_PMS5003::SGBotic_PMS5003(SoftwareSerial *ss) {

    hwSerial = NULL;
    swSerial = ss;
    mySerial = swSerial;
}
#endif

SGBotic_PMS5003::SGBotic_PMS5003(HardwareSerial *ss) {

    #ifdef __AVR__
    swSerial = NULL;
    #endif
    hwSerial = ss;
    mySerial = hwSerial;
}

void SGBotic_PMS5003::begin(uint16_t baudrate) {
    delay(1000);  // one second delay to let the sensor 'boot up'

    if (hwSerial) hwSerial->begin(baudrate);
    #ifdef __AVR__
    if (swSerial) swSerial->begin(baudrate);
    #endif
}


uint8_t SGBotic_PMS5003::readPMS(uint16_t buffer_u16[15]) {
  if (! mySerial->available()) {
    return 0;
  }
    
// Read a byte at a time until we get to the special '0x42' start-byte
  if (mySerial->peek() != PMS5003_STARTBYTE) {
    mySerial->read();
    return 0;
  }   
   
// Now read all 32 bytes
  if (mySerial->available() < 32) {
    return 0;
  }
  uint8_t buffer[32];    
  uint16_t sum = 0;
  mySerial->readBytes(buffer, 32);

// get checksum ready
  for (uint8_t i=0; i<30; i++) {
    sum += buffer[i];
  }
      
#ifdef PMS5003_DEBUG
  for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
    Serial.println();
  }
#endif      
  
// The data comes in endian'd, this solves it so it works on all platforms
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }      
   
  if (sum != buffer_u16[checksum]) {
#ifdef PMS5003_DEBUG
    Serial.println("Checksum failure");
#endif 
    return 0;
  }
      
    return 1;
}


