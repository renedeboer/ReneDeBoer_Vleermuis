/*
  Project: LED_patronen_varianten.ino
  Versie: 1.0
  Description: Diverse effecten voor de ATTINY85 Vleermuis

  Author: @rodedio
  Date: 22-09-2025
*/
  
//////////////////////////////////////////////////
// Pin-definities
//////////////////////////////////////////////////
int P1 = 0;
int P2 = 1;
int P3 = 2;
int P4 = 3;
int P5 = 4;

int ledMap[21] = {
  0, 5,1,10,6,9,2,8,18,14,7,13,3,12,19,17,4,11,15,16,20
};

//////////////////////////////////////////////////
// Basis functies
//////////////////////////////////////////////////
void high_Z_all() {
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);
  pinMode(P4, INPUT);
  pinMode(P5, INPUT);
}

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

void ledOn(int ledNumber) {
  if (ledNumber < 1 || ledNumber > 20) return;
  charlieWrite(ledMap[ledNumber]);
}

void ledsOff() {
  charlieWrite(0);
}

void ledsGroupOn(const int leds[], int count, int durationMs) {
  unsigned long start = millis();
  while (millis() - start < (unsigned long)durationMs) {
    for (int i = 0; i < count; i++) {
      ledOn(leds[i]);
      delay(3);
      ledsOff();
    }
  }
  ledsOff();
}

//////////////////////////////////////////////////
// Variaties
//////////////////////////////////////////////////

void variant1() {
  int g1[]  = {20};
  int g2[]  = {1, 11};
  int g3[]  = {2, 12};
  int g4[]  = {3, 13, 1, 11};
  int g5[]  = {4, 14};
  int g6[]  = {5, 15, 1, 11};
  int g7[]  = {10};
  int g8[]  = {9, 19};
  int g9[]  = {8, 18};
  int g10[] = {7, 17, 1, 11};
  int g11[] = {6, 16};

  ledsGroupOn(g1,  1, 800);
  ledsGroupOn(g2,  2, 200);
  ledsGroupOn(g3,  2, 200);
  ledsGroupOn(g4,  4, 200);
  ledsGroupOn(g5,  2, 200);
  ledsGroupOn(g6,  4, 200);
  ledsGroupOn(g7,  1, 200);
  ledsGroupOn(g8,  2, 200);
  ledsGroupOn(g9,  2, 200);
  ledsGroupOn(g10, 4, 200);
  ledsGroupOn(g11, 2, 200);

  delay(200);
}

void variant2() {
  int g1[] = {6, 16};
  int g2[] = {7, 17, 1, 11};
  int g3[] = {8, 18};
  int g4[] = {9, 19};
  int g5[] = {10};
  int g6[] = {20};

  ledsGroupOn(g1, 2, 200);
  ledsGroupOn(g2, 4, 200);
  ledsGroupOn(g3, 2, 200);
  ledsGroupOn(g4, 2, 200);
  ledsGroupOn(g5, 1, 400);
  ledsGroupOn(g6, 1, 800);

  delay(200);
}

void variant3() {
  int g1[] = {1, 2, 3, 4, 5};
  int g2[] = {6, 7, 8, 9, 10};
  int g3[] = {11, 12, 13, 14, 15};
  int g4[] = {16, 17, 18, 19, 20};

  ledsGroupOn(g1, 5, 300);
  ledsGroupOn(g2, 5, 300);
  ledsGroupOn(g3, 5, 300);
  ledsGroupOn(g4, 5, 300);

  delay(200);
}

void variant4() {
  // springend: eerste en laatste LED naar binnen
  int g1[] = {1, 20};
  int g2[] = {2, 19};
  int g3[] = {3, 18};
  int g4[] = {4, 17};
  int g5[] = {5, 16};

  ledsGroupOn(g1, 2, 200);
  ledsGroupOn(g2, 2, 200);
  ledsGroupOn(g3, 2, 200);
  ledsGroupOn(g4, 2, 200);
  ledsGroupOn(g5, 2, 400);

  delay(200);
}

void variant5() {
  // langzaam alle LEDs achter elkaar aan
  for (int i = 1; i <= 20; i++) {
    int g[] = {i};
    ledsGroupOn(g, 1, 150);
  }
  delay(200);
}

void variant6() {
  // dubbel loopje: 1->10 en 11->20 tegelijk
  for (int i = 1; i <= 10; i++) {
    int g[] = {i, i + 10};
    ledsGroupOn(g, 2, 180);
  }
  delay(200);
}

void variant7() {
  // knipper alle even LEDs tegelijk, daarna alle oneven
  int evenLeds[]  = {2,4,6,8,10,12,14,16,18,20};
  int oddLeds[]   = {1,3,5,7,9,11,13,15,17,19};

  ledsGroupOn(evenLeds, 10, 500);
  ledsGroupOn(oddLeds,  10, 500);

  delay(200);
}

void variant8() {
  // Random sparkle: 20 willekeurige LEDs snel achter elkaar
  for (int i = 0; i < 20; i++) {
    int r = random(1, 21); // LED 1..20
    int g[] = {r};
    ledsGroupOn(g, 1, 120);
  }
  delay(200);
}

//////////////////////////////////////////////////
// Setup en loop
//////////////////////////////////////////////////

void setup() {
  high_Z_all();
  randomSeed(analogRead(A0)); // voor variant8 random
}

void loop() {
  variant1();
  variant2();
  variant3();
  variant4();
  variant5();
  variant6();
  variant7();
  variant8();
}
