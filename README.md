# 🦉 Projet Nichoir Connecté - ESP32 TimerCAM & Raspberry Pi

Ce dépôt contient l’ensemble des ressources matérielles et logicielles pour la réalisation d’un nichoir intelligent. Le système détecte la présence d'un oiseau, capture une image et la transmet via MQTT à un serveur central pour consultation web.

---

## 1. Description du Système

Le projet repose sur l’utilisation d’une **TimerCAM (ESP32)** optimisée pour l'ultra-basse consommation, permettant une autonomie complète sur une saison de nidification.

### Fonctionnalités clés :
- **Détection PIR** : Réveil matériel du système par capteur de mouvement.
- **Capture & Éclairage** : Prise de vue automatique avec support LED IR.
- **Connectivité** : Transmission asynchrone des images et de la télémétrie batterie via MQTT.
- **Interface Web** : Galerie dynamique développée en ASP.NET Core pour le suivi à distance.

---

## 2. Architecture Matérielle

L'électronique est intégrée dans un boîtier sur mesure fixé au plafond du nichoir, orienté verticalement pour une vue zénithale.

- **Microcontrôleur** : ESP32 TimerCAM (M5Stack).
- **Capteur de mouvement** : PIR BS612.
- **Énergie** : Batterie LiPo 2000 mAh. (normalement 3000 --> théorie)
- **Serveur de données** : Raspberry Pi (Broker Mosquitto + Base MariaDB).

---

## 3. Structure du Dépôt

Le projet est organisé comme suit :

- [DataSheet](./DataSheet) : Fiches techniques de l'ESP32, du capteur PIR et des régulateurs.
- [doc](./doc) : Diagrammes (MCD/ERD, algorigrammes, schémas blocs) et rapport final au format PDF.
- [ProjetNichoir](./ProjetNichoir) : Solution Visual Studio (`.slnx`) et code source de la WebApp ASP.NET C# .NET Core.
- [RPI](./RPI) : Scripts Python "Listener" MQTT pour la réception et le stockage des données.
- [TIMER_CAMERA](./TIMER_CAMERA) : Firmware Arduino (`.ino`) et librairies spécifiques (`MQTT.h`, `EspCamera.h`, `WifiESP.h`).
- [LICENSE](./LICENSE) : Fichier de licence du projet.

---

## 4. Bilan Énergétique & Mesures

### Mesures Réelles :
- **Mode Shutdown** : 4 µA (Consommation quasi-nulle entre deux cycles).
- **Mode Deep Sleep** : 800 µA.
- **Mode Actif (Calcul)** : Plateau de **150 mA** mesuré sur une résistance de shunt de 1Ω (150 mV à l'oscilloscope).
- **Mode Actif (Transmission)** : Pics estimés à 250 mA.

**Conclusion** : Avec une consommation journalière réelle optimisée, l'autonomie dépasse largement les **200 jours**, sécurisant ainsi l'objectif initial de 6 mois.

---

## 5. Environnement de travail

### Logiciels utilisés :
- **Arduino IDE** : Pour le flashage de l'ESP32.
- **Visual Studio** : Pour le développement de la plateforme web C#.
- **Python 3** : Pour le script de gestion MQTT sur le Raspberry Pi.
- **Draw.io** : Pour la réalisation des algorigrammes et schémas fonctionnels.

---

## Auteur
Projet réalisé dans le cadre du cours **SmartCities & IoT**, par **[MARTIN Maximilien et AL-ZUBAIDI Mohammed / Groupe 3]**.

Licence : [MIT License](./LICENSE)
