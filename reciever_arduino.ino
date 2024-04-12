const int pinNumber = 8;
int buffer;

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(1200);
  pinMode(pinNumber, OUTPUT);
  //Serial.println("Init");
}

void loop() {


  if (Serial.available() > 0) {
  buffer = Serial.read();

  if(buffer == 49) {
    digitalWrite(pinNumber, HIGH);
  
    delay(6000); // 1000 milliseconds = 1 second
    
    digitalWrite(pinNumber, LOW);

  }
  }
}
