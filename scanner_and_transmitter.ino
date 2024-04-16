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
    Serial.print('1');
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
  }
  delay(1000);
}
