void data_default()
{
  if (String(readFile(SPIFFS, "/cn_str.txt")) == "") {
    cn_str = "SDFMS SS6";
    writeFile(SPIFFS, "/cn_str.txt", "SDFMS SS6");
  }
  else {
    cn_str = readFile(SPIFFS, "/cn_str.txt");
  }

  writeFile(SPIFFS, "/http_username.txt", "admin");
  writeFile(SPIFFS, "/http_password.txt", "admin");
  writeFile(SPIFFS, "/cn_str.txt", cn_str.c_str());
  writeFile(SPIFFS, "/sn_str.txt", "1234");
  writeFile(SPIFFS, "/ssid_wifi_ap.txt", cn_str.c_str());
  writeFile(SPIFFS, "/pass_wifi_ap.txt", "12345678");
  writeFile(SPIFFS, "/en_fatiq.txt", "false");
  writeFile(SPIFFS, "/en_fms.txt", "false");
  writeFile(SPIFFS, "/brand.txt", "scania");
  writeFile(SPIFFS, "/en_overspeed.txt", "false");
  writeFile(SPIFFS, "/en_lte.txt", "false");
  writeFile(SPIFFS, "/en_traccar.txt", "false");
  writeFile(SPIFFS, "/server_traccar.txt", "fms.ppa-mhu.net");
  writeFile(SPIFFS, "/port_traccar.txt", "5055");
  writeFile(SPIFFS, "/en_http.txt", "false");
  writeFile(SPIFFS, "/server_http.txt", "ss6api.ppa-mhu.net");
  writeFile(SPIFFS, "/resource.txt", "/ppa-device-api/api/device/kemiringan");
  writeFile(SPIFFS, "/en_mqtt.txt", "false");
  writeFile(SPIFFS, "/broker.txt", "103.88.152.49");
  writeFile(SPIFFS, "/user.txt", "device-client");
  writeFile(SPIFFS, "/pass.txt", "yC9QDtWnYM65VERhkswmpT");
  writeFile(SPIFFS, "/interval_mqtt.txt", "5");
  writeFile(SPIFFS, "/interval_http.txt", "10");
  writeFile(SPIFFS, "/interval_traccar.txt", "10");
  writeFile(SPIFFS, "/set_bitrate.txt", "250");
  writeFile(SPIFFS, "/server_ota.txt", "storage.ppa-bib.net");
  writeFile(SPIFFS, "/resource_ota.txt", "/firmware/fms_dt/v1.bin");
  writeFile(SPIFFS, "/firm_ver.txt", firm_ver.c_str());
  writeFile(SPIFFS, "/no_simcard.txt", "08xxxxxxxxxx");
  Serial.println("default ok");
}

