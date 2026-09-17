#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("RECEIVER READY");
}

void loop() {
  if (mySerial.available() > 0) {
    char c = mySerial.read();
    Serial.write(c);
  }
}