#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

class MQTT {
private:
  const char* batteryTopic = "ProjetNichoir/battery";
  const char* imageTopic = "ProjetNichoir/image";
  const char* mqtt_server;
  const int mqtt_port = 1883;

public:
  MQTT(const char* server_address, const char* imageTopic = "ProjetNichoir/image") {
    mqtt_server = server_address;
    imageTopic = imageTopic;
    client.setServer(mqtt_server, mqtt_port);
  }

  void reconnect() {
    while (!client.connected()) {
      Serial.print("Connexion au broker MQTT...");
      String clientId = "ESP32Client";
      clientId += String(random(0xffff), HEX);

      if (client.connect(clientId.c_str())) {
        Serial.println("Connecté au broker MQTT");
      } else {
        Serial.print("Échec, code de retour : ");
        Serial.print(client.state());
        delay(2000);
      }
    }
  }

  void publishBatteryLevel(int batteryLevel) {
    String batteryMessage = String(batteryLevel);
    client.publish(batteryTopic, batteryMessage.c_str());
    Serial.print("Message publié sur le topic 'ProjetNichoir/battery': ");
    Serial.println(batteryLevel);
  }

  void sendBattery(int batteryLevel) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    publishBatteryLevel(batteryLevel);
  }

  void sendImage(String base64Image) {
    if (base64Image != "") {
      if (!client.connected()) {
        reconnect();
      }
      client.loop();

      Serial.println("Sending base64 image...");
      client.beginPublish(imageTopic, base64Image.length(), false);
      client.print(base64Image);
      client.endPublish();

      Serial.println("Image sent successfully!");
    } else {
      Serial.println("Error: Empty image data.");
    }
  }
};
