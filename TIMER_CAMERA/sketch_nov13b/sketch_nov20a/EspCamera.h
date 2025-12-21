#include "M5TimerCAM.h"
#include "base64.h"

struct ImageData {
  uint8_t* buffer = nullptr;  // Pointeur vers les données JPEG (TimerCAM.Camera.fb->buf)
  size_t size = 0;            // Taille de l'image (TimerCAM.Camera.fb->len)
};


class EspCamera {
public:
  EspCamera() {}

  void begin() {
    TimerCAM.begin();

    if (!TimerCAM.Camera.begin()) {
      Serial.println("Camera Init Fail");
      return;
    }
    Serial.println("Camera Init Success");


    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_pixformat(s, PIXFORMAT_JPEG);

    set3MP();
  }


  // 2 MP (1600x1200)
  void set2MP() {
    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_framesize(s, FRAMESIZE_UXGA);
    Serial.println("Résolution : 2MP (UXGA)");
  }

  // 3 MP (2048x1536)
  void set3MP() {
    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_framesize(s, FRAMESIZE_QXGA);
    Serial.println("Résolution : 3MP (QXGA)");
  }


  void flipVertical() {
    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_vflip(s, 1);    // on active le flip vertical
    s->set_hmirror(s, 0);  // pas de miroir horizontal
    Serial.println("Mode : flip vertical");
  }

  // Image miroir gauche/droite (comme un selfie)
  void mirror() {
    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_vflip(s, 0);    // pas de flip vertical
    s->set_hmirror(s, 1);  // on active le miroir horizontal
    Serial.println("Mode : miroir horizontal");
  }

  ImageData TakePicture() {
    ImageData data;

    // 1. Capture de l'image
    if (TimerCAM.Camera.get()) {
      data.size = TimerCAM.Camera.fb->len;
      data.buffer = TimerCAM.Camera.fb->buf;

      Serial.printf("\n--- Capture reussie --- Taille: %d octets\n", data.size);
    } else {
      Serial.println("Erreur de capture de la camera.");
    }
    return data;
  }
  int GetBatteryLevel() {
    int battery = TimerCAM.Power.getBatteryLevel();
    Serial.printf("Bat Voltage: %dmv\r\n", TimerCAM.Power.getBatteryVoltage());
    Serial.printf("Bat Level: %d%%\r\n", TimerCAM.Power.getBatteryLevel());

    return battery;
  }
};