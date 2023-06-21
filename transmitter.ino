#include <TinyGPS++.h>
#include <RH_RF95.h>

#define GPS_RX_PIN 4
#define GPS_TX_PIN 3
#define LORA_SS_PIN 10
#define LORA_DIO0_PIN 2
#define LORA_BAND 868.0

TinyGPSPlus gps;
RH_RF95 rf95(LORA_SS_PIN, LORA_DIO0_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}

  if (!rf95.init()) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  rf95.setFrequency(LORA_BAND);
}

void loop() {
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isUpdated()) {
        String lat = String(gps.location.lat(), 6);
        String lng = String(gps.location.lng(), 6);
        String message = lat + "," + lng;

        rf95.send((uint8_t *)message.c_str(), message.length());
        rf95.waitPacketSent();
      }
    }
  }
}
