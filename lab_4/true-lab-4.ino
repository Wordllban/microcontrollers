#include <LiquidCrystal.h>

int pinA = 22;
int pinB = 23;
int pinC = 24;
int pinD = 25;
int pinE = 26;
int pinF = 27;
int pinG = 28;
int dotPin = 29;
int D1 = 21;
int D2 = 20;
int D3 = 19;
int D4 = 18;
int D5 = 17;
int D6 = 16;

int sec = 0;
int minute = 0;
int hour = 0;
int minuteAlarm = 0;
int hourAlarm = 0;

boolean isActive = false;
void displayAlarmTime(void);

int pinInit[] = {
  pinA,
  pinB,
  pinC,
  pinD,
  pinE,
  pinF,
  pinG,
  D1,
  D2,
  D3,
  D4,
  D5,
  D6
};
void setup() {
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(37, OUTPUT);
  for (int i = 0; i < 14; i++) {
    pinMode(pinInit[i], OUTPUT);
  }

  cli();

  // timer1
  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); //CTC mode & Prescaler @ 1024
  TIMSK1 = (1 << OCIE1A);
  OCR1A = 0x0B71; // compare value = 1 sec 

  TCCR2A = 0x00;
  TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS20); //CTC mode & Prescaler @ 1024
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 0x0010; // compare value for 500 Hz

  sei();
}

bool isAlarm = false;

boolean hourButton;
boolean hourFlag = 0;

boolean minuteButton;
boolean minuteFlag = 0;

boolean alarmMenuButton;
boolean alarmMenuButtonFlag = 0;

boolean alarmStatusButton;
boolean alarmStatusButtonFlag = 0;

long buzzerDuration = 15000;
int startTime = millis();

void loop() {
  // HANDLE BUZZER ON ALARM
  if(isActive == true && isAlarm == false) {
    if(hourAlarm == hour && minuteAlarm == minute) {
      while(millis() < startTime + buzzerDuration) {
        digitalWrite(37, HIGH);
        // FORCE ALARM TO STOP
        if(digitalRead(A3) || digitalRead(A4) || digitalRead(A5)  || digitalRead(A6)) {
          break;  
        } 
      }
      digitalWrite(37, LOW);
    }
  }
  
  if(!isAlarm) {
    // HOUR INCREMENT BUTTON
    hourButton = !digitalRead(A3);
    if(hourButton && hourFlag == 0) {
      hour += 1;
      hourFlag = 1;
    }
    if(hourButton == 0 && hourFlag == 1) {
      hourFlag = 0;  
    }

    // MINUTE INCREMENT BUTTON
    minuteButton = !digitalRead(A4);
    if(minuteButton == 1 && minuteFlag == 0) {
      minute += 1;
      minuteFlag = 1;
    }
    if(minuteButton == 0 && minuteFlag == 1) {
      minuteFlag = 0;  
    }
  }

  // GO TO ALARM SETUP MENU
  alarmMenuButton = !digitalRead(A5);
  if(alarmMenuButton == 1 && alarmMenuButtonFlag == 0) {
    isAlarm = !isAlarm;
    alarmMenuButtonFlag = 1;
  }
  if(alarmMenuButton == 0 && alarmMenuButtonFlag == 1) {
    alarmMenuButtonFlag = 0;
  }  

  // SETUP ALARM 
  if(isAlarm) {
    alarmStatusButton = !digitalRead(A6);
    if(alarmStatusButton == 1 && alarmStatusButtonFlag == 0) {
      isActive = !isActive;
      alarmStatusButtonFlag = 1;
    }
    if(alarmStatusButton == 0 && alarmStatusButtonFlag == 1) {
      alarmStatusButtonFlag = 0;  
    }

    // HOUR ALARM INCREMENT BUTTON
    hourButton = !digitalRead(A3);
    if(hourButton && hourFlag == 0) {
      hourAlarm += 1;
      hourFlag = 1;
    }
    if(hourButton == 0 && hourFlag == 1) {
      hourFlag = 0;  
    }

    // MINUTE ALARM INCREMENT BUTTON
    minuteButton = !digitalRead(A4);
    if(minuteButton == 1 && minuteFlag == 0) {
      minuteAlarm += 1;
      minuteFlag = 1;
    }
    if(minuteButton == 0 && minuteFlag == 1) {
      minuteFlag = 0;  
    }
    
  }
  
}

ISR(TIMER1_COMPA_vect) {
  if (sec == 60) {
    sec = 0;
    minute += 1;
  }
  if (minute == 60 && sec == 0) {
    hour += 1;
    minute = 0;
  }
  if (hour == 24 && minute == 0 && sec == 0) {
    hour = 0;
    minute = 0;
    sec = 0;
  }
  if (hour >= 24) {
    hour = 0;
  }
  if (minute >= 60) {
    minute = 0;
  }
  sec += 1;
}

ISR(TIMER2_COMPA_vect) {
  if (isAlarm) {
    printAlarmTime(hourAlarm, minuteAlarm, isActive);
  } else {
    printTime(hour, minute, sec);
  }
}
