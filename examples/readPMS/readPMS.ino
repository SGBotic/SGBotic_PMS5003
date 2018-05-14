#include <SGBotic_PMS5003.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX
SGBotic_PMS5003 PMS5003 = SGBotic_PMS5003(&mySerial);

// Hardware serial,
//SGBotic_PMS5003 PMS5003 = SGBotic_PMS5003(&Serial1);

uint16_t PMSdata[data_size];

void setup() {

  Serial.begin(9600);

  PMS5003.begin(9600);
}

void loop() {
  //int pm = PMS5003.readPMS(data);

  if (PMS5003.readPMS(PMSdata))
  {
    Serial.println();
    Serial.println("---------------------------------------");
    Serial.println("Concentration Units (standard)");
    Serial.print("PM 1.0: "); Serial.print(PMSdata[pm10_standard]);
    Serial.print("\t\tPM 2.5: "); Serial.print(PMSdata[pm25_standard]);
    Serial.print("\t\tPM 10: "); Serial.println(PMSdata[pm100_standard]);
    Serial.println("---------------------------------------");
    Serial.println("Concentration Units (environmental)");
    Serial.print("PM 1.0: "); Serial.print(PMSdata[pm10_env]);
    Serial.print("\t\tPM 2.5: "); Serial.print(PMSdata[pm25_env]);
    Serial.print("\t\tPM 10: "); Serial.println(PMSdata[pm100_env]);
    Serial.println("---------------------------------------");
    Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(PMSdata[particles_03um]);
    Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(PMSdata[particles_05um]);
    Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(PMSdata[particles_10um]);
    Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(PMSdata[particles_25um]);
    Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(PMSdata[particles_50um]);
    Serial.print("Particles > 50 um / 0.1L air:"); Serial.println(PMSdata[particles_100um]);
    Serial.println("---------------------------------------");

    delay(500);
  }
}
