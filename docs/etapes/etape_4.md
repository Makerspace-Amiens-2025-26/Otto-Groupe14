---
layout: default
title: Etape 4 - Contrôle & Test
parent: Fabriquer Notre Robot !
nav_order: 4
---

# Étape 5 - Contrôle Qualité et Tests sur Piste

Félicitations, votre TigrOtto est assemblé et programmé ! Cependant, avant de vous lancer dans la Chrono Race ou l'épreuve de Sumo, une phase de test rigoureuse s'impose. En ingénierie, on ne pose jamais un robot directement sur la piste sans avoir vérifié ses systèmes un par un.

Voici notre protocole de test en 3 phases pour valider le fonctionnement de "TigrOtto".

---

## Phase 1 : Tests à vide (Dans les mains)

Pour cette première série de tests, **ne posez pas le robot par terre**. Gardez-le dans vos mains pour éviter qu'il ne tombe de la table ou ne force sur ses moteurs en cas de problème dans le code.

1. **Test d'alimentation et de son :** Allumez la batterie. Vous devez immédiatement entendre notre `startupMusic` jouée par le buzzer. C'est le signal que la carte ESP32 a bien démarré.
2. **Test du calibrage initial :** Dès la fin de la musique, les 4 moteurs des jambes doivent se verrouiller fermement dans leur position de repos. Les jambes doivent être parfaitement droites et les pieds bien à plat. S'il a l'air tordu, revérifiez vos variables `centreFoot` et `centreLeg` dans le code.
3. **Test de connexion Bluetooth :** * Ouvrez l'application **RemoteXY** sur votre smartphone.
   * Ajoutez une connexion Bluetooth et cherchez l'appareil nommé **TigrOtto** (Mot de passe : `tigre`).
   * L'interface de la manette doit s'afficher sur votre écran.

---

## Phase 2 : Tests de l'interface et des sécurités

Toujours en gardant le robot dans les mains, nous allons vérifier que nos sécurités logicielles (le code anti-stress) fonctionnent bien.

1. **Test de l'interrupteur :**
   * Laissez le switch sur **OFF**. Touchez le joystick : le robot doit vous ignorer totalement et rester immobile.
   * Basculez le switch sur **ON** : le robot est maintenant armé et prêt à écouter vos commandes.
2. **Test de la Zone Morte (Deadzone) :**
   * Poussez le joystick très légèrement vers le haut (moins de la moitié). Le robot ne doit rien faire.
   * Poussez-le **franchement à fond** vers le haut : les jambes doivent commencer à s'agiter de manière fluide.
   * Relâchez d'un coup : le robot doit s'arrêter net et se remettre en position droite.

---

## Phase 3 : Tests sur piste (Mouvements et Adhérence)

Il est temps de poser le robot sur la piste pour évaluer ses performances dynamiques et ajuster ses derniers réglages matériels.

1. **Test d'adhérence (Le grip) :**
   * Poussez le joystick en marche avant. Observez bien le contact entre le plastique et le sol. 
   * Grâce à nos semelles élargies et au carré de **Rubber Gum** collé au centre des pieds, le robot ne doit pas glisser, mais se propulser efficacement. Observez les virages : les bords lisses du pied doivent lui permettre de pivoter sans forcer.
2. **Test du "Drift" (La ligne droite) :**
   * Faites avancer le robot sur une longue ligne droite (environ 1 mètre). 
   * S'il dévie petit à petit vers la gauche ou la droite à cause des frottements mécaniques, **ne touchez pas à l'assemblage !**
   * Ouvrez votre code Arduino, trouvez la variable `int drift = 15;` et modifiez cette valeur (augmentez-la ou passez-la en négatif) jusqu'à ce que la compensation mathématique force votre robot à marcher parfaitement droit.
3. **Le Capteur Ultrasons (Optionnel mais recommandé) :**
   * Bien que notre arme ait été retirée pour des raisons de fiabilité mécanique, notre capteur frontal (les yeux) est bien branché. 
   * Si vous activez la variable `debug = true;` dans le code et que vous regardez le Moniteur Série de l'IDE Arduino, vous verrez s'afficher la distance exacte des obstacles en temps réel. Un atout précieux si vous souhaitez un jour automatiser l'épreuve de la course d'obstacles !

---

> 🏆 **Validation Finale :** Tous les tests sont au vert ? La musique fonctionne, le joystick est réactif, le robot marche droit et sans saccades ? 
> **Félicitations, votre TigrOtto est prêt pour la compétition !**
