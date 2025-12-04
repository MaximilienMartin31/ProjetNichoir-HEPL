#include "M5TimerCAM.h"
#include "base64.h"  // Assurez-vous d'avoir la bibliothèque base64.h pour l'encodage Base64


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

    // On dit à la caméra qu'on veut des images en JPEG

    sensor_t* s = TimerCAM.Camera.sensor;
    s->set_pixformat(s, PIXFORMAT_JPEG);

    set2MP();
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
  String TakePicture() {
    if (TimerCAM.Camera.get()) {
      Serial.printf("Taille photo : %d octets\n", TimerCAM.Camera.fb->len);

      // Encoder l'image capturée en base64
      String base64Image = base64::encode(TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);  // Encode l'image en base64

      // Libérer la mémoire utilisée par l'image après l'encodage
      TimerCAM.Camera.free();

      // Retourner l'image encodée en base64
      return base64Image;
    } else {
      Serial.println("Capture ratée");
    }

    return "";
  }
  int GetBatteryLevel() {
    int battery = TimerCAM.Power.getBatteryLevel();
    Serial.printf("Bat Voltage: %dmv\r\n", TimerCAM.Power.getBatteryVoltage());
    Serial.printf("Bat Level: %d%%\r\n", TimerCAM.Power.getBatteryLevel());

    return battery;
  }
};
