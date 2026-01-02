#include "WifiESP.h"
#include "EspCamera.h"
#include "MQTT.h"
#define led_infrarouge 13

WifiESP wifi;
EspCamera esp;
MQTT mqtt("192.168.1.25");

void WakeFromPIR() {
  pinMode(2, OUTPUT);
  Serial.println("PIR detected!");

  digitalWrite(led_infrarouge, HIGH);
  digitalWrite(2, HIGH);

  ImageData image_data = esp.TakePicture();

  if (image_data.size > 0) {
    mqtt.SendImage(image_data);
  }
  digitalWrite(led_infrarouge, LOW);

  delay(1000);
  
  mqtt.sendBatteryLevel(esp.GetBatteryLevel());
  delay(1000);

  TimerCAM.Power.timerSleep(30);
}
void setup() {
  TimerCAM.begin(true); 
  Serial.begin(115200);

  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);

  pinMode(led_infrarouge, OUTPUT);

  esp.begin();

  bool connection = wifi.isConfigured();

  if (!connection) {
    wifi.beginAP();
    while (!wifi.isConfigured()) {
      wifi.handleClient();
    }
  }

  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  if (reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("ici chef ici");
    WakeFromPIR();
  }

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1);
  esp_deep_sleep_start();
}

void loop() {
}