int data_pin  = 0;  // Pin 0 - Data
int clock_pin = 1;  // Pin 1 - Clock
int SR_pin    = 2;  // Pin 2 - Shift Register Signal
int gate_pin  = 3;  // Pin 3 - MOSFET Gate
int btn_pin   = 4;  // Pin 4 - Button

int freq = 1000;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
}

void loop() {
  while (digitalRead(btn_pin) == LOW) {
    tone(gate_pin, freq);
  }
  noTone(gate_pin);
}
