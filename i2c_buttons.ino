/*
 * Copyright 2022  Cygnix Proto
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <Wire.h>

// Change these to the pins you have your buttons connected to
#define BUTTONA_PIN 13
#define BUTTONB_PIN 12
#define BUTTONC_PIN 11
#define BUTTOND_PIN 10
#define BUTTONE_PIN 9
#define BUTTONF_PIN 8
#define BUTTONG_PIN 7
#define BUTTONH_PIN 6

// Do not modify
#define BUTTONA (1 << 0)
#define BUTTONB (1 << 1)
#define BUTTONC (1 << 2)
#define BUTTOND (1 << 3)
#define BUTTONE (1 << 4)
#define BUTTONF (1 << 5)
#define BUTTONG (1 << 6)
#define BUTTONH (1 << 7)

uint8_t buttonState = 0;

void setup() {
  // Delete any buttons not used here
  pinMode(BUTTONA_PIN, INPUT);
  pinMode(BUTTONB_PIN, INPUT);
  pinMode(BUTTONC_PIN, INPUT);
  pinMode(BUTTOND_PIN, INPUT);
  pinMode(BUTTONE_PIN, INPUT);
  pinMode(BUTTONF_PIN, INPUT);
  pinMode(BUTTONG_PIN, INPUT);
  pinMode(BUTTONH_PIN, INPUT);

  Wire.begin(0x0A);
  Wire.onRequest(requestEvent);
}

void loop() {
  buttonState = 0;

  // Remove any if statements from below for any unused buttons
  if(digitalRead(BUTTONA_PIN) == HIGH) {
    buttonState |= BUTTONA;
  }

  if(digitalRead(BUTTONB_PIN) == HIGH) {
    buttonState |= BUTTONB;
  }

  if(digitalRead(BUTTONC_PIN) == HIGH) {
    buttonState |= BUTTONC;
  }

  if(digitalRead(BUTTOND_PIN) == HIGH) {
    buttonState |= BUTTOND;
  }

  if(digitalRead(BUTTONE_PIN) == HIGH) {
    buttonState |= BUTTONE;
  }

  if(digitalRead(BUTTONF_PIN) == HIGH) {
    buttonState |= BUTTONF;
  }

  if(digitalRead(BUTTONG_PIN) == HIGH) {
    buttonState |= BUTTONG;
  }

  if(digitalRead(BUTTONH_PIN) == HIGH) {
    buttonState |= BUTTONH;
  }

  delay(100); 
}

void requestEvent() {
  Wire.write(buttonState);
}
