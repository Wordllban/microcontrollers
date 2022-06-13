#define RX 19
#define TX 18
#define EN 20

const byte SLAVE1ADRESS = 0x9B;
const byte SLAVE2ADRESS = 0xA5;
byte CRC8LookUpTable[256];

byte getReversedByte(byte byteToReverse) {
   byte reversedByte = 0;
  for (int i = 0; i < 8; i++) {
    bitWrite(reversedByte, i, bitRead(byteToReverse, 7 - i));
  }
  return reversedByte;
}

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

byte calculateCRC(byte bytes[], unsigned char bytesSize) {
  byte crc = 0x00;
  for (unsigned char i = 0; i < bytesSize; i++) {
    byte data = (byte)(bytes[i] ^ crc);
    crc = (byte)(CRC8LookUpTable[data]);
  }
  crc ^= 0x55;
  return crc;
}

bool isMessageDistorted(byte message[50]) {
  unsigned char messageCounter = 0;
  while (messageCounter < 50 && message[messageCounter] != 0) {
    if ((messageCounter + 1) % 5 == 0) {
      byte data[4] = {
        message[messageCounter - 4],
        message[messageCounter - 3],
        message[messageCounter - 2],
        message[messageCounter - 1]
      };
      if (message[messageCounter] != calculateCRC(data, 4)) {
        return true;
      }
    } 
    messageCounter++;
  }
  
  return false;
}

void prepareMessageToUI(byte message[50], byte data[50]) {
  unsigned int messageCounter = 0;
  for (unsigned char i = 0; i < 50; i++) {
    if ((i + 1) % 5 != 0) {
      message[messageCounter] = data[i];
      messageCounter++;
    }
  }
  
}
void sendMessageRequest(byte recevierId) {
  digitalWrite(EN, HIGH);
  Serial1.write(recevierId);
  delay(10);
  digitalWrite(EN, LOW);
}

void setup() {
  generateCRC8LookUpTable(CRC8LookUpTable);
  Serial.begin(9600);
  Serial1.begin(14400);
  pinMode(EN, OUTPUT); 
  delay(10);
}

void loop() {
  if (Serial.available()) {
    int serialRequestInfo = Serial.read();
    if (serialRequestInfo == 0xA1) {
      sendMessageRequest(SLAVE1ADRESS);
      byte receivedMessage[50];
      Serial1.readBytes(receivedMessage, 50);
      bool isDistorted = isMessageDistorted(receivedMessage);
      byte messageToUI[50];
      prepareMessageToUI(messageToUI, receivedMessage);
      Serial.write(0xA1);
      Serial.write(messageToUI, 50);
      if (isDistorted) {
        Serial.write(0x01);
      } else {
        Serial.write(0x00);
      }
    }
    
    if (serialRequestInfo == 0xB1) {
      sendMessageRequest(SLAVE2ADRESS);
      byte receivedMessage[50];
      Serial1.readBytes(receivedMessage, 50);
      bool isDistorted = isMessageDistorted(receivedMessage);
      byte messageToUI[50];
      prepareMessageToUI(messageToUI, receivedMessage);
      Serial.write(0xB1);
      Serial.write(messageToUI, 50);
      
      if (isDistorted) {
        Serial.write(0x01);
      } else {
        Serial.write(0x00);
      }
    }
  }

  
}