void read_setting()
{
  cn_str = readFile(SPIFFS, "/cn_str.txt");
  brand = readFile(SPIFFS, "/brand.txt");

  if (cn_str == "" and brand == "")
  {
    data_default();
    delay(200);
  }

  brand = readFile(SPIFFS, "/brand.txt");
  cn_str = readFile(SPIFFS, "/cn_str.txt");
  sn = readFile(SPIFFS, "/sn_str.txt");
  http_username = readFile(SPIFFS, "/http_username.txt");
  http_password = readFile(SPIFFS, "/http_password.txt");
  ssid_wifi_ap = cn_str;
  ssid_wifi_ap =  readFile(SPIFFS, "/cn_str.txt");
  pass_wifi_ap =  readFile(SPIFFS, "/pass_wifi_ap.txt");
  sn_dev = readFile(SPIFFS, "/sn_dev.txt");
  en_fatiq = readFile(SPIFFS, "/en_fatiq.txt");
  en_fms = readFile(SPIFFS, "/en_fms.txt");
  en_overspeed = readFile(SPIFFS, "/en_overspeed.txt");
  overspeed = readFile(SPIFFS, "/overspeed.txt");
  en_lte = readFile(SPIFFS, "/en_lte.txt");
  en_traccar = readFile(SPIFFS, "/en_traccar.txt");
  server_traccar = readFile(SPIFFS, "/server_traccar.txt");
  port_traccar = readFile(SPIFFS, "/port_traccar.txt");
  en_http = readFile(SPIFFS, "/en_http.txt");
  server_http = readFile(SPIFFS, "/server_http.txt");
  resource = readFile(SPIFFS, "/resource.txt");
  en_mqtt = readFile(SPIFFS, "/en_mqtt.txt");
  broker = readFile(SPIFFS, "/broker.txt");
  user = readFile(SPIFFS, "/user.txt");
  pass = readFile(SPIFFS, "/pass.txt");
  interval_mqtt = readFile(SPIFFS, "/interval_mqtt.txt");
  interval_http = readFile(SPIFFS, "/interval_http.txt");
  interval_traccar = readFile(SPIFFS, "/interval_traccar.txt");
  set_bitrate = readFile(SPIFFS, "/set_bitrate.txt");
  en_anglewarning = readFile(SPIFFS, "/en_anglewarning.txt");
  limit_angle = readFile(SPIFFS, "/limit_angle.txt");
  server_ota = readFile(SPIFFS, "/server_ota.txt");
  resource_ota = readFile(SPIFFS, "/resource_ota.txt");
  last_hm = readFile(SPIFFS, "/last_hm.txt");
  xshift = readFile(SPIFFS, "/xshift.txt").toInt();
  no_simcard = readFile(SPIFFS, "/no_simcard.txt");

  hm = readFile(SPIFFS, "/hm.txt").toInt();
  idle = readFile(SPIFFS, "/idle.txt").toInt();
  standby = readFile(SPIFFS, "/standby.txt").toInt();
  dumping = readFile(SPIFFS, "/dumping.txt").toInt();

  dumping_hmOn = readFile(SPIFFS, "/dumping_hmOn.txt");
  timer_dumpingOn = readFile(SPIFFS, "/timer_dumpingOn.txt");
  tanggal_dumpingOn = readFile(SPIFFS, "/tanggal_dumpingOn.txt");
  timer_dumpingOff = readFile(SPIFFS, "/timer_dumpingOff.txt");
  tanggal_dumpingOff = readFile(SPIFFS, "/tanggal_dumpingOff.txt");

  hm_starting = readFile(SPIFFS, "/hm_starting.txt");
  timer_hmOn = readFile(SPIFFS, "/timer_hmOn.txt");
  tanggal_hmOn = readFile(SPIFFS, "/tanggal_hmOn.txt");
  hm_starting = readFile(SPIFFS, "/hm_starting.txt");
  timer_hmOff = readFile(SPIFFS, "/timer_hmOff.txt");
  tanggal_hmOff = readFile(SPIFFS, "/tanggal_hmOff.txt");

  idle_hmOn = readFile(SPIFFS, "/idle_hmOn.txt");
  timer_idleOn = readFile(SPIFFS, "/timer_idleOn.txt");
  tanggal_idleOn = readFile(SPIFFS, "/tanggal_idleOn.txt");
  idle_hmOn = readFile(SPIFFS, "/idle_hmOn.txt");
  timer_idleOff = readFile(SPIFFS, "/timer_idleOff.txt");
  tanggal_idleOff = readFile(SPIFFS, "/tanggal_idleOff.txt");

  standby_hmOn = readFile(SPIFFS, "/standby_hmOn.txt");
  timer_standbyOn = readFile(SPIFFS, "/timer_standbyOn.txt");
  tanggal_standbyOn = readFile(SPIFFS, "/tanggal_standbyOn.txt");
  standby_hmOn = readFile(SPIFFS, "/standby_hmOn.txt");
  timer_standbyOff = readFile(SPIFFS, "/timer_standbyOff.txt");
  tanggal_standbyOff = readFile(SPIFFS, "/tanggal_standbyOff.txt");

  dumping_hmOff = readFile(SPIFFS, "/dumping_hmOff.txt");
  timer_dumpingOff = readFile(SPIFFS, "/timer_dumpingOff.txt");
  tanggal_dumpingOff = readFile(SPIFFS, "/tanggal_dumpingOff.txt");
  total_jamdumping = readFile(SPIFFS, "/total_jamdumping.txt");
  en_writedumping = readFile(SPIFFS, "/en_writedumping.txt").toInt();

  hm_start = readFile(SPIFFS, "/hm_start.txt").toFloat();
  hm_stoping = readFile(SPIFFS, "/hm_stoping.txt");
  timer_hmOff = readFile(SPIFFS, "/timer_hmOff.txt");
  tanggal_hmOff = readFile(SPIFFS, "/tanggal_hmOff.txt");
  total_jamhm = readFile(SPIFFS, "/total_jamhm.txt");
  en_writehm = readFile(SPIFFS, "/en_writehm.txt").toInt();

  idle_hmOff = readFile(SPIFFS, "/idle_hmOff.txt");
  timer_idleOff = readFile(SPIFFS, "/timer_idleOff.txt");
  tanggal_idleOff = readFile(SPIFFS, "/tanggal_idleOff.txt");
  total_jamidle = readFile(SPIFFS, "/total_jamidle.txt");
  en_writeidle = readFile(SPIFFS, "/en_writeidle.txt").toInt();

  standby_hmOff = readFile(SPIFFS, "/standby_hmOff.txt");
  timer_standbyOff = readFile(SPIFFS, "/timer_standbyOff.txt");
  tanggal_standbyOff = readFile(SPIFFS, "/tanggal_standbyOff.txt");
  total_jamstandby = readFile(SPIFFS, "/total_jamstandby.txt");
  en_writestandby = readFile(SPIFFS, "/en_writestandby.txt").toInt();
  xfirm_ver = readFile(SPIFFS, "/xfirm_ver.txt");

  lat_str = readFile(SPIFFS, "/lat_str.txt");
  lng_str = readFile(SPIFFS, "/lng_str.txt");
  alt_str = readFile(SPIFFS, "/alt_str.txt");
  spd_str = readFile(SPIFFS, "/spd_str.txt");
  heading_str = readFile(SPIFFS, "/heading_str.txt");
  st_str = readFile(SPIFFS, "/st_str.txt");

  Serial.print("SPIFFS Free: "); Serial.println(humanReadableSize((SPIFFS.totalBytes() - SPIFFS.usedBytes())));
  Serial.print("SPIFFS Used: "); Serial.println(humanReadableSize(SPIFFS.usedBytes()));
  Serial.print("SPIFFS Total: "); Serial.println(humanReadableSize(SPIFFS.totalBytes()));
}

