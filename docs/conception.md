---
layout: default
nav_order: 5
title: Conception et prototypage
---

# Conception et Prototypage

Avoir un code optimisé ne suffit pas si la mécanique ne suit pas. Cette section explique comment nous sommes passés des composants électroniques à un véritable robot de compétition, en utilisant la modélisation 3D sur Onshape, les imprimantes 3D de notre Makerspace, et quelques astuces de bricolage intelligentes.

## 1. Le défi du 5ème moteur

Le kit Otto de base est prévu pour accueillir seulement 4 moteurs (2 pour les jambes, 2 pour les pieds). Pour l'épreuve de Sumo, notre plus grand défi matériel a été de modifier le châssis pour ajouter un 5ème moteur (nommé `pusher` dans notre code, branché sur la broche D3) destiné à animer une arme.

**Notre travail en CAO (Conception Assistée par Ordinateur) :**
Nous avons importé le corps de base du robot sur le logiciel Onshape pour le retravailler. Nous y avons creusé un emplacement sur mesure pour ce nouveau servomoteur. Le choix technique a été de jouer sur les tolérances d'impression (en laissant environ 0.2 mm de marge) pour que le moteur s'encastre. Cela nous évite d'utiliser de la colle et permet de remplacer le moteur facilement s'il casse.

## 2. L'Optimisation des Pieds

Pour aller vite à la course sans trébucher, et pour avoir la force de pousser l'adversaire au Sumo, le robot avait besoin d'une meilleure assise au sol. Le modèle 3D d'origine n'était pas suffisant.

* **L'agrandissement des semelles :** Sur Onshape, nous avons redessiné les pieds pour les faire plus larges et plus longs. Cette plus grande surface de contact offre au robot une stabilité maximale et l'empêche de basculer en avant ou en arrière lors des grosses accélérations.
* **L'ajout de Rubber Gum :** Le plastique PLA imprimé en 3D est dur et glisse énormément sur la piste. Pour gagner de l'adhérence, nous avons découpé des bandes de "rubber gum" (une matière caoutchouteuse) que nous avons fixées à la super glue sous les pieds.
* **L'astuce de prototypage:** Lors de nos premiers essais avec le caoutchouc, nous en avions collé sur toute la surface du pied. Résultat : le robot avait trop de grip, les moteurs n'avaient plus la force de le faire basculer et il faisait du sur-place ! La solution a été de coller les bandes de caoutchouc **uniquement au centre** des pieds. Ainsi, le robot adhère parfaitement pour se propulser quand le pied est plat, mais les extrémités (qui restent en plastique lisse) peuvent pivoter sans forcer lorsque le robot se balance sur les côtés.

## 3. Le Prototypage de l'Arme

Le règlement exige que le robot rentre dans une boîte de 15x15 cm au début du match. Impossible donc de lui mettre un grand bras fixe qui dépasse.

* **Le design de la balayette :** Nous avons dessiné une petite faucheuse, avec une forme de pince à son extrémité, attachée à notre 5ème moteur. Qui rentrait exactement dans les mesures exigées.
* **L'attaque prévue :** Pendant le combat, une pression sur le bouton de notre application devait faire basculer le moteur d'un coup sec à 180° pour tourner la balayette et faucher le robot adverse.
* **L'imprévu du prototypage :** La veille de la compétition, lors de nos derniers tests intensifs sur la piste, la pièce imprimée en 3D de notre balayette a cassé. Face au manque de temps pour réimprimer une pièce plus massive, nous avons pris la décision d'abandonner l'arme.

## 4. L'Électronique et le Câblage

Pour que tout ce matériel communique avec notre code, l'assemblage a demandé une organisation rigoureuse des câbles dans le petit corps imprimé en 3D :

* **La carte cerveau (ESP32) :** Elle gère tout le code et intègre la puce Bluetooth (indispensable pour communiquer avec l'application RemoteXY sur notre téléphone).
* **Les jambes et les pieds :** Branchées sur les broches D7 à D10, elles exécutent notre marche.
* **Le capteur à ultrasons (Les yeux) :** Branché sur les broches D1 (Echo) et D2 (Trig), il permet de mesurer la distance des obstacles (grâce à notre fonction `distance()`).
* **Le Buzzer (Le son) :** Branché sur la broche D0, il nous permet de jouer notre petite musique de démarrage (`startupMusic`). C'est un excellent outil de diagnostic : quand la musique retentit, cela nous confirme que le robot est bien allumé, connecté, et que les moteurs sont verrouillés à leur point d'équilibre avant de le poser sur la ligne de départ.

L'ensemble de ces modifications a validé notre passage du monde virtuel (le code Arduino et les plans Onshape) au monde réel, nous donnant une machine robuste et prête à affronter les épreuves.