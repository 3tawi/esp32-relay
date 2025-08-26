
#include <Arduino.h>

#undef LED_BUILTIN
#define LED_BUILTIN         2
#define IR_RECEIVE_PIN      13
#define DECODE_NEC

#include <IRremote.hpp> // Arduino-IRremote: https://github.com/Arduino-IRremote/Arduino-IRremote.


#define relay_1 0x54
#define relay_2 0x16
#define relay_3 0x15
#define relay_4 0x50
#define relay_5 0x12
#define relay_6 0x11
#define relay_7 0x4C
#define relay_8 0xE

int relay_pin[8] = {23, 22, 21, 19, 25, 26, 27, 14};
bool relay_state[8];

void SetCommand(uint8_t Comd) {
  switch(Comd) {
    case relay_1:
      relay_state[0] = !relay_state[0];
      digitalWrite(relay_pin[0], relay_state[0]);
      break;
    case relay_2:
      relay_state[1] = !relay_state[1];
      digitalWrite(relay_pin[1], relay_state[1]);
      break;
    case relay_3:
      relay_state[2] = !relay_state[2];
      digitalWrite(relay_pin[2], relay_state[2]);
      break;
    case relay_4:
      relay_state[3] = !relay_state[3];
      digitalWrite(relay_pin[3], relay_state[3]);
      break;
    case relay_5:
      relay_state[4] = !relay_state[4];
      digitalWrite(relay_pin[4], relay_state[4]);
      break;
    case relay_6:
      relay_state[5] = !relay_state[5];
      digitalWrite(relay_pin[5], relay_state[5]);
      break;
    case relay_7:
      relay_state[6] = !relay_state[6];
      digitalWrite(relay_pin[6], relay_state[6]);
      break;
    case relay_8:
      relay_state[7] = !relay_state[7];
      digitalWrite(relay_pin[7], relay_state[7]);
      break;
  }

}
void irReceive() {
  if (IrReceiver.decode()) {
    uint16_t received = IrReceiver.decodedIRData.command;
    if (received) {
      Serial.print("Command: 0x");
      Serial.println(received, HEX);
      SetCommand(received);
    }
    delay(250);
  }
  IrReceiver.resume();
}

void setup() {
  Serial.begin(115200);
  delay(2500);
  for ( int j=0; j<8;j++) {
    pinMode(relay_pin[j], OUTPUT);
    relay_state[j] = true;
    digitalWrite(relay_pin[j], HIGH);
  }
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // data pin 13
}

void loop() {
  irReceive();
  delay(5);
}