String readFile(fs::FS &fs, const char * path) {
  File file = fs.open(path, "r");
  if (!file || file.isDirectory())
  {
    return String();
  }
  String fileContent;
  while (file.available())
  {
    fileContent += String((char)file.read());
  }
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message)
{
  File file = fs.open(path, "w");
  if (!file)
  {
    return;
  }
  file.print(message);
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.print(F("Message appending : "));
    Serial.println(message);
    Serial.println("Message appended");
  }
  else {
    Serial.println("Append failed");
  }
  file.close();
}

String humanReadableSize(const size_t bytes) {
  if (bytes < 1024) return String(bytes) + " B";
  else if (bytes < (1024 * 1024)) return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024)) return String(bytes / 1024.0 / 1024.0) + " MB";
  else return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

void notFoundd(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

String processor(const String& var)
{
  if (var == "version")
  {
    return version;
  }
  else if (var == "type_board")
  {
    return type_board;
  }
  else if (var == "sn_dev")
  {
    return readFile(SPIFFS, "/sn_dev.txt");
  }
  else if (var == "cn")
  {
    return readFile(SPIFFS, "/cn_str.txt");
  }
  else if (var == "sn")
  {
    return readFile(SPIFFS, "/sn_str.txt");
  }
  else if (var == "brand")
  {
    return readFile(SPIFFS, "/brand.txt");
  }

  else if (var == "selected_mercy")
  {
    String x = readFile(SPIFFS, "/brand.txt");

    if (x == "mercy")
    {
      return "selected";
    }
    else if (x == "scania")
    {
      return " ";
    }
    else if (x == "volvo")
    {
      return " ";
    }
  }

  else if (var == "selected_scania")
  {
    String x = readFile(SPIFFS, "/brand.txt");

    if (x == "mercy")
    {
      return " ";
    }
    else if (x == "scania")
    {
      return "selected";
    }
    else if (x == "volvo")
    {
      return " ";
    }
  }

  else if (var == "selected_volvo")
  {
    String x = readFile(SPIFFS, "/brand.txt");

    if (x == "mercy")
    {
      return " ";
    }
    else if (x == "scania")
    {
      return " ";
    }
    else if (x == "volvo")
    {
      return "selected";
    }
  }

  else if (var == "en_fatiq")
  {
    return en_fatiq;
  }

  else if (var == "selected_disableAlarm")
  {
    String x = readFile(SPIFFS, "/en_fatiq.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "selected_enableAlarm")
  {
    String x = readFile(SPIFFS, "/en_fatiq.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "en_fms")
  {
    return en_fms;
  }

  else if (var == "selected_disableFMS")
  {
    String x = readFile(SPIFFS, "/en_fms.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "selected_enableFMS")
  {
    String x = readFile(SPIFFS, "/en_fms.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "en_overspeed")
  {
    return en_overspeed;
  }

  else if (var == "selected_disableOvs")
  {
    String x = readFile(SPIFFS, "/en_overspeed.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "selected_enableOvs")
  {
    String x = readFile(SPIFFS, "/en_overspeed.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "en_anglewarning")
  {
    return readFile(SPIFFS, "/en_anglewarning.txt");;
  }

  else if (var == "selected_enableanglewarning")
  {
    String x = readFile(SPIFFS, "/en_anglewarning.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "selected_disableanglewarning")
  {
    String x = readFile(SPIFFS, "/en_anglewarning.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "limit_angle")
  {
    return readFile(SPIFFS, "/limit_angle.txt");;
  }

  else if (var == "overspeed")
  {
    return overspeed;
  }

  else if (var == "set_time")
  {
    return times;
  }

  else if (var == "set_date")
  {
    return dates;
  }

  else if (var == "en_lte")
  {
    return en_lte;
  }

  else if (var == "selected_enablelte")
  {
    String x = readFile(SPIFFS, "/en_lte.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "selected_disablelte")
  {
    String x = readFile(SPIFFS, "/en_lte.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "en_traccar")
  {
    return en_traccar;
  }

  else if (var == "selected_enabletraccar")
  {
    String x = readFile(SPIFFS, "/en_traccar.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "selected_disabletraccar")
  {
    String x = readFile(SPIFFS, "/en_traccar.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "server_traccar")
  {
    return server_traccar;
  }

  else if (var == "port_traccar")
  {
    return readFile(SPIFFS, "/port_traccar.txt");
  }

  else if (var == "interval_traccar")
  {
    return readFile(SPIFFS, "/interval_traccar.txt");
  }

  else if (var == "en_http")
  {
    return en_http;
  }

  else if (var == "selected_enablehttp")
  {
    String x = readFile(SPIFFS, "/en_http.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "selected_disablehttp")
  {
    String x = readFile(SPIFFS, "/en_http.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "server_http")
  {
    return readFile(SPIFFS, "/server_http.txt");
  }

  else if (var == "resource")
  {
    return resource;
  }

  else if (var == "interval_http")
  {
    return readFile(SPIFFS, "/interval_http.txt");;
  }

  else if (var == "en_mqtt")
  {
    return en_mqtt;
  }

  else if (var == "selected_enablemqtt")
  {
    String x = readFile(SPIFFS, "/en_mqtt.txt");

    if (x == "true")
    {
      return "selected";
    }
    else if (x == "false")
    {
      return " ";
    }
  }

  else if (var == "selected_disablemqtt")
  {
    String x = readFile(SPIFFS, "/en_mqtt.txt");

    if (x == "true")
    {
      return " ";
    }
    else if (x == "false")
    {
      return "selected";
    }
  }

  else if (var == "set_bitrate")
  {
    return readFile(SPIFFS, "/set_bitrate.txt");
  }

  else if (var == "125kbps")
  {
    String x = readFile(SPIFFS, "/set_bitrate.txt");

    if (x == "125")
    {
      return "selected";
    }
    else if (x == "250")
    {
      return " ";
    }
  }

  else if (var == "250kbps")
  {
    String x = readFile(SPIFFS, "/set_bitrate.txt");

    if (x == "125")
    {
      return " ";
    }
    else if (x == "250")
    {
      return "selected";
    }
  }

  else if (var == "mqtt_state")
  {
    return mqtt_state;
  }

  else if (var == "broker")
  {
    return broker;
  }

  else if (var == "user")
  {
    return user;
  }

  else if (var == "pass")
  {
    return pass;
  }

  else if (var == "interval_mqtt")
  {
    return readFile(SPIFFS, "/interval_mqtt.txt");
  }

  else if (var == "no_simcard")
  {
    return readFile(SPIFFS, "/no_simcard.txt");
  }

  else if (var == "server_ota")
  {
    return readFile(SPIFFS, "/server_ota.txt");
  }

  else if (var == "resource_ota")
  {
    return readFile(SPIFFS, "/resource_ota.txt");
  }

  else if (var == "freespace") {
    int xfreesp = SD.totalBytes() / (1024 * 1024);
    freesp = String(xfreesp) + " MB";
    return freesp;
  }

  else if (var == "usedstorage") {
    int xusedstr = SD.usedBytes() / (1024 * 1024);
    usedstr = String(xusedstr) + " MB";
    return usedstr;
  }

  else if (var == "totalStorage") {
    int xtotalstr = SD.cardSize() / (1024 * 1024);
    totalstr = String(xtotalstr) + " MB";
    return totalstr;
  }

  else
  {
    return String();
  }
}

void server_begin()
{
  server.serveStatic("/", SPIFFS, "/");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    read_setting();
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(401);
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(401);
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    Serial2.println("{\"restart\":\"" + String(1) + "\"}");
    Serial.println("================");
    Serial.println("Device Restart");
    Serial.println("================");
    delay(3000);
    ESP.restart();
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/default", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    Serial.println("================");
    Serial.println("Reset Default");
    Serial.println("================");
    data_default();
    delay(3000);
    ESP.restart();
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/push_traccar", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    Serial.println();
    Serial.println("__________________traccar_test_______________________");
    Serial.println();
    push_traccar();
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/push_http", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    Serial.println();
    Serial.println("__________________http_test_______________________");
    Serial.println();
    post();
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/publish", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    Serial.println();
    Serial.println("__________________mqtt_test_______________________");
    Serial.println();
    String get_payload = payload();
    Serial.println("POST PAYLOAD mqtt");
    Serial.println(get_payload);
    pub(String(cn_str + "_pub"), get_payload);
    request->send(SPIFFS, "/dashboard_ws.html", String(), false, processor);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    read_setting();
    request->redirect("/");
  });

  server.onNotFound(notFoundd);
  server.begin();
}
