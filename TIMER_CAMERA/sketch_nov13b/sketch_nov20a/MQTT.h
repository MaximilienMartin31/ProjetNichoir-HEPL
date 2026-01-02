#include <WiFi.h>
#include <PubSubClient.h>
#include <Base64.h>


WiFiClient espClient;
PubSubClient client(espClient);

class MQTT {
private:
  const char* TOPIC_IMAGE = "ProjetNichoir/image";      // Topic pour les données binaires
  const char* topic_battery = "ProjetNichoir/battery";  // Pour la batterie
  const char* TOPIC_INFO = "ProjetNichoir/info";        // Topic pour START/END
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
  // Méthode pour envoyer le niveau de batterie
  void sendBatteryLevel(uint8_t batteryLevel) {
    if (!client.connected()) {
      reconnect();  // Reconnexion si nécessaire
    }
    client.loop();                                 // Maintient la communication active
    String batteryMessage = String(batteryLevel);  // Convertir l'entier en chaîne
    if (client.publish(topic_battery, batteryMessage.c_str())) {
      Serial.print("Message publié sur le topic 'ProjetNichoir/battery': ");
      Serial.println(batteryLevel);
    } else {
      Serial.println("Erreur lors de la publication du niveau de batterie.");
    }
  }
  void SendImage(ImageData data) {

    if (!client.connected()) {
      reconnect();
    }

    size_t image_size = data.size;
    uint8_t* image_buffer = data.buffer;

    String mac = WiFi.macAddress();
    String startMsg = "START:" + String(image_size) + ":" + mac;

    Serial.print("Envoi Info: ");
    Serial.println(startMsg);

    if (!client.publish(TOPIC_INFO, startMsg.c_str())) {
      Serial.println("Erreur: Echec envoi message START!");
    }

    delay(200);

    size_t bytes_sent = 0;

    while (bytes_sent < image_size) {
      client.loop();

      size_t chunk_size = image_size - bytes_sent;
      if (chunk_size > MQTT_CHUNK_SIZE) {
        chunk_size = MQTT_CHUNK_SIZE;
      }

      if (client.publish(TOPIC_IMAGE, image_buffer + bytes_sent, chunk_size, false)) {
      } else {
        Serial.println("Erreur envoi paquet !");
      }

      bytes_sent += chunk_size;

      delay(20);
    }

    client.publish(TOPIC_INFO, "END");
    Serial.println("Transmission terminee.");

    TimerCAM.Camera.free();
    Serial.println("Memoire du buffer liberee.");
  }
};
