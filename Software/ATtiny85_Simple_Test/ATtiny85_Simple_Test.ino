uint8_t data_pin  = 0;  // Pin 0 - Data
uint8_t clock_pin = 1;  // Pin 1 - Clock
uint8_t SR_pin    = 2;  // Pin 2 - Shift Register Signal
uint8_t gate_pin  = 3;  // Pin 3 - MOSFET Gate
uint8_t btn_pin   = 4;  // Pin 4 - Button

// List of note frequencies from F3 to E4
float freq[] = {174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63};

uint8_t note = 11; // This particular microcontroller's pitch

void setup() {
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  pinMode(SR_pin, INPUT);
  pinMode(gate_pin, OUTPUT);
  pinMode(btn_pin, INPUT);
}

void loop() {
  while (digitalRead(btn_pin) == LOW) {
    tone(gate_pin, freq[note]);
  }
  noTone(gate_pin);
}
