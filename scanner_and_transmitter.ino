#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId = "None";
byte nuidPICC[4];
 
void setup(void) 
{
 Serial.begin(9600);
 nfc.begin();
}
 
void loop() 
{
 readNFC();
}
 
void readNFC() 
{

  if (nfc.tagPresent())
  {
    
    NfcTag tag = nfc.read();
    NdefMessage message = tag.getNdefMessage();
    NdefRecord record = message.getRecord(0);
    int payloadLength = record.getPayloadLength();
    byte payload[payloadLength];
    record.getPayload(payload);
    String payloadAsString = "";
    for (int c = 3; c < payloadLength; c++) {
      payloadAsString += (char)payload[c];
    }
    Serial.println("<" + payloadAsString + ">");

  }
  delay(1000);
}
