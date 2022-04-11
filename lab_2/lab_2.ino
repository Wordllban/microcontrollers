const int buttonPin = A0;
const int buttonPinAlgo2 = A1;// the number of the button pin
const int pinsAlgo1[8]  = {10, 9, 8, 7, 6, 5, 4, 3};
const int pinsAlgo2[8] = {3, 5, 7, 9, 4, 6, 8, 10};

void setup() {
  // initialize UART0
     //до яких запуску плат,також в ній ініціалізуємо Є
                                      //підключенна зовнішння перефирія
  Serial.begin(9600);
 
  for (int i = 3; i <= 10  ; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPinAlgo2, INPUT_PULLUP);
}

void loop() {
  // read from port 0:
  if (Serial.available()) {
    int inByte = Serial.read();
    if (inByte == 0xA1) {
      for (int i = 0; i < 8; i++) {
      digitalWrite(pinsAlgo1[i], HIGH);
      delay(850);
      digitalWrite(pinsAlgo1[i], LOW);
      delay(850);
      }
   inByte=0;
  } else if (inByte == 0xB1) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(pinsAlgo2[i], HIGH);
        delay(850);
        digitalWrite(pinsAlgo2[i], LOW);
        delay(850);
      }
    inByte=0;
    }
    
  }

  // write to port 0:
  if(digitalRead(buttonPin)==LOW){
    Serial.write(0xA1);
    delay(200);
  }
  if(digitalRead(buttonPinAlgo2)==LOW){
    Serial.write(0xB1);
    delay(200);
  }
}
