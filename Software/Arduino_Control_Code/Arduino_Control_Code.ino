// All this does is blink the on-board LED when a byte is received.
// A blank sketch could also be used, or you could omit the 
// Arduino altogether and just use a USB-TTL cable thingy.

// Connect pin 0 (RX) to the data pin on the PCB

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    Serial.read();
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
}
