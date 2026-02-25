#include <Arduino.h>

// Définition des fréquences des notes de musiques de la 4ème octave
#define OCTAVE_4_DO 523
#define OCTAVE_4_RE 587
#define OCTAVE_4_MI 659
#define OCTAVE_4_FA 698
#define OCTAVE_4_SOL 784
#define OCTAVE_4_LA 880
#define OCTAVE_4_SI 988
#define DUREE_TEMPS 300  // Durée de chaque note en millisecondes

#define BUZZER_PIN D0  // Définition de la broche du buzzer


void startupMusic() { // Fonction pour jouer la musique de démarrage
  tone(BUZZER_PIN, OCTAVE_4_DO, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3); // Pause entre les notes
  tone(BUZZER_PIN, OCTAVE_4_DO, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN , OCTAVE_4_DO, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_RE, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_MI, 2 * DUREE_TEMPS);
  delay(2.6 * DUREE_TEMPS);
  tone(BUZZER_PIN, OCTAVE_4_RE, 2 * DUREE_TEMPS);
  delay(2.6 * DUREE_TEMPS);
  tone(BUZZER_PIN, OCTAVE_4_DO, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_MI, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_RE, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_RE, DUREE_TEMPS);
  delay(DUREE_TEMPS*1.3);
  tone(BUZZER_PIN, OCTAVE_4_DO, 4 * DUREE_TEMPS);
  delay(5.2 * DUREE_TEMPS);
  noTone(BUZZER_PIN);    // Silence après la série de sons
}


void setup() { // Fonction d'initialisation de la carte
  startupMusic();
}


void loop() {
  // Rien à faire dans la boucle principale
}