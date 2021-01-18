// A receive-only version of the SoftwareSerial library
#include <SoftwareSerialIn.h>

uint8_t data_pin  = 0;  // Pin 0 - Data
uint8_t clock_pin = 1;  // Pin 1 - Clock
uint8_t SR_pin    = 2;  // Pin 2 - Shift Register Signal
uint8_t gate_pin  = 3;  // Pin 3 - MOSFET Gate
uint8_t btn_pin   = 4;  // Pin 4 - Button
int my_address = 97;     // This device's address

SoftwareSerialIn mySerial(0); // receive on pin 0
int address_byte = 0;
int data_byte = 0;

int freq = 400;

void setup() {
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  pinMode(SR_pin, INPUT_PULLUP);
  pinMode(btn_pin, INPUT);
  pinMode(gate_pin, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available() == 2) { // two bytes available in the buffer
    address_byte = mySerial.read();
    data_byte = mySerial.read();

    if (address_byte == my_address) { // address is this device's address
      switch (data_byte) {
        case 48: // '0' - clear frequency
          freq = 0;
          break;
        case 49: // '1' - decrease frequency by 100
          freq -= 100;
          break;
        case 50: // '2' - decrease frequency by 10
          freq -= 10;
          break;
        case 51: // '3' - decrease frequency by 1
          freq -= 1;
          break;
        case 52: // '4' - increase frequency by 1
          freq += 1;
          break;
        case 53: // '5' - increase frequency by 10
          freq += 10;
          break;
        case 54: // '6' - increase frequency by 100
          freq += 100;
          break;
      }
    }
    else {
      // do nothing, not this device's address
    }
  }
  else if (mySerial.available() > 2) {
    // something has gone horribly wrong!
    flush_serial();
  }

  // Button pressed or enable from shift register
  //  while ((digitalRead(btn_pin) == LOW) || (digitalRead(SR_pin) == LOW)) {
  while ((digitalRead(btn_pin) == LOW)) {
    tone(gate_pin, freq);
  }
  noTone(gate_pin);
}

void flush_serial() {
  // purge everything from the serial buffer
  tone(gate_pin, 1000); // beep to tell me what's happening (debugging)
  while (mySerial.available())
    mySerial.read();
  delay(500);
  noTone(gate_pin);
}
