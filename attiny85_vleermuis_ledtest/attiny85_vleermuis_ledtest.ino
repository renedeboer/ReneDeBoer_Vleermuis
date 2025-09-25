/*
  Project: attiny85_vleermuis_ledtest.ino
  Versie: 1.0
  Description: Licht de LEDS 1 voor 1 op voor de ATTINY85 Vleermuis

  Author: @enedeboer
  Date: 01-09-2025
*/

int P1 = 0;
int P2 = 1;
int P3 = 2;
int P4 = 3;
int P5 = 4;

// mapping from LED number (D1..D20) to charlieWrite ID
// Index 0 unused so you can call ledOn(1) for D1, ledOn(20) for D20
// LED number (D1..D20) → Charlie ID
int ledMap[21] = {
  0,   // index 0 unused
  5,   // D1  -> charlie 5
  1,   // D2  -> charlie 1
  10,  // D3  -> charlie 10
  6,   // D4  -> charlie 6
  9,   // D5  -> charlie 9
  2,   // D6  -> charlie 2
  8,   // D7  -> charlie 8
  18,  // D8  -> charlie 18
  14,  // D9  -> charlie 14
  7,   // D10 -> charlie 7
  13,  // D11 -> charlie 13
  3,   // D12 -> charlie 3
  12,  // D13 -> charlie 12
  19,  // D14 -> charlie 19
  17,  // D15 -> charlie 17
  4,   // D16 -> charlie 4
  11,  // D17 -> charlie 11
  15,  // D18 -> charlie 15
  16,  // D19 -> charlie 16
  20   // D20 -> charlie 20
};


//////////////////////////////////////////////////
// Utility functions
//////////////////////////////////////////////////

void high_Z_all() {
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);
  pinMode(P4, INPUT);
  pinMode(P5, INPUT);
}

// Turn one LED on by its number (D1..D20)
void ledOn(int ledNumber) {
  if (ledNumber < 1 || ledNumber > 20) return;
  charlieWrite(ledMap[ledNumber]);
}

// Turn all LEDs off
void ledsOff() {
  charlieWrite(0);
}

// Flash one LED multiple times
void flashLed(int ledNumber, int times, int onTime, int offTime) {
  for (int i = 0; i < times; i++) {
    ledOn(ledNumber);
    delay(onTime);
    ledsOff();
    delay(offTime);
  }
}

// Show a sequence of LEDs with a fixed delay
void sequenceLeds(int start, int end, int delayMs) {
  for (int i = start; i <= end; i++) {
    ledOn(i);
    delay(delayMs);
  }
  ledsOff();
}

//////////////////////////////////////////////////
// Example behavior
//////////////////////////////////////////////////

void setup() {
  // nothing special
}

void loop() {
  // Flash D1 fast 5 times to indicate start
  flashLed(1, 5, 100, 100);

  // Sequence D1..D20 with 1 second delay each
  sequenceLeds(1, 20, 1000);

  delay(1000); // pause before repeating
}

//////////////////////////////////////////////////
// Original charlieWrite function
//////////////////////////////////////////////////

void charlieWrite(int x) {
  high_Z_all();

  switch (x) {
    case 0:  break;
    case 1:  pinMode(P1, OUTPUT); pinMode(P2, OUTPUT); digitalWrite(P1, HIGH); break;
    case 2:  pinMode(P1, OUTPUT); pinMode(P3, OUTPUT); digitalWrite(P1, HIGH); break;
    case 3:  pinMode(P1, OUTPUT); pinMode(P4, OUTPUT); digitalWrite(P1, HIGH); break;
    case 4:  pinMode(P1, OUTPUT); pinMode(P5, OUTPUT); digitalWrite(P1, HIGH); break;
    case 5:  pinMode(P2, OUTPUT); pinMode(P1, OUTPUT); digitalWrite(P2, HIGH); break;
    case 6:  pinMode(P2, OUTPUT); pinMode(P3, OUTPUT); digitalWrite(P2, HIGH); break;
    case 7:  pinMode(P2, OUTPUT); pinMode(P4, OUTPUT); digitalWrite(P2, HIGH); break;
    case 8:  pinMode(P2, OUTPUT); pinMode(P5, OUTPUT); digitalWrite(P2, HIGH); break;
    case 9:  pinMode(P3, OUTPUT); pinMode(P1, OUTPUT); digitalWrite(P3, HIGH); break;
    case 10: pinMode(P3, OUTPUT); pinMode(P2, OUTPUT); digitalWrite(P3, HIGH); break;
    case 11: pinMode(P3, OUTPUT); pinMode(P4, OUTPUT); digitalWrite(P3, HIGH); break;
    case 12: pinMode(P3, OUTPUT); pinMode(P5, OUTPUT); digitalWrite(P3, HIGH); break;
    case 13: pinMode(P4, OUTPUT); pinMode(P1, OUTPUT); digitalWrite(P4, HIGH); break;
    case 14: pinMode(P4, OUTPUT); pinMode(P2, OUTPUT); digitalWrite(P4, HIGH); break;
    case 15: pinMode(P4, OUTPUT); pinMode(P3, OUTPUT); digitalWrite(P4, HIGH); break;
    case 16: pinMode(P4, OUTPUT); pinMode(P5, OUTPUT); digitalWrite(P4, HIGH); break;
    case 17: pinMode(P5, OUTPUT); pinMode(P1, OUTPUT); digitalWrite(P5, HIGH); break;
    case 18: pinMode(P5, OUTPUT); pinMode(P2, OUTPUT); digitalWrite(P5, HIGH); break;
    case 19: pinMode(P5, OUTPUT); pinMode(P3, OUTPUT); digitalWrite(P5, HIGH); break;
    case 20: pinMode(P5, OUTPUT); pinMode(P4, OUTPUT); digitalWrite(P5, HIGH); break;
  }
}
