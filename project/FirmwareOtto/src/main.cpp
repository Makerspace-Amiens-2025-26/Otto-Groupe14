#include <Arduino.h>
#include <ESP32Servo.h>

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "TigrOtto"
#define REMOTEXY_ACCESS_PASSWORD "tigre"


#include <RemoteXY.h>

// Définition des fréquences des notes de musiques de la 4ème octave
#include "notes.h"
#define DUREE_TEMPS 300  // Durée de chaque note en millisecondes
#define BUZZER_PIN D0  // Définition de la broche du buzzer

Servo legLeft;
Servo legRight;
Servo footLeft;
Servo footRight;
Servo pusher;

const int trig_pin = D2;
const int echo_pin = D1;
const int pinLegLeft = D7;
const int pinLegRight = D8;
const int pinFootLeft = D9;
const int pinFootRight = D10;
const int pinPusher = D3;


bool debug = false; // Variable pour activer/désactiver les messages de débogage

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   // 63 bytes V19 
  { 255,4,0,0,0,56,0,19,0,0,0,84,105,103,114,79,116,116,111,0,
  79,1,106,200,1,1,3,0,2,37,167,32,18,0,2,26,31,31,79,78,
  0,79,70,70,0,5,42,70,60,60,32,2,26,31,1,7,87,24,24,0,
  2,31,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_01; // =1 if switch ON and =0 if OFF, from 0 to 1
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  uint8_t button_01; // =1 if button pressed, else =0, from 0 to 1

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)

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
  Serial.println("Position : 0°");
  legLeft.write(0);
  legRight.write(0);
  footLeft.write(0);
  footRight.write(0);
  pusher.write(0);
  delay(1000); 

  Serial.println("Position : 180°");
  legLeft.write(180);
  legRight.write(180);
  footLeft.write(180);
  footRight.write(180);
  pusher.write(180);
  delay(1000);
}

void distance(){
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
}

// ==========================================
// VARIABLES POUR LA MARCHE (Offsets physiques)
// ==========================================
int centreFootLeft = 90;  // Modifie ces valeurs si le robot
int centreFootRight = 90; // penche ou vrille au repos.
int centreLegLeft = 90;   
int centreLegRight = 90;  
float vitesseCycle = 500.0;
float vitesseRapide = 1000.0;
int stride = 25;             
int liftGauche = 20;         
int liftDroite = 20;
int drift = 15;

void stopRobot() {
  // Remet les 4 moteurs dans leur position de repos (tes variables de centrage)
  footLeft.write(centreFootLeft);
  footRight.write(centreFootRight);
  legLeft.write(centreLegLeft);
  legRight.write(centreLegRight);
}

void marcheAvant() {
  unsigned long tempsActuel = millis();
  float phase = (2.0 * PI * tempsActuel) / vitesseRapide;
  
  float ondePied = sin(phase);
  float ondeJambe = cos(phase);

  // Bascule du poids
  footLeft.write(centreFootLeft - (liftGauche * ondePied));
  footRight.write(centreFootRight - (liftDroite * ondePied));
  
  // Les deux jambes poussent vers l'arrière pour avancer (Signe -)
  legLeft.write(centreLegLeft - (stride * ondeJambe) + drift);
  legRight.write(centreLegRight - (stride * ondeJambe) - drift);
}

void marcheArriere() {
  unsigned long tempsActuel = millis();
  float phase = (2.0 * PI * tempsActuel) / vitesseCycle;
  
  float ondePied = sin(phase);
  float ondeJambe = cos(phase);

  // Bascule du poids (inchangée)
  footLeft.write(centreFootLeft - (liftGauche * ondePied));
  footRight.write(centreFootRight - (liftDroite * ondePied));
  
  // Les deux jambes poussent vers l'avant pour reculer (Signe +)
  legLeft.write(centreLegLeft + (stride * ondeJambe) + drift);
  legRight.write(centreLegRight + (stride * ondeJambe) - drift);
}

void tournerGauche() {
  unsigned long tempsActuel = millis();
  float phase = (2.0 * PI * tempsActuel) / vitesseCycle;
  
  float ondePied = sin(phase);
  float ondeJambe = cos(phase);

  // Bascule du poids
  footLeft.write(centreFootLeft - (liftGauche * ondePied));
  footRight.write(centreFootRight - (liftDroite * ondePied));
  
  // Jambe gauche avance (-), Jambe droite recule (+)
  legLeft.write(centreLegLeft - (stride * ondeJambe));
  legRight.write(centreLegRight + (stride * ondeJambe));
}

