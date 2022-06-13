#include <SPI.h>

#define EN 2

const byte ADRESS = 0x9B;
unsigned char signalCounter = 0;

void generateCRC8LookUpTable(byte crc8table[]) {
  const byte polynomial = 0x70;
  for (int divident = 0; divident < 256; divident++) {
    byte currByte = (byte) divident;
    for (byte bit = 0; bit < 8; bit++) {
      if ((currByte & 0x80) != 0) {
        currByte <<= 1;
        currByte ^= polynomial;
      } else {
        currByte <<= 1;
      }
    }
    crc8table[divident] = currByte;
  }
}

byte CRC8LookUpTable[256];

byte calculateCRC(byte bytes[], unsigned char bytesSize) {
  byte crc = 0x00;
  for (unsigned char i = 0; i < bytesSize; i++) {
    byte data = (byte)(bytes[i] ^ crc);
    crc = (byte)(CRC8LookUpTable[data]);
  }
  crc ^= 0x55;
  return crc;
}

void prepareMessage(String text, byte message[50]) {
  unsigned char textCounter = 0, messageCounter = 0;
  while (textCounter < text.length() && messageCounter < 50) {
    if (textCounter % 4 == 0 && textCounter != 0) {
      byte data[4] = {
        message[messageCounter - 4],
        message[messageCounter - 3],
        message[messageCounter - 2],
        message[messageCounter - 1]
      };
      message[messageCounter] = calculateCRC(data, 4);
      messageCounter++;
    } 
    
    message[messageCounter] = (byte) text[textCounter];
    textCounter++;
    messageCounter++;
  }
  int lastBytesCount = text.length() % 4;
  if (lastBytesCount != 0) {
    for(unsigned char i = 0; i < (4 - lastBytesCount); i++) {
       message[messageCounter] = (byte)' ';
       messageCounter++;
    }
    byte data[4] = {
      message[messageCounter - 4],
      message[messageCounter - 3],
      message[messageCounter - 2],
      message[messageCounter - 1]
    };
    message[messageCounter] = calculateCRC(data, 4);
  }
}


byte getTemperature() {
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1));
  digitalWrite(9, LOW);         // CS
  digitalWrite(9, HIGH);        // CS
  byte val = SPI.transfer(0x00);
  delay(50);
  digitalWrite(9, LOW);         // CS
  delay(50);
  SPI.endTransaction();
  return val;  
}

// DELETE DELETE DELETE
char *arr[] = {
               "30.00", "24.00", "25.00",
               "31.00", "32.00", 
              };
int inc=0;

void sendMessage() {
  byte message[50];
  prepareMessage(arr[inc], message);
  
  digitalWrite(EN, HIGH);
  Serial.write(message, 50);
  delay(100);
  digitalWrite(EN, LOW);
}



void setup() { 
  generateCRC8LookUpTable(CRC8LookUpTable);
  Serial.begin(14400);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW); 
  SPI.begin();
}

void loop() {
   if (Serial.available()) {
    byte receiverAddress = (byte)Serial.read();
    if (receiverAddress == ADRESS) {
      delay(20);
      sendMessage();
      inc++;
      if(inc == 4) {
        inc = 0;  
      } 
    }
  }
}
