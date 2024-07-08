void setup_wifi() {
  String APssid2 = cn_str;
  WiFi.softAP(APssid2.c_str(), "");
  WiFi.mode(WIFI_AP);
  AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
  wifi_ap = true;
  server.begin();
  server_begin();
}

void login() {
  if (!user_login) {
    if ((millis() - prev_login) > 1000) {
      time_login++;
      prev_login = millis();
    }
  }
  else {
    if (wifi_ap == false) {
      String APssid2 = cn_str;
      startAP(APssid2);
      AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
    }
  }

  if (time_login > 300) {
    time_login = 301;
    if (wifi_ap == true) {
      stopAP();
      AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , OFF";
    }
  }

  if (ignition == "ON" and !wifi_ap and time_login > 300) {
    time_login = 0;
    wifi_ap = true;
    user_login = true;
    String APssid2 = cn_str;
    startAP(APssid2);
    AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
  }

  if (ignition == "OFF" and wifi_ap == true) {
    stopAP();
    time_login = 301;
    user_login = 0;
    wifi_ap = false;
    AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , OFF";
  }
}

void loop_wifi() {
  if ((millis() - lastTime) > 500) {
    String get_payload = payload();
    notifyClients(get_payload);
    state = !state;
    lastTime = millis();
  }

  simbol = state;
  ind = state ? " | " : " - ";
}

void startAP(String ssid) {
  Serial.println("Starting AP...");
  WiFi.softAP(ssid.c_str(), "");
  WiFi.mode(WIFI_AP);
  Serial.println("AP Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  wifi_ap = true;
}

void stopAP() {
  Serial.println("Stopping AP...");
  WiFi.softAPdisconnect(true);
  Serial.println("AP Stopped");
  wifi_ap = false;
}
