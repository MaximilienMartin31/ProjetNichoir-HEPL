#include "WifiESP.h"
#include "EspCamera.h"
#include "MQTT.h"

WifiESP wifi;
EspCamera esp;
MQTT mqtt("raspberrypiMohammedalzubaidi.local");

void setup() {
  Serial.begin(115200);
  wifi.beginAP();
  esp.begin();
}

void loop() {

 // Serial.print("debut veille");
  wifi.handleClient();
 // esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);  // LOW = réveil

 // esp_deep_sleep_start();
 // Serial.print("fin veille");



  if (WiFi.status() == WL_CONNECTED) {

    
  }
}
