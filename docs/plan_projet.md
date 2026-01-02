# Plan de projet – Nichoir connecté

## 1. Contexte et objectifs

- Objectif général : construire un nichoir connecté autonome sur batterie capable de :
  - détecter une présence (PIR),
  - prendre une photo avec l’ESP32 Timer-Cam + LED IR,
  - envoyer image + niveau de batterie au Raspberry Pi via MQTT,
  - stocker les données dans MariaDB,
  - afficher une galerie sur un site Web,
  - optimiser l’autonomie batterie (deep sleep, réveils limités, gestion LED IR/WiFi).

## 2. Périmètre du projet

- Matériel : ESP32 Timer-Cam M5Stack, PIR, LED IR, batterie, Raspberry Pi, PCB, nichoir en bois, fixation imprimée en 3D.
- Logiciel embarqué : Arduino (C) sur ESP32.
- Backend : Python sur Raspberry Pi (MQTT + DB).
- BDD : MariaDB (modélisation, création, scripts).
- Web : site simple (Flask) pour galerie + stats batterie.
- Électronique : PCB sous Eagle / Altium, intégration dans le nichoir en bois via fixation imprimée en 3D.

## 3. Architecture globale (résumé)

- ESP32 Timer-Cam :
  - États : NORMAL_SLEEP, CAPTURE_EVENT.
  - Lecture batterie (ADC), PIR, LED IR, caméra, WiFi + MQTT.
- Raspberry Pi :
  - Broker MQTT (Mosquitto).
  - Script Python listener (Paho MQTT) → fichiers images + inserts DB.
- Base de données :
  - Table `captures` (timestamp, chemin image, niveau_batterie, type_event…).
- Site Web :
  - Page d’accueil : possibilité de prendre des photos à distance via le site web. 
  - Page galerie : toutes les captures d’un nichoir avec des filtres (dates, plages de jours) + infos.

## 4. Gestion de la batterie 

- Type de batterie choisi : Lipo
- Stratégie d’économie :
  - Deep sleep la majorité du temps.
  - Réveil par PIR (présence) et par timer (heartbeat batterie).
  - Minimiser le temps WiFi/caméra/LED IR allumés.
- Mesures prévues :
  - Courant en deep sleep / actif,
  - Durée d’un cycle capture,
  - Estimation d’autonomie (formule + hypothèses).

## 5. Organisation du travail

- Binôme :
  - Gestion en duo de chaque tâche.
- Gestion de version :
  - Branches Git : `main`, `Maximilien`, `Mohammed`.
  - Revue avant merge sur `main`.

## 6. Planning par semaine

- Semaine 1 : 
- Semaine 2 : 
- Semaine 3 : 
- Semaine 4 : 
- Semaine 5 : 

## 7. Livrables

- Code ESP32 propre et commenté.
- Script MQTT + DB sur Raspberry Pi.
- Base de données MariaDB créée (script SQL).
- Site Web fonctionnel.
- PCB Eagle / Altium + composants soudés.
- Nichoir en bois (donné) + Support de fixation imprimé en 3D.
- Rapport final + présentation.
