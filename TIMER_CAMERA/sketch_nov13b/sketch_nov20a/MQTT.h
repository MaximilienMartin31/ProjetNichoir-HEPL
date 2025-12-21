#include <WiFi.h>
#include <PubSubClient.h>
#include <Base64.h>


WiFiClient espClient;
PubSubClient client(espClient);

class MQTT {
private:
  const char* TOPIC_IMAGE = "ProjetNichoir/image";        // Topic pour les données binaires
  const char* topic_battery = "ProjetNichoir/battery";  // Pour la batterie
  const char* TOPIC_INFO = "ProjetNichoir/info";         // Topic pour START/END
  const char* mqtt_server;                              // Adresse du broker MQTT
  const int mqtt_port = 1883;                           // Port MQTT (généralement 1883)
  const size_t MQTT_CHUNK_SIZE = 1024;
public:
  MQTT(const char* server_address) {
    mqtt_server = server_address;
    client.setServer(mqtt_server, mqtt_port);
    client.setBufferSize(MQTT_CHUNK_SIZE + 200);
  }

  // Méthode pour se reconnecter au broker MQTT
  void reconnect() {
    while (!client.connected()) {
      Serial.print("Connexion au broker MQTT...");
      String clientId = "ESP32Client";
      clientId += String(random(0xffff), HEX);

      // Tentative de connexion au broker
      if (client.connect(clientId.c_str())) {
        Serial.println("Connecté au broker MQTT");
      } else {
        Serial.print("Échec, code de retour : ");
        Serial.print(client.state());
        delay(2000);  // Attente avant de réessayer
      }
    }
  }

  // Publication du niveau de batterie sur le topic MQTT
  void publishBatteryLevel(int batteryLevel) {
    String batteryMessage = String(batteryLevel);  // Convertir l'entier en chaîne
    if (client.publish(topic_battery, batteryMessage.c_str())) {
      Serial.print("Message publié sur le topic 'ProjetNichoir/battery': ");
      Serial.println(batteryLevel);
    } else {
      Serial.println("Erreur lors de la publication du niveau de batterie.");
    }
  }

  // Méthode pour envoyer le niveau de batterie
  void sendBattery(int batteryLevel) {
    if (!client.connected()) {
      reconnect();  // Reconnexion si nécessaire
    }
    client.loop();                      // Maintient la communication active
    publishBatteryLevel(batteryLevel);  // Envoi du message
  }
  // Nécessaire pour les constantes de configuration du paquet et des topics

  // La fonction prend l'objet client MQTT, les données capturées, et l'objet caméra
  // (pour la libération du buffer)
  void SendImage(ImageData& data) {

    if (data.buffer == nullptr || data.size == 0) {
      Serial.println("Envoi annule : Donnees d'image manquantes.");
      return;
    }
    if (!client.connected()) {
      // Appelez la méthode de reconnexion de la classe MQTT.
      // Vous devez avoir une méthode publique 'reconnect()' dans votre classe MQTT.
      reconnect();
    }

    // Récupération des données locales pour la clarté
    size_t image_size = data.size;
    uint8_t* image_buffer = data.buffer;

    // 1. PRÉPARATION DU MESSAGE DE DÉBUT (START)
    // Format : START:TAILLE:MAC_ADDRESS
    String mac = WiFi.macAddress();
    String startMsg = "START:" + String(image_size) + ":" + mac;

    Serial.print("Envoi Info: ");
    Serial.println(startMsg);

    //
    if (!client.publish(TOPIC_INFO, startMsg.c_str())) {
      Serial.println("Erreur: Echec envoi message START!");
      // Continuer l'envoi des fragments est risqué, mais nous allons essayer
    }

    // Petit délai pour laisser le temps au script Python de traiter le START
    delay(200);

    // 2. ENVOI DES DONNÉES PAR MORCEAUX (CHUNKS)
    size_t bytes_sent = 0;

    while (bytes_sent < image_size) {
      // Maintenir la connexion MQTT active
      client.loop();

      size_t chunk_size = image_size - bytes_sent;
      if (chunk_size > MQTT_CHUNK_SIZE) {
        chunk_size = MQTT_CHUNK_SIZE;
      }

      // Envoi du morceau binaire (avec le drapeau 'false' pour conserver la mémoire)
      if (client.publish(TOPIC_IMAGE, image_buffer + bytes_sent, chunk_size, false)) {
        // Succès silencieux
      } else {
        Serial.println("Erreur envoi paquet !");
        // Optionnel : Ajouter une logique de reconnexion ou de retry ici
      }

      bytes_sent += chunk_size;

      // Délai pour éviter la saturation
      delay(20);
    }

    // 3. MESSAGE DE FIN
    client.publish(TOPIC_INFO, "END");
    Serial.println("Transmission terminee.");

    // 4. Libération de la mémoire caméra (CRUCIAL)
    TimerCAM.Camera.free();
    Serial.println("Memoire du buffer liberee.");
  }
};
