
#include <Arduino.h>

#undef LED_BUILTIN
#define LED_BUILTIN         2
#define IR_RECEIVE_PIN      13
#define DECODE_NEC

#include <IRremote.hpp> // Arduino-IRremote: https://github.com/Arduino-IRremote/Arduino-IRremote.


void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // data pin 13
}

void loop() {
  irReceive();
  delay(5);
}

void irReceive() {
  if (IrReceiver.decode()) {
    uint16_t received = IrReceiver.decodedIRData.command;
    if (received) {
      Serial.print("Command: 0x");
      Serial.println(received, HEX);
    }
    delay(250);
  }
  IrReceiver.resume();
}