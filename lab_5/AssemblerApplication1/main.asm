.include "m2560def.inc"
.def _temp1 = r16
.def _temp2 = r17
.def _is_algo_1_on  = r20
.def _is_algo_2_on  = r21
.def _algo_1_counter = r22
.def _algo_2_counter = r23
.def _delay_counter_1 = r24
.def _delay_counter_2 = r25


;==========FLASH==========
  .CSEG
  .org 0x000
  rjmp RESET
  .org 0x0040
  rjmp TIMER3_COMPA

;-----------------------------

ALGO_1:
  ldi ZL, low(algo_1_arr*2)
  ldi ZH, high(algo_1_arr*2)
  clr _temp1
  add ZL, _algo_1_counter
  adc ZH, _temp1
  lpm _temp1, Z
  sts PORTK, _temp1
  inc _algo_1_counter
  cpi _algo_1_counter, 9
  BREQ ALGO_1_END
  ret

ALGO_1_END:
  ldi _is_algo_1_on, 0
  clr _algo_1_counter
  ldi _temp1, 0x00
  sts PORTK, _temp1
  clr _temp1
  ret

ALGO_2:
  ldi ZL, low(algo_2_arr*2)
  ldi ZH, high(algo_2_arr*2)
  clr _temp1
  add ZL, _algo_2_counter
  adc ZH, _temp1
  lpm _temp1, Z
  sts PORTL, _temp1
  inc _algo_2_counter
  cpi _algo_2_counter, 9
  BREQ ALGO_2_END
  ret

ALGO_2_END:
  ldi _is_algo_2_on, 0
  clr _algo_2_counter
  ldi _temp1, 0x00
  sts PORTL, _temp1
  clr _temp1
  ret

TIMER3_COMPA:
  sbrc _is_algo_1_on, 0
  rcall ALGO_1

  sbrc _is_algo_2_on, 0
  rcall ALGO_2
  reti

RESET:
  ;--- PIN NUMBERS ---;
  algo_1_arr: .db 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001
  algo_2_arr: .db 0b00000001, 0b00000100, 0b00010000, 0b01000000, 0b00000010, 0b00001000, 0b00100000, 0b10000000

  ;--- STACK ---;
  ldi _temp1, Low(RAMEND)
  out SPL, _temp1
  ldi _temp1, High(RAMEND)
  out SPH, _temp1

  ;--- DIODS' PINS ---;
  ldi _temp1, 0xFF
  ldi _temp2, 0x00
  sts DDRK, _temp1	  ; OUTPUT
  sts DDRL, _temp1	  ; OUTPUT
  sts PORTK, _temp2	  ; LOW
  sts PORTL, _temp2	  ; LOW

  ;--- BUTTONS & BUZZER ---;
  ldi _temp1, 0b00000001   ; PA0 - OUTPUT
  ldi _temp2, 0b10100000   ; PA7, PA5 - HIGH
  out DDRA, _temp1
  out PORTA, _temp2

  ;--- TIMER3 SETUP ---;
  ldi _temp1, 0x00
  sts TCCR3A, _temp1
  ldi _temp1, (1 << WGM32) | (1 << CS32) | (1 << CS30) ; CTC mode & Prescaler @ 1024
  sts TCCR3B, _temp1
  ldi _temp1, (1 << OCIE3A)
  sts TIMSK3, _temp1
  ldi _temp1, 0xFF
  ldi _temp2, 0xFF
  sts OCR3AL, _temp2
  sts OCR3AH, _temp1

  ;--- MAKE SURE REGISTERS ARE CLEARED ---;
  clr _temp1
  clr _temp2
  clr _is_algo_1_on
  clr _is_algo_2_on 
  clr _algo_1_counter 
  clr _algo_2_counter 
  clr _delay_counter_1 
  clr _delay_counter_2 

  ;--- INITIAL SETUP ---;
  ldi _is_algo_1_on, 0
  ldi _is_algo_2_on, 0
  sei 

;-----------------------------

main:
  sbis PINA, 5
  rcall BUTTON_1

  sbis PINA, 7
  rcall BUTTON_2

  rjmp main    
  
BUTTON_1:
  sbi PORTA, 0
  sbrc _is_algo_1_on, 0
  rjmp STOP_ALGO_1

  sbrs _is_algo_1_on, 0
  rjmp START_ALGO_1

  BUTTON_1_RETURN:
  rcall DELAY
  cbi PORTA, 0
  ret 

START_ALGO_1:
  ldi _is_algo_1_on, 1
  ldi _algo_1_counter, 0
  rjmp BUTTON_1_RETURN

STOP_ALGO_1:
  ldi _is_algo_1_on, 0
  clr _algo_1_counter
  ldi _temp1, 0x00
  sts PORTK, _temp1
  rjmp BUTTON_1_RETURN

BUTTON_2:
  sbi PORTA, 0
  sbrc _is_algo_2_on, 0
  rjmp STOP_ALGO_2

  sbrs _is_algo_2_on, 0
  rjmp START_ALGO_2

  BUTTON_2_RETURN:
  rcall DELAY
  cbi PORTA, 0
  ret               

START_ALGO_2:
  ldi _is_algo_2_on, 1
  ldi _algo_2_counter, 0
  rjmp BUTTON_2_RETURN

STOP_ALGO_2:
  ldi _is_algo_2_on, 0
  clr _algo_2_counter
  ldi _temp1, 0x00
  sts PORTL, _temp1
  rjmp BUTTON_2_RETURN

DELAY:
  ldi _delay_counter_1, 0xFF      
  DELAY_LOOP:                
    subi _delay_counter_1, 1       
    sbci _delay_counter_2, 0          
  brcc DELAY_LOOP                   
  ret               

  .ESEG
