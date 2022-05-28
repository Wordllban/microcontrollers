unsigned char current7SegmentsPowerPinIndex = 0;

const bool SevenSegmentsNumsArray[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 }, // 0
  { 0, 1, 1, 0, 0, 0, 0 }, // 1
  { 1, 1, 0, 1, 1, 0, 1 }, // 2
  { 1, 1, 1, 1, 0, 0, 1 }, // 3
  { 0, 1, 1, 0, 0, 1, 1 }, // 4
  { 1, 0, 1, 1, 0, 1, 1 }, // 5
  { 1, 0, 1, 1, 1, 1, 1 }, // 6
  { 1, 1, 1, 0, 0, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1 }, // 8
  { 1, 1, 1, 1, 0, 1, 1 }  // 9
};

const unsigned char SevenSegmentsControlPins[8] = {22, 23, 24, 25, 26, 27, 28, 29};
const unsigned char SevenSegmentsPowerPins[6] = {21, 20, 19, 18, 17, 16};


void printNumber(unsigned char number) {
  if (number < 10) {
    for (unsigned char i = 0; i < 7; i++)
      digitalWrite(SevenSegmentsControlPins[i], SevenSegmentsNumsArray[number][i]);
  }
}

void printAlarmStatus(boolean isActive) {
  if (isActive) {
    for (unsigned char i = 0; i < 7; i++) {
      digitalWrite(SevenSegmentsControlPins[i], SevenSegmentsNumsArray[8][i]);
    }
    digitalWrite(SevenSegmentsControlPins[3], LOW);
  } else {
    for (unsigned char j = 0; j < 7; j++) {
      digitalWrite(SevenSegmentsControlPins[j], SevenSegmentsNumsArray[0][j]);
    }
  }
}

void printAlarmTime(int hours, int minutes, boolean isActive) {
  digitalWrite(SevenSegmentsPowerPins[current7SegmentsPowerPinIndex], LOW);
  if (current7SegmentsPowerPinIndex == 5)
    current7SegmentsPowerPinIndex = 0;
  else
    current7SegmentsPowerPinIndex++;
  digitalWrite(SevenSegmentsPowerPins[current7SegmentsPowerPinIndex], HIGH);

  for (unsigned char i = 0; i < 7; i++)
    digitalWrite(SevenSegmentsControlPins[i], LOW);
  digitalWrite(SevenSegmentsControlPins[7], LOW);
  switch (current7SegmentsPowerPinIndex) {
  case 0:
    printNumber((unsigned char)(hours / 10));
    break;
  case 1:
    printNumber(hours % 10);
    digitalWrite(SevenSegmentsControlPins[7], HIGH);
    break;
  case 2:
    printNumber((unsigned char)(minutes / 10));
    break;
  case 3:
    printNumber(minutes % 10);
    digitalWrite(SevenSegmentsControlPins[7], HIGH);
    break;
  case 4:
    printAlarmStatus(isActive);
    break;
  case 5:
    printAlarmStatus(isActive);
    break;
  }
}
