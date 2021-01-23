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
uint8_t freq_cal = 0; // OSCCAL adjustment
uint8_t note_on = 0; // software note enable

int freq;

void setup() {
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  pinMode(SR_pin, INPUT_PULLUP);
  pinMode(btn_pin, INPUT);
  pinMode(gate_pin, OUTPUT);
  EEPROM.get(0, freq);
  //EEPROM.get(2, freq_cal);
  //OSCCAL = freq_cal;
  mySerial.begin(2400);
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
        case 55: // '7' - increase freq_cal by 1
          freq_cal++;
          break;
        case 56: // '8' - decrease freq_cal by 1
          freq_cal--;
          break;
        case 57: // '9' - turn note on
          note_on = 1;
          break;
        case 58: // ':' - turn note off
          note_on = 0;
          break;
      }
      //OSCCAL = freq_cal;
      //EEPROM.put(2, freq_cal);
      EEPROM.put(0, freq);
    }
    else {
      // do nothing, not this device's address
    }
  }

  // Button pressed or enable from shift register
  //  while ((digitalRead(btn_pin) == LOW) || (digitalRead(SR_pin) == LOW)) {
  if ((digitalRead(btn_pin) == LOW) || note_on) {
    tone(gate_pin, freq);
  }
  if ((!note_on) && (digitalRead(btn_pin) == HIGH)) {
    noTone(gate_pin);
  }
  if (note_on && (digitalRead(btn_pin) == LOW)) {
    note_on = 0;
  }
}

void flush_serial() {
  // purge everything from the serial buffer
  while (mySerial.available())
    mySerial.read();
}
