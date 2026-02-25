#include <Arduino.h>

#define BUZZER_PIN D0  // Définition de la broche du buzzer

void setup() {
  tone(BUZZER_PIN, 500, 300);  // Émet un son à 500 Hz pendant 300 ms
  delay(500);
  tone(BUZZER_PIN, 1000, 300); // Émet un son à 1000 Hz pendant 300 ms
  delay(500);
  tone(BUZZER_PIN, 1500, 300); // Émet un son à 1500 Hz pendant 300 ms
  delay(500);
  noTone(BUZZER_PIN);          // Silence après la série de sons
}

void loop() {
  // Rien à faire dans la boucle principale
}