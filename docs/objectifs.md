---
layout: default
nav_order: 3
title: Objectifs du projet
---

# Introduction

Le projet **Otto-MKS** consiste à concevoir, programmer et assembler un petit robot bipède pour le transformer d'un simple kit éducatif en une véritable machine de compétition, le tout documenté de A à Z pour être facilement reproduit.

## Contexte du Projet

Ce projet est réalisé dans le cadre de nos études au Makerspace d'UniLaSalle Amiens. La particularité de notre démarche est que nous avons dû partir d'une feuille blanche, notamment pour la programmation. L'idée n'était pas de télécharger un projet tout fait sur internet, mais de comprendre comment fonctionne réellement la marche d'un robot, de concevoir nos propres améliorations en 3D sur Onshape, et d'écrire notre propre application de pilotage. Le but final est de s'imposer face aux autres groupes lors de trois épreuves spécifiques : une course de vitesse (Chrono Race), une course d'obstacles (Slalom) et un combat (Sumo).

## Objectifs du Projet

Notre objectif principal est de repousser les limites matérielles du robot. Nous voulons qu'il soit le plus rapide possible, qu'il marche parfaitement droit, et qu'il dispose d'une arme pour le combat. Tout cela doit être facilement pilotable depuis un smartphone, même quand le pilote est sous le stress de la compétition. Pour y arriver, nous devons comprendre les défauts mécaniques du robot et trouver des astuces (en conception 3D ou en code) pour les contourner.

# Existant

Au tout début du projet, ce que l'on nous a fourni se limitait strictement à une base matérielle :
* Les fichiers 3D open-source de la structure de base du robot Otto.
* Les composants électroniques : une carte programmables (ESP32), des petits moteurs bleus standard (servomoteurs SG90), et un capteur/récepteur à ultrasons.
* Un site web (RemoteXY) permettant de dessiner une télécommande pour smartphone.

**Côté logiciel, nous n'avions absolument rien.**

# Cahier des Charges

Pour gagner les épreuves, le règlement nous a imposé des règles strictes qui ont mis en lumière plusieurs défis techniques majeurs. Voici les contraintes identifiées que notre projet final doit résoudre :

**1. Le défi de la Taille (Règle d'homologation)**
* **La règle :** Au lancement de n'importe quelle épreuve, le robot doit impérativement rentrer dans une boîte de mesure de 15x15 cm. 
* **Le défi identifié :** Pour l'épreuve de Sumo, nous voulons ajouter un 5ème moteur pour animer une arme (comme une balayette). Il va falloir concevoir cette arme et son support en 3D pour qu'elle soit efficace en combat, sans pour autant dépasser les 15 cm fatidiques avant le signal de départ. Il faudra aussi modifier la pièce du corps du robot pour insérer ce moteur.

**2. Le défi de la Vitesse (Règle de la Chrono Race)**
* **La règle :** Parcourir une ligne droite le plus rapidement possible.
* **Le défi identifié n°1 (La fluidité) :** Il faut trouver un moyen de programmer la marche pour supprimer les temps de pause. Le mouvement doit devenir fluide et continu pour que le robot arrête de glisser et soit le + efficace possible.
* **Le défi identifié n°2 (La dérive) :** Un robot imprimé en 3D n'est jamais symétrique à 100%. À cause des frottements, il a tendance à dériver en marchant. Nous devons trouver un moyen de corriger ce défaut pour le forcer à marcher parfaitement droit.
* **Le défi identifié n°3 (Les contraintes des moteurs) :** Les petits moteurs SG90 ont une limite physique. Si le programme leur demande d'enchaîner les pas en moins de 200 millisecondes, ils n'ont pas le temps de suivre et se bloquent. Le défi sera de trouver le réglage parfait pour aller le plus vite possible sans faire bloquer la machine.

**3. Le défi du Pilotage (Règle du Sumo)**
* **La règle :** Piloter le robot en direct via le téléphone pour pousser l'adversaire.
* **Le défi identifié :** En condition de combat, si le joystick de l'application est trop sensible, le robot risque de tourner au lieu d'avancer tout droit, ce qui serait fatal. De plus, un faux départ accidentel avant le coup de sifflet est pénalisé. Nous devons donc concevoir une télécommande avec des sécurités pour empêcher les erreurs humaines.

**4. Le défi de l'Agilité (Règle de la Course d'obstacles)**
* **La règle :** Traverser un parcours semé d'obstacles sans les faire tomber.
* **Le défi identifié :** Contrairement à la Chrono Race où l'on fonce tout droit, cette épreuve demande de faire des virages très serrés et de s'arrêter net.
* **L'objectif d'agilité :** Nous devons créer des mouvements de rotation sur place précis (le robot doit pouvoir lever un pied pendant que l'autre pivote le corps), tout en gardant une excellente réactivité pour slalomer de manière fluide.
