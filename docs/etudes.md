---
layout: default
nav_order: 4
title: Études et choix techniques
---

# Études et Choix Techniques

Après avoir identifié les défauts du robot de base et les défis des épreuves, nous avons dû faire des choix techniques forts, particulièrement dans notre programme Arduino. Cette page explique la logique mathématique et logicielle que nous avons utilisée pour rendre notre Otto performant, ainsi que nos décisions de gestion de projet face aux exigences et aux imprévus matériels.

## 1. Le Mouvement

Dans notre premier prototype, nous utilisions la fonction `delay()` (une pause temporelle) entre chaque mouvement. Cela rendait le robot saccadé et l'empêchait de lire la télécommande en temps réel. Nous avions une marche qui se décomposait en 8 temps.

**Notre choix technique :** Nous avons remplacé les pauses par un chronomètre continu (`millis()`) et des ondes mathématiques. 
Dans notre code, la fonction de marche utilise :
* Une onde en **Sinus** (`sin`) pour faire basculer le poids du robot de gauche à droite.
* Une onde en **Cosinus** (`cos`) pour faire avancer et reculer les jambes.

L'avantage de ces deux ondes, c'est qu'elles sont naturellement décalées. Le robot n'a plus besoin de s'arrêter pour changer de mouvement : tout s'enchaîne de manière parfaitement fluide. C'est le secret de notre vitesse.

## 2. Pousser la vitesse sans bloquer les moteurs

Les petits moteurs SG90 ne peuvent pas réagir si on leur demande d'aller plus vite que 200 millisecondes par mouvement. Pour frôler cette limite sans faire trembler ou bloquer le robot, nous avons créé des variables réglables en haut de notre code :
* `vitesseRapide = 500.0;` : C'est le temps total pour faire un cycle de pas complet. Cette valeur était modifié pour adapter le robot à l'épreuve qu'on lui faisait faire.
* `stride = 25;` et `lift = 20;` : Ce sont les amplitudes (respectivement la taille du pas et la hauteur de levée du pied). Plutôt que de faire de très grands pas lents, nous avons choisi de faire de petits pas très rapides, ce qui offre une meilleure adhérence sur la piste.

## 3. Corriger la dérive

Notre robot imprimé en 3D avait tendance à tourner tout seul à cause des frottements mécaniques. Pour le forcer à aller droit, nous avons mis en place deux astuces dans le code :
1. **Les centres personnalisés :** Au lieu de bloquer les moteurs à 90°, nous avons des variables (`centreFootLeft`, `centreLegRight`, etc.) pour régler le point d'équilibre parfait lors du montage.
2. **Le Drift :** Nous avons créé la variable `int drift = 5;`. Dans nos équations de marche, ce chiffre s'ajoute à une jambe et se soustrait à l'autre. Résultat : le robot fait automatiquement un pas un peu plus grand à gauche qu'à droite, ce qui corrige sa trajectoire.

## 4. La Télécommande

Pour l'épreuve de Sumo, le pilotage doit être parfait. L'application RemoteXY nous donne un joystick, mais que nous souhaitions faire fonctionner que dans 4 directions.

**Notre solution :** Dans le code du programme principal, nous avons créé une "zone morte" avec la variable `int seuil = 50;`. 
Le robot ignore tous les petits mouvements du joystick entre -50 et 50. Il ne lance un virage ou la marche avant que si le joystick est poussé franchement à fond. Le joystick réagit ainsi comme 4 vrais boutons directionnels, évitant toutes les erreurs de pilotage.

## 5. L'Arme pour le Sumo
L'objectif initial pour l'épreuve de combat était d'intégrer une balayette en forme de pince animée par un 5ème moteur nommé dans notre code: (`pusher`).

**En théorie:**
L'arme avait été conçue pour respecter la contrainte de taille (15x15 cm). Au démarrage, le moteur restait verrouillé à 90°. Une simple pression sur un bouton de notre interface RemoteXY devait faire basculer le moteur à 180° pour lancer une frappe rapide et déstabiliser l'adversaire.

**La réalité du prototypage :**
Malgré une conception et une programmation fonctionnelles, la pièce imprimée en 3D de notre balayette a cassé la veille de la compétition lors de nos derniers tests. Nous avons donc pris la décision d'**abandonner l'arme**. 
Nous avons préféré retirer ce 5ème moteur de l'assemblage final pour nous concentrer à 100% sur nos points forts validés : la vitesse et la stabilité de notre châssis en corps à corps. Ce qui a par ailleurs été très bénéfique lors de la compétition, ayant été 1er de la phase préliminaire du Sumo, 1er de la Chrono Race et 3e du Slalom. Cela justifie le fait de ne pas l'avoir rajoutée avant la publication de notre projet.