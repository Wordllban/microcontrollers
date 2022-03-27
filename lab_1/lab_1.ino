boolean butt_flag = 0;
boolean butt;
boolean led_flag = 0;
unsigned long last_press;
int LEDnumber = 10;

void setup() {
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
}

void loop() {
  butt = !digitalRead(A0);
  if (butt == 1 && butt_flag == 0 && millis() - last_press > 200) {
    for (LEDnumber; LEDnumber >= 3; LEDnumber--) {
      digitalWrite(LEDnumber, 1);
      delay(850);
      digitalWrite(LEDnumber, 0);
      delay(850);
    }
    last_press = millis();
    butt_flag = 1;
  }

  if (butt == 0 && butt_flag == 1) {
    LEDnumber = 10;
    butt_flag = 0;
  }
}
