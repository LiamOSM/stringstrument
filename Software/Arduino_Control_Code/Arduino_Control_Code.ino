#include <SoftwareSerial.h>

SoftwareSerial softSerial(2,3); // RX pin 2, TX pin 3

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  Serial.println("Ready for commands");
}

void loop() {


}
