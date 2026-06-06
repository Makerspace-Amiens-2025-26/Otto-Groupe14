---
layout: default
title: Etape 1 - Préparation & Impressions
parent: Fabriquer Notre Robot !
nav_order: 1
---

# Étape 1 - Préparation et Impression 3D

Avant de visser la moindre pièce ou de brancher le moindre câble, la réussite de notre robot repose sur une préparation rigoureuse. Cette première étape rassemble tout ce dont vous aurez besoin pour démarrer le projet dans de bonnes conditions.

## 1. Liste du Matériel Nécessaire

Voici l'inventaire complet des composants à réunir sur votre plan de travail :

### Composants Électroniques (Le Cerveau et les Muscles)
* **1x Carte ESP32**
* **4x Servomoteurs SG90**
* **1x Servomoteur SG90 supplémentaire** (Optionnel : si vous souhaitez tester notre système d'arme pour le Sumo)
* **1x Capteur à ultrasons HC-SR04**
* **1x Batterie** (et son connecteur)

### Outillage et Consommables
* **1x Tournevis cruciforme de précision**
* **1x Pince coupante** (pour ajuster les palonniers en plastique des moteurs)
* **1x Fer à souder et du fil d'étain** (Requis uniquement si vous installez le 5ème moteur)
* **Du filament PLA** (pour l'impression 3D du corps)
* **De la Super-glue et du Rubber Gum** (caoutchouc pour l'adhérence des pieds)

---

## 2. Logiciels et Machines Utilisés

Pour passer du virtuel au réel, nous avons utilisé les équipements de notre Makerspace et plusieurs logiciels accessibles à tous les étudiants :

* **Conception 3D :** [Onshape](https://www.onshape.com/). Ce logiciel de CAO en ligne nous a permis de modifier le châssis d'origine d'Otto pour répondre à nos contraintes (ajout de l'arme et agrandissement des semelles).
* **Découpage 3D (Slicer) :** OrcaSlicer. Ce logiciel traduit notre modèle 3D en instructions de couches pour l'imprimante.
* **Fabrication :** Une Imprimante 3D (type dépôt de fil fondu / FDM).
* **Programmation :** L'IDE Arduino (pour téléverser notre code C++ dans l'ESP32) et la plateforme en ligne [RemoteXY](https://remotexy.com/) (pour créer l'interface de notre télécommande sur smartphone).

---

## 3. Fichiers 3D : Imprimer notre version TigrOtto

Plutôt que d'utiliser les fichiers standards, nous vous mettons à disposition notre espace de travail Onshape. Il contient toutes nos améliorations mécaniques, prêtes à être exportées (en format `.stl` ou `.step`) pour l'impression.

👉 **[Accéder à notre projet Onshape (Otto Groupe 14)](https://cad.onshape.com/documents/4bcfa44804b55b924cbb133d/w/5e7bed91d1405d67cb91704f/e/3df3aac1875ac242bb4538be)**{: .btn .btn-primary .fs-5 .mb-4 .mb-md-0 }

**Liste des pièces à imprimer depuis notre lien :**
1. **1x Corps (Body) :** Modifié avec une encoche sur mesure (tolérance de 0.2 mm) pour encastrer le 5ème moteur.
2. **2x Pieds (Foot) :** Élargis et allongés pour offrir une meilleure stabilité lors des accélérations.
3. **1x Tête (Head)**
4. **2x Jambes (Leg)**
5. **1x Faucheuse / Balayette (Optionnel) :** L'arme conçue pour l'épreuve de Sumo.

---

## 4. Préparation de la Carte Électronique : La Soudure (Optionnel)

Si vous avez fait le choix d'intégrer le 5ème servomoteur pour animer l'arme, une petite étape de bricolage électronique s'impose. 

La carte fournie de base n'est prévue que pour brancher 4 moteurs. Pour pouvoir connecter la faucheuse sur la broche **D3** (comme défini dans notre code), vous devez **souder un support de broches supplémentaire** directement sur la carte électronique.
* Faites chauffer votre fer à souder.
* Positionnez le support sur les bons trous (GND, 5V, et Signal D3).
* Appliquez l'étain proprement pour fixer les broches. Une soudure propre est indispensable pour éviter un faux contact qui déconnecterait l'arme en plein combat !

---

## 5. L'Étape Cruciale : Le Calibrage Électronique

C'est la règle d'or en robotique : **ne montez jamais un robot sans avoir préparé ses moteurs !**

Avant de passer à l'étape d'assemblage, vous devez impérativement brancher vos servomoteurs SG90 à votre carte ESP32, et la relier à votre ordinateur via USB. 
Ouvrez l'IDE Arduino et téléversez un code de test très simple (la fonction `testServos()` de notre programme final) pour forcer tous vos moteurs à se positionner exactement à **90 degrés** (leur point central / point zéro).

Laissez-les dans cette position. Cela garantit que lorsque vous visserez les jambes et les pieds à l'étape suivante, votre robot sera parfaitement droit et symétrique.