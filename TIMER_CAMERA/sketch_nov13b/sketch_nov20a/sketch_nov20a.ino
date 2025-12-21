#include "WifiESP.h"
#include "EspCamera.h"
#include "MQTT.h"

WifiESP wifi;
EspCamera esp;
MQTT mqtt("172.20.10.4");

void setup() {
  Serial.begin(115200);
  wifi.beginAP();
  
  esp.begin();
}

void loop() {

  wifi.handleClient();
  if (WiFi.status() == WL_CONNECTED) {
    ImageData image_data = esp.TakePicture();

    // 2. Si la photo a été prise avec succès, l'envoyer
    if (image_data.size > 0) {
      mqtt.SendImage(image_data);
    }

    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);  // LOW = réveil
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);  // LOW = réveil

    // esp_deep_sleep_start();
    // Serial.print("fin veille");
  }
}
