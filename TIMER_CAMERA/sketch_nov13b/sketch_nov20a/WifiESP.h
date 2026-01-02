#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Preferences.h>

class WifiESP {

private:
  WebServer server{ 80 };
  const byte DNS_PORT = 53;
  DNSServer dnsServer;
  Preferences prefs;
public:
  WifiESP() {}
  void beginSTA(const char* ssid, const char* password) {

    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);

    Serial.print("Connexion au Wi-Fi : ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      retry++;

      if (retry > 20) {
        Serial.println("\nÉchec de connexion !");
        return;
      }
    }

    Serial.println("\nConnecté !");
    Serial.print("Adresse IP locale : ");
    Serial.println(WiFi.localIP());
  }
  void beginAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP_Config");

    Serial.println("Point d'accès activé (sans mot de passe)");
    Serial.print("SSID : ESP_Config\nIP : ");
    Serial.println(WiFi.softAPIP());

    // Routes
    server.on("/", [this]() {
      handleRoot();
    });
    server.on("/save", [this]() {
      handleSave();
    });

    server.begin();
    Serial.println("Serveur HTTP démarré");

    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    server.onNotFound([this]() {
      handleRoot();
    });
  }

  // ----- PAGE HTML -----
  String getPageHTML() {

    // Scan WiFi
    int n = WiFi.scanNetworks();
    String options = "";

    for (int i = 0; i < n; i++) {
      options += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    }


    String page;

    page += "<!doctype html>";
    page += "<html lang='fr'>";
    page += "<head>";
    page += "<meta charset='utf-8'>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<title>WiFi Config</title>";

    // CSS
    page += "<style>";
    page += "body{font-family:Arial;background:#f8f9fa;height:100vh;"
            "margin:0;display:flex;justify-content:center;align-items:center;}";
    page += ".card{width:320px;background:#fff;padding:20px;border-radius:14px;"
            "box-shadow:0 4px 15px rgba(0,0,0,0.1);}";

    page += "h3{text-align:center;margin-bottom:20px;font-weight:600;color:#333;}";
    page += "label{font-size:14px;font-weight:500;color:#333;margin-bottom:6px;display:block;}";

    page += "select,input{width:100%;padding:10px;border:1px solid #ccc;border-radius:8px;"
            "font-size:15px;box-sizing:border-box;}";

    page += ".btn{margin-top:15px;width:100%;padding:12px;font-size:16px;background:#007BFF;"
            "border:none;border-radius:8px;color:white;font-weight:600;cursor:pointer;}";
    page += ".btn:hover{background:#006BDB;}";
    page += "</style>";

    page += "</head>";
    page += "<body>";

    // Form
    page += "<form action='/save' method='POST' class='card'>";
    page += "<h3>Connexion WiFi</h3>";

    page += "<label for='SSID'>SSID Serveur :</label>";
    page += "<select id='SSID' name='ssid' required>";
    page += "<option selected>Choisissez un réseau</option>";
    page += options;  // Ajout des réseaux détectés
    page += "</select>";

    page += "<label for='Password' style='margin-top:15px;'>Password :</label>";
    page += "<input type='password' id='Password' name='password' required>";

    page += "<button type='submit' class='btn'>Se connecter</button>";

    page += "</form>";
    page += "</body></html>";

    return page;
  }
  // ----- ROUTE "/" -----
  void handleRoot() {
    server.send(200, "text/html", getPageHTML());
  }

  void handleSave() {

    if (server.method() == HTTP_POST) {

      String ssid = server.arg("ssid");
      String password = server.arg("password");

      Serial.println("===== FORMULAIRE REÇU =====");
      Serial.println("SSID     : " + ssid);
      Serial.println("Password : " + password);



      // Page temporaire
      server.send(200, "text/html",
                  "<html><body style='font-family:Arial;text-align:center;'>"
                  "<h3>Connexion en cours...</h3>"
                  "<p>Veuillez patienter...</p>"
                  "</body></html>");

      delay(300);
      saveWifi(ssid, password);

      beginSTA(ssid.c_str(), password.c_str());
      Serial.println("AP désactivé, fonctionnement uniquement en station.");
    }
  }
  void saveWifi(String ssid, String password) {
    prefs.begin("wifi", false);
    prefs.putString("ssid", ssid);
    prefs.putString("pass", password);
    prefs.end();
  }
  void handleClient() {
    server.handleClient();
  }
  bool isConfigured() {
    prefs.begin("wifi", true);

    if (!prefs.isKey("ssid") || !prefs.isKey("pass")) {
      prefs.end();
      return false;
    }

    String ssid = prefs.getString("ssid");
    String password = prefs.getString("pass");

    prefs.end();
    beginSTA(ssid.c_str(), password.c_str());

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(100);
    }
    return (WiFi.status() == WL_CONNECTED);
  }
  void clearWifiPreferences() {
    Serial.println("Effacement des identifiants WiFi...");
    prefs.begin("wifi", false);
    prefs.clear();  // Efface toutes les clés dans l'espace "wifi"
    prefs.end();
    Serial.println("Mémoire WiFi effacée !");
  }
};
