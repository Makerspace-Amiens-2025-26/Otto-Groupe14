---
layout: default
title: Assemblage
parent: Etapes de fabrication
nav_order: 2
---

# Assemblage du Robot Otto-MKS

Cette page détaille le montage physique de notre robot, avec notamment l'ajout du 5ème servomoteur pour l'arme et l'optimisation de l'adhérence.

## 🛠️ Liste du matériel nécessaire

Avant de commencer, assurez-vous d'avoir tous ces éléments sur votre plan de travail :

| Catégorie | Éléments |
| :--- | :--- |
| **Électronique** | 1x ESP32 + Shield d'extension, 4x (ou 5x) Servomoteurs SG90, 1x Capteur HC-SR04, 1x Buzzer, 1x Batterie 9V + Cosse. |
| **Pièces 3D** | 1x Corps, 1x Tête, 2x Jambes, 2x Pieds, 1x Balayette (optionnelle). |
| **Visserie** | Sachets de palonniers et de vis fournis avec les moteurs (vis à bout plat et vis pointues), tournevis de précision. |
| **Consommables** | Super-glue, bandes de Rubber Gum (caoutchouc)|

---

## Étape 1 : Préparation du châssis (Body)
1. Insérez les deux servomoteurs de hanches dans la pièce `Body` (axes vers l'extérieur).
2. **Option Arme :** Insérez le 5ème servomoteur dans l'encoche sur mesure située sur le côté du châssis. L'emplacement est conçu pour un encastrement "en force" (0.2mm de tolérance).
3. Fixez les moteurs à l'aide des vis à **bout pointus**.

## Étape 2 : Jambes et Arme (optionelle)
1. Préparez les jambes et l'arme en insérant les grands palonniers blancs (coupez deux branches pour qu'ils rentrent).
2. Branchez les moteurs à la carte et lancez le code de calibrage pour les bloquer à **90°**.
3. Emboîtez les jambes et l'arme sur les axes pour qu'elles soient parfaitement verticales et vissez-les par l'intérieur avec les vis à **bout plats**.

## Étape 3 : Pieds et Stabilité
1. Insérer les petits palonniers dans les pieds et les visser avec les vis à **bouts plat**.
é. Insérez et visser les deux derniers moteurs dans les pieds élargis avec les vis à **bouts pointus**. Pensez à relancer le code de calibrage des moteurs avant !
3. Faites remonter les câbles à travers les jambes jusqu'au corps.
4. Vissez les moteurs dans les jambe avec les vis à **bouts pointus**
3. Découpez et collez à la super-glue des bandes de **Rubber Gum** uniquement au centre de la semelle. Laissez les bords lisses pour permettre au robot de marcher correctement.

## Étape 4 : Tête et Câblage final
1. Installez le capteur ultrasons (yeux) et le buzzer dans la tête.
2. Raccordez tous les composants à l'ESP32 :
   - Moteurs : D7 à D10 (Jambes) et D3 (Arme).
   - Capteurs : D1, D2 (Ultrasons).
3. Clipsez la tête sur le corps.