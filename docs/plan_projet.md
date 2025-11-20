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

- Matériel : ESP32 Timer-Cam M5Stack, PIR, LED IR, batterie, Raspberry Pi, PCB, nichoir 3D.
- Logiciel embarqué : Arduino (C) sur ESP32.
- Backend : Python sur Raspberry Pi (MQTT + DB).
- BDD : MariaDB (modélisation, création, scripts).
- Web : site simple (Flask recommandé) pour galerie + stats batterie.
- Électronique : PCB sous Eagle, intégration dans nichoir imprimé 3D.

## 3. Architecture globale (résumé)

- ESP32 Timer-Cam :
  - États : CONFIG_AP, NORMAL_SLEEP, CAPTURE_EVENT.
  - Lecture batterie (ADC), PIR, LED IR, caméra, WiFi + MQTT.
- Raspberry Pi :
  - Broker MQTT (Mosquitto).
  - Script Python listener (Paho MQTT) → fichiers images + inserts DB.
- Base de données :
  - Table `nichoirs` / `appareils`.
  - Table `captures` (timestamp, chemin image, niveau_batterie, type_event…).
- Site Web :
  - Page d’accueil : liste des nichoirs + dernière capture + état batterie.
  - Page galerie : toutes les captures d’un nichoir.
  - Page détail : image + infos.

## 4. Gestion de la batterie

- Type de batterie choisi : …
- Schéma de mesure : pont diviseur → ADC ESP32.
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
  - A.S. : ESP32, batterie, MQTT côté ESP, PCB…
  - A.A. : Raspberry Pi, DB, site web, 3D…
- Gestion de version :
  - Branches Git : `main`, `Maximilien`, branche de ton binôme.
  - Revue avant merge sur `main`.

## 6. Planning par semaine

- Semaine 1 : environnement, schéma bloc, modélisation BDD, test caméra.
- Semaine 2 : MQTT simple + DB + lecture batterie.
- Semaine 3 : envoi images + site web de base.
- Semaine 4 : deep sleep + optimisation batterie + PCB + 3D.
- Semaine 5 : intégration nichoir + tests + refacto + rapport.

## 7. Livrables

- Code ESP32 propre et commenté.
- Script MQTT + DB sur Raspberry Pi.
- Base de données MariaDB créée (script SQL).
- Site Web minimal fonctionnel.
- PCB Eagle + éventuellement carte soudée.
- Nichoir imprimé 3D avec intégration des composants.
- Rapport final + présentation.
