/* 
  Copyright 2020 Roman Mindlin <Roman@Mindlin.ru>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  MA 02110-1301, USA.
*/

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Potentiometer
const int P=2;

// Define number of steps per rotation:
const int stepsPerRevolution=2048;

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper=Stepper(stepsPerRevolution, 4, 6, 5, 7);

int r, r_prev, coef, steps, speed;

void setup() {
  // Set the speed to 1 rpm:
  myStepper.setSpeed(1);
  speed=1;

  // Initial potentiomter value
  r_prev=analogRead(P);
  coef=stepsPerRevolution/1024;

  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

static inline int8_t sgn(int val) {
 if (val<0) return -1;
 if (val==0) return 0;
 return 1;
}


void loop() {

  r=analogRead(P);
  steps=(r-r_prev)*coef;

  Serial.print(" r=");
  Serial.print(r);
  Serial.print(" steps=");
  Serial.print(steps);
  Serial.print(" speed=");
  Serial.print(speed);
  Serial.print("\n");

  if (abs(steps)<6) return;
  else if (abs(steps)>=6 and abs(steps)<100) {
    speed = 1;
  }
  else if (abs(steps)>=100 and abs(steps)<300) {
    speed = 3;
  }
  else if (abs(steps)>=300) {
    speed = 5;
  }

  r_prev=r;

  myStepper.setSpeed(speed);
  myStepper.step(steps);
}
