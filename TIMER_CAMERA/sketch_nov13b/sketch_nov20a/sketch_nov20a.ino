#include "WifiClientSTA.h"
#include "EspCamera.h"
#include "MQTT.h"

WifiClientSTA wifiClient("Al-zubaidi Mohammed", "12345678");
EspCamera esp;
MQTT mqtt("raspberrypiMohammedalzubaidi.local");  

void setup() {
  Serial.begin(115200); 
  wifiClient.begin();    
  esp.begin();      
}

void loop() {
  mqtt.sendImage(esp.TakePicture());

  delay (5000);
}
