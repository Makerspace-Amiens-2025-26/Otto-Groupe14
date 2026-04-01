#include <Arduino.h>
#include <ESP32Servo.h>

// Définition des fréquences des notes de musiques de la 4ème octave
#include "notes.h"
#define DUREE_TEMPS 300  // Durée de chaque note en millisecondes
#define BUZZER_PIN D0  // Définition de la broche du buzzer

Servo legLeft;
Servo legRight;
Servo footLeft;
Servo footRight;

const int trig_pin = D2;
const int echo_pin = D1;
const int pinLegLeft = D7;
const int pinLegRight = D8;
const int pinFootLeft = D9;
const int pinFootRight = D10;


bool debug = false; // Variable pour activer/désactiver les messages de débogage

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

// Fonction qui teste les moteurs de 0 à 180°
void testServos() {
  legLeft.attach(pinLegLeft);
  legRight.attach(pinLegRight);
  footLeft.attach(pinFootLeft);
  footRight.attach(pinFootRight);
  
  Serial.println("Position : 0°");
  legLeft.write(0);
  legRight.write(0);
  footLeft.write(0);
  footRight.write(0);
  delay(1000); 

  Serial.println("Position : 180°");
  legLeft.write(180);
  legRight.write(180);
  footLeft.write(180);
  footRight.write(180);
  delay(1000);
}

void setup() { // Fonction d'initialisation de la carte
  startupMusic();

  Serial.begin(9600);  // Initialisation de la liaison série à 9600 bauds
  Serial.println("Démarrage de la communication série");

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // On indique à la carte sur quelles broches sont branchés les moteurs
  legLeft.attach(pinLegLeft);
  legRight.attach(pinLegRight);
  footLeft.attach(pinFootLeft);
  footRight.attach(pinFootRight);

  testServos(); //On teste les moteurs en les faisant bouger de 0 à 180°

  //On met tous les moteurs à 90°
  legLeft.write(90);
  legRight.write(90);
  footLeft.write(90);
  footRight.write(90);
  
  Serial.println("Calibrage des moteurs terminé");
}


void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH);
  float distance = (duration * 0.0343) / 2;
  if (debug){
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }


  delay(1000);  // Attendre 1 seconde avant d'envoyer à nouveau
}