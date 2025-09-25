/*
  Project: attiny85_vleermuis.ino
  Versie: 1.0
  Description: LED effecten voor de ATTINY85 Vleermuis, standaard meegeleverd script

  Author: @enedeboer
  Date: 01-09-2025
*/

// ------------------ Pin Setup ------------------
int P1 = 0;
int P2 = 1;
int P3 = 2;
int P4 = 3;
int P5 = 4;

int DELAY = 100; 

// ------------------ Helpers ------------------
void high_Z_all() {
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);
  pinMode(P4, INPUT);
  pinMode(P5, INPUT);
}

// ------------------ Mapping ------------------
int ledMap[21] = {
  0,  // dummy index 0
  5,  // LED 1 → eye left
  1,  // LED 2
 10,  // LED 3
  6,  // LED 4
  9,  // LED 5
  2,  // LED 6
  8,  // LED 7
 18,  // LED 8
 14,  // LED 9
  7,  // LED 10
 13,  // LED 11 → eye right
  3,  // LED 12
 12,  // LED 13
 19,  // LED 14
 17,  // LED 15
  4,  // LED 16
 11,  // LED 17
 15,  // LED 18
 16,  // LED 19
 20   // LED 20 → mouth
};

// ------------------ Charlieplexing ------------------
void charlieWrite(int x) {
  high_Z_all();  
  switch(x) {
    case 0: break;
    case 1:  pinMode(P1, OUTPUT); digitalWrite(P1,HIGH); pinMode(P2, OUTPUT); break;
    case 2:  pinMode(P1, OUTPUT); digitalWrite(P1,HIGH); pinMode(P3, OUTPUT); break;
    case 3:  pinMode(P1, OUTPUT); digitalWrite(P1,HIGH); pinMode(P4, OUTPUT); break;
    case 4:  pinMode(P1, OUTPUT); digitalWrite(P1,HIGH); pinMode(P5, OUTPUT); break;
    case 5:  pinMode(P2, OUTPUT); digitalWrite(P2,HIGH); pinMode(P1, OUTPUT); break;
    case 6:  pinMode(P2, OUTPUT); digitalWrite(P2,HIGH); pinMode(P3, OUTPUT); break;
    case 7:  pinMode(P2, OUTPUT); digitalWrite(P2,HIGH); pinMode(P4, OUTPUT); break;
    case 8:  pinMode(P2, OUTPUT); digitalWrite(P2,HIGH); pinMode(P5, OUTPUT); break;
    case 9:  pinMode(P3, OUTPUT); digitalWrite(P3,HIGH); pinMode(P1, OUTPUT); break;
    case 10: pinMode(P3, OUTPUT); digitalWrite(P3,HIGH); pinMode(P2, OUTPUT); break;
    case 11: pinMode(P3, OUTPUT); digitalWrite(P3,HIGH); pinMode(P4, OUTPUT); break;
    case 12: pinMode(P3, OUTPUT); digitalWrite(P3,HIGH); pinMode(P5, OUTPUT); break;
    case 13: pinMode(P4, OUTPUT); digitalWrite(P4,HIGH); pinMode(P1, OUTPUT); break;
    case 14: pinMode(P4, OUTPUT); digitalWrite(P4,HIGH); pinMode(P2, OUTPUT); break;
    case 15: pinMode(P4, OUTPUT); digitalWrite(P4,HIGH); pinMode(P3, OUTPUT); break;
    case 16: pinMode(P4, OUTPUT); digitalWrite(P4,HIGH); pinMode(P5, OUTPUT); break;
    case 17: pinMode(P5, OUTPUT); digitalWrite(P5,HIGH); pinMode(P1, OUTPUT); break;
    case 18: pinMode(P5, OUTPUT); digitalWrite(P5,HIGH); pinMode(P2, OUTPUT); break;
    case 19: pinMode(P5, OUTPUT); digitalWrite(P5,HIGH); pinMode(P3, OUTPUT); break;
    case 20: pinMode(P5, OUTPUT); digitalWrite(P5,HIGH); pinMode(P4, OUTPUT); break;
  }
}

// ------------------ Multiplexing ------------------
void multiplexLEDs(int leds[], int count, int duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    for (int i = 0; i < count; i++) {
      charlieWrite(ledMap[leds[i]]); // map LED number → charlie ID
      delay(5);
    }
  }
}

void ledOnSingle(int led, int time_ms) {
  charlieWrite(ledMap[led]);
  delay(time_ms);
  charlieWrite(0);
}

// ------------------ Effects ------------------
void wakeUp() {
  int eyes[] = {1, 11};
  for(int i=0;i<3;i++) {
    multiplexLEDs(eyes, 2, 200);
    charlieWrite(0);
    delay(200);
  }
  ledOnSingle(20, 300); // mouth
}

void surprise() {
  int leds[] = {1, 11, 20};
  for(int i=0;i<3;i++) {
    multiplexLEDs(leds, 3, 150);
    charlieWrite(0);
    delay(100);
  }
}

void scare() {
  int allLEDs[20];
  for(int j=0;j<20;j++) allLEDs[j] = j+1;
  for(int i=0;i<5;i++) {
    multiplexLEDs(allLEDs, 20, 100);
    charlieWrite(0);
    delay(100);
  }
}

void flyingloop(int cycles, int speed) {
  int leftWing[]  = {2,3,4,5,6,7,8,9};
  int rightWing[] = {12,13,14,15,16,17,18,19};
  int body[] = {1,11,20}; // eyes + mouth

  for(int c=0;c<cycles;c++) {
    for(int i=0;i<8;i++) {
      int leds[] = {leftWing[i], body[0], body[1], body[2]};
      multiplexLEDs(leds, 4, speed);
    }
    for(int i=0;i<8;i++) {
      int leds[] = {rightWing[i], body[0], body[1], body[2]};
      multiplexLEDs(leds, 4, speed);
    }
    ledOnSingle(10, speed*2); // tail flick
  }
}

void flying(int cycles, int speed) {
  int leftWing[]  = {2,3,4,5,6,7,8,9};
  int rightWing[] = {12,13,14,15,16,17,18,19};
  int body[] = {1,11,20}; // eyes + mouth

  for(int c = 0; c < cycles; c++) {
    for(int i = 0; i < 8; i++) {
      // Combine left and right wing LEDs for simultaneous movement
      int leds[5] = {leftWing[i], rightWing[i], body[0], body[1], body[2]};
      multiplexLEDs(leds, 5, speed);
    }

    // Tail flick at the end of each flap
    ledOnSingle(10, speed*2); 
  }
}

// ------------------ Mood System ------------------
int mood = 0;              
unsigned long lastChange;

void setup() {
  randomSeed(analogRead(0));
  lastChange = millis();
}

void loop() {
  if (millis() - lastChange > random(15000, 30000)) {
    mood = random(0, 3);
    lastChange = millis();
  }

  switch (mood) {
    case 0: calmBehavior(); break;
    case 1: playfulBehavior(); break;
    case 2: scaryBehavior(); break;
  }

  delay(random(500, 1500));
}

void calmBehavior() {
  int r = random(0, 10);
  if (r < 3) wakeUp();
  else if (r < 9) flying(random(2,5), random(120,180));
  else surprise();
}

void playfulBehavior() {
  int r = random(0, 10);
  if (r < 5) flying(random(4,7), random(90,140));
  else if (r < 7) surprise();
  else if (r < 9) wakeUp();
  else scare();
}

void scaryBehavior() {
  int r = random(0, 10);
  if (r < 5) scare();
  else if (r < 8) flying(random(5,9), random(70,120));
  else surprise();
}



