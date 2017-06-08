#include "motor_driver.h"
#include "commands.h";

/* encode */
volatile long left_enc_pos = 0L;
volatile long right_enc_pos = 0L;
int left_rotate = 0;
int right_rotate = 0;

void initEncoders(){
  pinMode(19, INPUT);//int4 AL motor_board_p09 //as Left encoder A
  pinMode(18, INPUT);//int5 AR motor_board_p12 //as Left encoder B
  pinMode(2, INPUT); //int0 BL motor_board_p06 //as Right encoder A
  pinMode(3, INPUT); //int1 BR motor_board_p03 //as Right encoder B

  attachInterrupt(4, encoderLeftISR, RISING);
//  attachInterrupt(5, encoderLeftISR, RISING);
  attachInterrupt(0, encoderRightISR, RISING);  
//  attachInterrupt(1, encoderRightISR, RISING);  
}

void encoderLeftISR(){
    if(1==digitalRead(18)){
      left_enc_pos--;
//    }
//    else if(direction(LEFT) == BACKWARDS){
//        left_enc_pos--;
    }else{
        left_enc_pos++;
    }
}

void encoderRightISR(){
    if(1==digitalRead(3)){
      right_enc_pos--;
//    }
//    else if(direction(RIGHT) == BACKWARDS){
//      right_enc_pos--;
    }else{
      right_enc_pos++;
    }
}

  long readEncoder(int i) {
      long encVal = 0L;
  if (i == LEFT)  {
    noInterrupts();
    encVal = left_enc_pos;
    interrupts();
  }
  else {
    noInterrupts();
    encVal = right_enc_pos;
    interrupts();
  }
  return encVal;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      noInterrupts();
      left_enc_pos=0L;
      interrupts();
      return;
    } else { 
      noInterrupts();
      right_enc_pos=0L;
      interrupts();
      return;
    }
  }

void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}
