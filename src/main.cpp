#include <Arduino.h>

int State1_Button = A2;
int State2_Button = A3;
int State3_Button = A4;
int State4_Button = A5;

int LED1 = 12;
int LED2 = 11;
int LED3 = 10;
int LED4 = 9;

bool State1;
bool State2;
bool State3;
bool State4;
bool State1_Cancel;
bool Device_loaded;
bool Device_detonated;

int time_State1;
int time_State3;

void setup() {
  Serial.begin(115200);
  pinMode(State1_Button, INPUT_PULLDOWN);
  pinMode(State2_Button, INPUT_PULLDOWN);
  pinMode(State3_Button, INPUT_PULLDOWN);
  pinMode(State4_Button, INPUT_PULLDOWN);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  State1 = digitalRead(State1_Button);
  State1_Cancel = false;
  Device_loaded = false;
  Device_detonated = false;
  time_State1 = 0;
  time_State3 = 0;
  while (State1 && State1_Cancel == false) {
    delay(100);
    digitalWrite(LED1, HIGH);
    
    if (time_State1 > 30 && Device_loaded == false) {
      Serial.println("Device is loaded");
      Device_loaded = true;
    }

    State1_Cancel = digitalRead(State1_Button);
    if (State1_Cancel && Device_loaded == false) {
      Serial.println("Loading Cancelled");
    }

    time_State1++;

    State2 = digitalRead(State2_Button);
    while (Device_loaded && State2) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);

      State3 = digitalRead(State3_Button);
      while (Device_loaded && State3) {
        digitalWrite(LED2, LOW);
        while (time_State3 < 10 && !Device_detonated) {
          digitalWrite(LED3, LOW);
          delay(150);
          digitalWrite(LED3, HIGH);
          delay(350);
          time_State3++;
          if (time_State3 == 10) {
            Device_detonated = true;            
          }
        }
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);

        State4 = digitalRead(State4_Button);
        if (State4) {
          digitalWrite(LED4, LOW);
          Device_loaded = false;
          State1 = false;
        }
        
      }
    }
  }
  delay(100);
  digitalWrite(LED1, LOW);
}