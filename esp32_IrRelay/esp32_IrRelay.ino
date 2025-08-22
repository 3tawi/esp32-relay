
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

int relay_1_pin = 23;
int relay_2_pin = 22;
int relay_3_pin = 21;
int relay_4_pin = 19;
int relay_5_pin = 14;
int relay_6_pin = 27;
int relay_7_pin = 26;
int relay_8_pin = 25;

bool relay_state_1 = false;
bool relay_state_2 = false;
bool relay_state_3 = false;
bool relay_state_4 = false;
bool relay_state_5 = false;
bool relay_state_6 = false;
bool relay_state_7 = false;
bool relay_state_8 = false;

void SetCommand(uint8_t Comd) {
  switch(Comd) {
    case relay_1:
      relay_state_1 = !relay_state_1;
      digitalWrite(relay_1_pin, relay_state_1);
      break;
    case relay_2:
      relay_state_2 = !relay_state_2;
      digitalWrite(relay_2_pin, relay_state_2);
      break;
    case relay_3:
      relay_state_3 = !relay_state_3;
      digitalWrite(relay_3_pin, relay_state_3);
      break;
    case relay_4:
      relay_state_4 = !relay_state_4;
      digitalWrite(relay_4_pin, relay_state_4);
      break;
    case relay_5:
      relay_state_5 = !relay_state_5;
      digitalWrite(relay_5_pin, relay_state_5);
      break;
    case relay_6:
      relay_state_6 = !relay_state_6;
      digitalWrite(relay_6_pin, relay_state_6);
      break;
    case relay_7:
      relay_state_7 = !relay_state_7;
      digitalWrite(relay_7_pin, relay_state_7);
      break;
    case relay_8:
      relay_state_8 = !relay_state_8;
      digitalWrite(relay_8_pin, relay_state_8);
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
  pinMode(relay_1_pin, OUTPUT);
  pinMode(relay_2_pin, OUTPUT);
  pinMode(relay_3_pin, OUTPUT);
  pinMode(relay_4_pin, OUTPUT);
  pinMode(relay_5_pin, OUTPUT);
  pinMode(relay_6_pin, OUTPUT);
  pinMode(relay_7_pin, OUTPUT);
  pinMode(relay_8_pin, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // data pin 13
}

void loop() {
  irReceive();
  delay(5);
}
