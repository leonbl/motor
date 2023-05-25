#include <Arduino.h>
#include <analogWrite.h>
#include <PID_v1.h>

#define E1A 15
#define E1B 16
#define MA1 6
#define MA2 7
#define MB1 4
#define MB2 5

int stevecA = 0;
int stariStevec = 0;
int steviloImpulzov = 0;
void motorA(int hitrost);

void encA(void);

// PID
// Setpoint - tista vrednost, ki si jo želimo
// Input - kar smo izmerili, kar v resnici je (se razlikuje od žele vrednosti)
// Output - v našem primeru: izračunana vrednost PWM
double Setpoint, Input, Output;

// Kp, Ki in Kd so konstante, ki jih moraš nastaviti sam glede na obnašanje krmilnika
double Kp=2, Ki=5, Kd=1;

// Inicializacija kmilnika (klic konstruktorja v C++)
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  Serial.begin(9600);
  attachInterrupt(E1A, encA, RISING);
  analogWrite(MA1, 255);
  analogWrite(MA2, 0);
  
  Setpoint = 10;
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255.0, 255.0);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  //motorA(200);    
}

void loop()
{
  steviloImpulzov = stevecA - stariStevec;
  Input = (double) steviloImpulzov;
  if(myPID.Compute()){
    Serial.println(Input);
    stariStevec = stevecA;
    motorA(Output);
  }
}

void encA(void){
  if(digitalRead(E1B) == 1)
    stevecA += 1;
  else 
    stevecA -= 1;
  //Serial.println(stevecA);
}

void motorA(int hitrost){
  if(hitrost>0){
    analogWrite(MA1, hitrost);
    analogWrite(MA2, 0);
  } 
  else if(hitrost<0){
    analogWrite(MA1, 0);
    analogWrite(MA2, abs(hitrost));
  }
  else{
    analogWrite(MA1, 0);
    analogWrite(MA2, 0);
  }
}