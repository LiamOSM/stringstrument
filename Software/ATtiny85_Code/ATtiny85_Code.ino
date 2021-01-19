// A receive-only version of the SoftwareSerial library
#include <SoftwareSerialIn.h>
#include <EEPROM.h>

const uint8_t data_pin   = 0;  // Pin 0 - Data
const uint8_t clock_pin  = 1;  // Pin 1 - Clock
const uint8_t SR_pin     = 2;  // Pin 2 - Shift Register Signal
const uint8_t gate_pin   = 3;  // Pin 3 - MOSFET Gate
const uint8_t btn_pin    = 4;  // Pin 4 - Button
const uint8_t my_address = 'l'; // This device's address

SoftwareSerialIn mySerial(0); // receive on pin 0
uint8_t address_byte = 0;
uint8_t data_byte = 0;

int freq;

void setup() {
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  pinMode(SR_pin, INPUT_PULLUP);
  pinMode(btn_pin, INPUT);
  pinMode(gate_pin, OUTPUT);
  EEPROM.get(0, freq);
  mySerial.begin(9600);
}

void loop() {
  if ((mySerial.available() > 1) && !(mySerial.available() % 2)) { // data available and multiple of two bytes in the buffer
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
      EEPROM.put(0, freq);
    }
    else {
      // do nothing, not this device's address
    }
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
  while (mySerial.available())
    mySerial.read();
}
