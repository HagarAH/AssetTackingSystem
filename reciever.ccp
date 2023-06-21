#include <RH_RF95.h>

#define LORA_SS_PIN 10
#define LORA_DIO0_PIN 2
#define LORA_BAND 868.0

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
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      String received = "";
      for (int i = 0; i < len; i++) {
        received += (char)buf[i];
      }

      Serial.println("Received: " + received);
    }
  }
}
