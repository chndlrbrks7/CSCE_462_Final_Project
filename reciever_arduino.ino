const int pinNumber = 8;
int buffer;
#define receivePin 2 // Define a digital pin for receiving data

void setup() {
  pinMode(receivePin, INPUT);
  pinMode(pinNumber, OUTPUT);
  SerialUSB.begin(1200);
}

void loop() {
  readData();
}

void readData() {
  String receivedData = "";

  // Read incoming data character by character
  // while (digitalRead(receivePin) == HIGH) {
  //   char ch = digitalRead(receivePin) + '0'; // Convert integer to ASCII character
  //   receivedData += ch;
  //   SerialUSB.print("Received character: ");
  //   SerialUSB.println(ch);
  //   delay(10); // Small delay between readings
  // }

  while (digitalRead(receivePin) == HIGH) {
    char ch = (char)digitalRead(receivePin); // Convert integer to ASCII character
    receivedData += ch;
    SerialUSB.println(ch);
    delay(10); // Small delay between readings
  }
  // Print received data
  if (!receivedData.equals("")) {
    SerialUSB.println(receivedData);
    digitalWrite(pinNumber, HIGH);
    delay(1000); // 1000 milliseconds = 1 second
    digitalWrite(pinNumber, LOW);
  }

  delay(1000);
}

// void loop() {


//   if (Serial2.available() > 0) {
//   buffer = Serial2.read();

//   if(buffer) {
//     Serial2.print('ACK');
//     digitalWrite(pinNumber, HIGH);

//     delay(6000); // 1000 milliseconds = 1 second
    
//     digitalWrite(pinNumber, LOW);

//   }
//   }
// }
