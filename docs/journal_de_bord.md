# Journal de bord – Nichoir connecté

## Séance du 13/11/2025

- **Objectifs** :
  - Se familiariser avec le projet et ses livrables.
  - Étudier la datasheet de l'ESP32 TimerCam.
  - Définir la méthode de travail (individuel ou en binôme pour les tâches).
  - Installer l'environnement de développement (Arduino IDE + bibliothèques nécessaires).
  - Installer Mosquitto et MariaDB sur le Raspberry Pi.

- **Tâches réalisées** :
  - Lecture de la **datasheet ESP32 TimerCam**.
  - Discussion sur la **méthode de travail** : travail en **binôme** sur chaque tâche.
  - **Installation de l'Arduino IDE** et des **bibliothèques ESP32 nécessaires** (T1).
  - **Installation de Mosquitto** et **MariaDB** sur le Raspberry Pi (T2).

- **Problèmes rencontrés** :
  - Trouver la bonne **librairie ESP32**.

- **Décisions prises** :
  - Travailler principalement **en binôme** sur chaque tâche pour mieux comprendre les concepts.

- **Prochaines étapes** :
  - Créer le **dépôt GitHub** pour centraliser le projet.
  - Mettre en place un **project Kanban** pour suivre l'avancement des tâches.
  - Définir et encoder les **issues** sur GitHub pour chaque tâche à réaliser.
  - Finaliser la **structure du projet** (dossiers, documentation, etc.).
  - **T4 :** Réaliser la tâche **T4** (PIR et gestion de la caméra).

---

## Séance du 20/11/2025

- **Objectifs** :
  - Créer le **dépôt GitHub** pour le projet de nichoir.
  - Organiser les **branches de travail** (Maximilien / Mohammed).
  - Créer la structure des dossiers et la documentation de base.

- **Tâches réalisées** :
  - Création du **dépôt GitHub** sous le compte de Maximilien.
  - Ajout des **branches** : `main`, `Maximilien`, `Mohammed`.
  - Mise en place du dossier `docs/` avec :
    - `plan_projet.md` (description du projet),
    - `taches.md` (planning et tâches à faire),
    - `journal_de_bord.md` (pour les retours de chaque séance).
  - Mise en place du **project Kanban** sur GitHub (`ProjetNichoir - Pilotage`).

- **Problèmes rencontrés** :
  - Difficulté à **lier un Project GitHub** d’un autre owner au dépôt. Solution : création d’un nouveau repo sous Maximilien.

- **Décisions prises** :
  - Le dépôt **officiel** du projet sera sous **Maximilien**.
  - Chacun travaillera sur sa **branche dédiée** (`Maximilien` / `Mohammed`).
  - Le suivi des tâches sera fait via le **Project Kanban GitHub** (`ProjetNichoir - Pilotage`).

- **Prochaines étapes** :
  - Ajouter les tâches **T3…Tn** dans le **Project Kanban** (`ProjetNichoir - Pilotage`).
  - Commencer la **modélisation de la base de données MariaDB** (T3).
  - **T5** : Envoi de messages **MQTT simple**.
  - **T6** : Script Python pour **écouter MQTT** et afficher les messages.
  - **T7** : Envoyer une **image + JSON** côté ESP32.

---

## Séance du 27/11/2025

- **Objectifs** :
  - Avancer sur la partie technique (ESP32 + MQTT + RPi + DB).
  - Tester les premières fonctionnalités **T5** et **T6**.
  - **Modélisation de la base de données (T3)**.
  - **T7 :** Envoi d’image + JSON côté ESP32.

- **Tâches réalisées** :
  - **Tests MQTT** : Envoi d'un message simple via ESP32 (T5).
  - **Script Python** qui écoute les messages MQTT et les affiche (T6).
  - Configuration de l'ESP32 pour **envoyer des messages MQTT** à partir du TimerCam (T7).
  - **Modélisation de la base de données MariaDB** (T3).

- **Problèmes rencontrés** :
  - Aucune difficulté majeure sur l’envoi de messages MQTT, mais tests à refaire pour l’envoi d’image.

- **Décisions prises** :
  - **Mosquitto** fonctionne correctement, mais des tests sont à prévoir pour la partie **envoi d’image** via MQTT.
  - Prioriser l’intégration de l’image dans les messages MQTT pour les tests suivants.

- **Prochaines étapes** :
  - **T8** : Sauvegarde de l’image et **insert en DB** côté Raspberry Pi.
  - Démarrage du site web (T9).
  - Finaliser la partie **Deep Sleep** et **réveil PIR/timer** (T10).

---

## Séance du 02/12/2025

- **Objectifs** :
  - Finaliser l’envoi d’images + JSON côté ESP32.
  - Sauvegarde dans la base de données côté Raspberry Pi.
  - Modification de la base de données.
  - Créer le site web (T9).

- **Tâches réalisées** :
  - Modification de la base de données (rajout de tables).
  - Début de la création du site web (T9).

- **Problèmes rencontrés** :
  - Sauvegarde d’image dans MariaDB nécessite l’ajout d’une colonne pour stocker le chemin de l’image.

- **Décisions prises** :
  - Utiliser **base64** pour l’image envoyée par MQTT.
  - Ajouter une colonne **`chemin_image`** dans la base de données MariaDB pour stocker l’emplacement.

- **Prochaines étapes** :
  - Finaliser la **page Flask d’accueil** (T9).
  - Tester le **réveil PIR** et les **cycle Deep Sleep** pour l’optimisation batterie (T10).
  - Ajouter les **tests d’autonomie** pour la batterie (T11).
  - Création AP.

---

## Séance du 04/12/2025

- **Objectifs** :
  - Finaliser l’envoi d’images + JSON côté ESP32.
  - Sauvegarde dans la base de données côté Raspberry Pi.
  - Créer la page **Flask d’accueil** (T9).
  - Création AP.

- **Tâches réalisées** :
  - Finalisation de **T7** : Envoi d’**image + JSON** côté ESP32 (fonctionne en test).
  - **T8** : Sauvegarde de l’image et **insert dans MariaDB** côté Raspberry Pi.
  - Début de la création de la page **Flask d’accueil** (T9).

- **Problèmes rencontrés** :
  - Point d'accès ne fonctionne pas.

- **Décisions prises** :
  - /

- **Prochaines étapes** :
  - Finaliser le site web (T9).
  - Finir AP.
  - Tester le **réveil PIR** et les **cycle Deep Sleep** pour l’optimisation batterie (T10).
  - Ajouter les **tests d’autonomie** pour la batterie (T11).
