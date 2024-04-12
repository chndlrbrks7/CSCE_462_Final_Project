//including the library for I2C communication
#include <Wire.h>
//including the library for I2C communication with the PN532 module, library for the PN532 module and the library for the NFC
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
 
//constructors for the library for I2C communication with the module and for the NFC
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);


 
void setup(void) {
 Serial.begin(115200);////serial communication initialization (speed 115200 baud)
 pinMode(13, OUTPUT);
 Serial.println("NDEF Citac"); //displaying a message that the module works as NDEF reader
 nfc.begin();//initialization of communication with the module
}
 
void loop(void) {
 Serial.println("\nSearching for NFC card/tag\n");
 if (nfc.tagPresent())//if we have pressed a card, we are reading a message from it and displaying this message immediately on the Serial monitor.
 {                      
 NfcTag tag = nfc.read(); //reading the NFC card or tag
 tag.print(); //displaying data from the card/tag
 }
 //2 seconds pause so that the read data is not displayed constantly
 delay(2000);
}