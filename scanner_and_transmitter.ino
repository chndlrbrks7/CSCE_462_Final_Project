#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId = "None";
byte nuidPICC[4];

#define transmitPin 2 // Define a digital pin for transmitting data

void setup() {
  pinMode(transmitPin, OUTPUT);
  nfc.begin();
  Serial.begin(1200);
}

void loop() {
  readNFC();
}

void readNFC() {
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    String tagId = tag.getUidString();
    Serial.println(tagId);

    // Transmit the tag ID character by character
    for (int i = 0; i < tagId.length(); i++) {
      char ch = tagId.charAt(i);
      digitalWrite(transmitPin, ch - '0'); // Convert ASCII character to integer
      Serial.println(ch - '0');
      delay(10); // Small delay between transmissions
    }
    digitalWrite(transmitPin, LOW); // Stop transmission
  }
  delay(1000);
}