void tournerDroite() {
  unsigned long tempsActuel = millis();
  float phase = (2.0 * PI * tempsActuel) / vitesseCycle;
  
  float ondePied = sin(phase);
  float ondeJambe = cos(phase);

  // Bascule du poids
  footLeft.write(centreFootLeft - (liftGauche * ondePied));
  footRight.write(centreFootRight - (liftDroite * ondePied));
  
  // Jambe gauche recule (+), Jambe droite avance (-)
  legLeft.write(centreLegLeft + (stride * ondeJambe));
  legRight.write(centreLegRight - (stride * ondeJambe));
}

void marcheRapide() {
 // 1. Chronomètre et phase
  unsigned long tempsActuel = millis();
  float phase = (2.0 * PI * tempsActuel) / vitesseRapide;
  
  // 2. Calcul des ondes (-1.0 à 1.0)
  float ondePied = sin(phase);
  float ondeJambe = cos(phase);

  // 3. Application aux moteurs avec les Centres Personnalisés
  
  // Les pieds basculent autour de leur propre point zéro
  footLeft.write(centreFootLeft - (liftGauche * ondePied));
  footRight.write(centreFootRight - (liftDroite * ondePied));
  
  // Les jambes s'écartent autour de leur propre point zéro
  legLeft.write(centreLegLeft - (stride * ondeJambe) + drift);
  legRight.write(centreLegRight - (stride * ondeJambe) - drift);
}

void setup() { // Fonction d'initialisation de la carte
  startupMusic();
  RemoteXY_Init();  // initialization by macros 

  Serial.begin(9600);  // Initialisation de la liaison série à 9600 bauds
  Serial.println("Démarrage de la communication série");

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // On indique à la carte sur quelles broches sont branchés les moteurs
  legLeft.attach(pinLegLeft);
  legRight.attach(pinLegRight);
  footLeft.attach(pinFootLeft);
  footRight.attach(pinFootRight);
  pusher.attach(pinPusher);

 // testServos(); //On teste les moteurs en les faisant bouger de 0 à 180°

  //On met tous les moteurs à 90°
  legLeft.write(90);
  legRight.write(90);
  footLeft.write(90);
  footRight.write(90);
  pusher.write(90);
  
  Serial.println("Calibrage des moteurs terminé");
  RemoteXY_delay(2000); // Pause de 2 secondes avant de commencer la boucle principale
}


void loop() {
  RemoteXY_Handler();
  //distance(); // On mesure la distance avec le capteur à ultrasons
  if (RemoteXY.switch_01 == 0) {
    // Le robot avance de manière autonome et fluide
    RemoteXY_delay(1000); // Petite pause pour éviter de surcharger le processeur
    
  }else {
    // ==========================================
    // MODE CONTRÔLE MANUEL
    // ==========================================
    
    // --- A. GESTION DE LA BALAYETTE (Le Bouton 01) ---
    if (RemoteXY.button_01 == 1) {
      pusher.write(180); // Frappe ! (Ajuste l'angle selon ton montage physique)
    } else {
      pusher.write(90);  // Repos (Bras levé ou caché)
    }

    // --- B. GESTION DU DÉPLACEMENT (Le Joystick) ---
    int axeX = RemoteXY.joystick_01_x;
    int axeY = RemoteXY.joystick_01_y;
    int seuil = 50; // Zone morte pour ignorer les tremblements du pouce

    // Marche Avant
    if (axeY > seuil && abs(axeX) < seuil) {
      marcheAvant();
    }
    // Marche Arrière
    else if (axeY < -seuil && abs(axeX) < seuil) {
      // (Il te faudra créer cette fonction en inversant les phases des jambes)
      marcheArriere(); 
    } 
    // Pivot Droite
    else if (axeX > seuil && abs(axeY) < seuil) {
      // (Il te faudra créer une fonction turnRight)
      tournerDroite(); 
    } 
    // Pivot Gauche
    else if (axeX < -seuil && abs(axeY) < seuil) {
      // (Il te faudra créer une fonction turnLeft)
      tournerGauche(); 
    } 
    // Arrêt (Le joystick est au centre ou le pouce a glissé)
    else {
      stopRobot(); 
    }
  }
}
