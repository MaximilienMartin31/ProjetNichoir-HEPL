#include <WiFi.h>

class WifiClientSTA {
private:
  char* ssid;
  char* password;

public:
  WifiClientSTA(char* wifi_ssid, char* wifi_password) 
  {
    ssid = wifi_ssid;
    password = wifi_password;
  }

  void begin() 
  {
    // Mode station (client Wi-Fi)
    WiFi.mode(WIFI_STA);

    Serial.print("Connexion au Wi-Fi : ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
      retry++;

      // Petit timeout de sécurité (10 secondes)
      if (retry > 20) {
        Serial.println("\nEchec de connexion au Wi-Fi !");
        return;
      }
    }

    Serial.println("\nConnecté au Wi-Fi !");
    Serial.print("Adresse IP locale : ");
    Serial.println(WiFi.localIP());
  }
};
