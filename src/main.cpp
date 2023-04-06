#include <Arduino.h>
#include <analogWrite.h>

#define E1A 15
#define E1B 16
#define MA1 6
#define MA2 7
#define MB1 4
#define MB2 5

int stanjeA = 0, staroStanje = 0;
int stevecA = 0;
void motorA(int hitrost);

void encA(void);

void setup()
{
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  Serial.begin(9600);
  attachInterrupt(E1A, encA, RISING);
  analogWrite(MA1, 255);
  analogWrite(MA2, 0);
}

void loop()
{
  motorA(100);
  delay(2000);
  motorA(-200);
  delay(2000);
}

void encA(void){
  if(digitalRead(E1B) == 1)
    stevecA += 1;
  else 
    stevecA -= 1;
  Serial.println(stevecA);
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