#include "WifiClientSTA.h"
#include "EspCamera.h"


WifiClientSTA wifiClient("Al-zubaidi Mohammed", "12345678");
EspCamera esp;



void setup() {
  Serial.begin(115200);
  wifiClient.begin();
  esp.begin();
}

void loop() {
  // ton code après connexion (HTTP, MQTT, etc.)

  esp.GetBatteryLevel();
  delay (1000);


}
