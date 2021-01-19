// this only sometimes works, for unknown reasons
// just connect the RX pin directly instead (pin 0)
#include <SoftwareSerial.h>

SoftwareSerial softSerial(2, 3); // RX pin 2, TX pin 3

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  softSerial.begin(9600);
  delay(1000);
  Serial.println("Ready for commands");
}

void loop() {
  if (Serial.available()) {
    byte receivedByte = 0;
    receivedByte = Serial.read();
    softSerial.write(receivedByte);
    Serial.print("  Sent ");
    Serial.print(receivedByte);
    Serial.println();
  }
}
