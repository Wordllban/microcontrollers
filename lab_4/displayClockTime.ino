void printTime(int hours, int minutes, int seconds) {
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
    printNumber((unsigned char)(seconds / 10));
    break;
  case 5:
    printNumber(seconds % 10);
    break;
  }
}
