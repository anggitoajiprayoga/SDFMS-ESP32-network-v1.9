void setup_esp32_to_atmega2560() {
  Serial2.begin(115200); // ← ESP32 to ATmega2560 Serial Port Baud
}

void websocket_parse(String input) {
  Serial.println();
  Serial.println("Config Parse");
  Serial.println();
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();

  String xcn  = obj["cn"].as<String>();
  String xsn  = obj["sn"].as<String>();
  String xen_fatiq  = obj["en_fatiq"].as<String>();
  String xen_anglewarning  = obj["en_anglewarning"].as<String>();
  String xlimit_angle  = obj["limit_angle"].as<String>();
  String xen_fms  = obj["en_fms"].as<String>();
  String xbrand  = obj["brand"].as<String>();
  String xset_bitrate  = obj["set_bitrate"].as<String>();
  String xen_overspeed  = obj["en_overspeed"].as<String>();
  String xoverspeed  = obj["overspeed"].as<String>();

  String xdate  = obj["date"].as<String>();
  String xtime  = obj["time"].as<String>();

  String xen_lte  = obj["en_lte"].as<String>();
  String xen_traccar  = obj["en_traccar"].as<String>();
  String xserver_traccar  = obj["server_traccar"].as<String>();
  String xport_traccar  = obj["port_traccar"].as<String>();
  String xinterval_traccar  = obj["interval_traccar"].as<String>();
  String xen_http  = obj["en_http"].as<String>();
  String xserver_http  = obj["server_http"].as<String>();
  String xresource  = obj["resource"].as<String>();
  String xinterval_http  = obj["interval_http"].as<String>();
  String xen_mqtt  = obj["en_mqtt"].as<String>();
  String xbroker  = obj["broker"].as<String>();
  String xusername  = obj["username"].as<String>();
  String xpass  = obj["pass"].as<String>();
  String xinterval_mqtt  = obj["interval_mqtt"].as<String>();

  String xserver_ota  = obj["server_ota"].as<String>();
  String xresource_ota  = obj["resource_ota"].as<String>();
  String xno_simcard  = obj["no_simcard"].as<String>();

  String xengSpeed     = obj["engSpeed"].as<String>();
  String xengHm        = obj["engHm"].as<String>();
  String xvehSpeed     = obj["vehSpeed"].as<String>();

  if (xengSpeed != "null" and xengSpeed != "") {
    engSpeed = xengSpeed;
    Serial.println("engSpeed: " + engSpeed);
  }
  if (xengHm != "null" and xengHm != "") {
    engHm = xengHm;
    Serial.println("engHm: " + engHm);
  }
  if (xvehSpeed != "null" and xvehSpeed != "") {
    vehSpeed = xvehSpeed;
    Serial.println("vehSpeed: " + vehSpeed);
  }

  if (xsn != "null" and xsn != "") {
    sn_str = xsn;
    writeFile(SPIFFS, "/sn_str.txt", xsn.c_str());
  }
  if (xen_fatiq != "null" and xen_fatiq != "") {
    en_fatiq = xen_fatiq;
    writeFile(SPIFFS, "/en_fatiq.txt", xen_fatiq.c_str());
  }
  if (xen_anglewarning != "null" and xen_anglewarning != "") {
    en_anglewarning = xen_anglewarning;
    writeFile(SPIFFS, "/en_anglewarning.txt", xen_anglewarning.c_str());
  }
  if (xlimit_angle != "null" and xlimit_angle != "") {
    limit_angle = xlimit_angle;
    writeFile(SPIFFS, "/limit_angle.txt", xlimit_angle.c_str());
  }
  if (xen_fms != "null" and xen_fms != "") {
    en_fms = xen_fms;
    writeFile(SPIFFS, "/en_fms.txt", xen_fms.c_str());
  }
  if (xbrand != "null" and xbrand != "") {
    brand = xbrand;
    writeFile(SPIFFS, "/brand.txt", xbrand.c_str());
  }
  if (xset_bitrate != "null" and xset_bitrate != "") {
    set_bitrate = xset_bitrate;
    writeFile(SPIFFS, "/set_bitrate.txt", xset_bitrate.c_str());
  }
  if (xen_overspeed != "null" and xen_overspeed != "") {
    en_overspeed = xen_overspeed;
    writeFile(SPIFFS, "/en_overspeed.txt", xen_overspeed.c_str());
  }
  if (xoverspeed != "null" and xoverspeed != "") {
    overspeed = xoverspeed;
    writeFile(SPIFFS, "/overspeed.txt", xoverspeed.c_str());
  }
  if (xcn != "null" and xcn != "") {
    cn_str = xcn;
    writeFile(SPIFFS, "/cn_str.txt", xcn.c_str());
    Serial2.println("{\"brand\":\"" + String(readFile(SPIFFS, "/brand.txt")) + "\",\"set_brand\":\"" + String(1) + "\",\"en_cn\":\"" + String(1) + "\",\"cn\":\"" + cn_str + "\",\"set_bitrate\":\"" + String(readFile(SPIFFS, "/set_bitrate.txt")) + "\",\"en_anglewarning\":\"" + en_anglewarning + "\",\"limit_angle\":\"" + limit_angle + "\"}");
    Serial.println("{\"brand\":\"" + String(readFile(SPIFFS, "/brand.txt")) + "\",\"set_brand\":\"" + String(1) + "\",\"en_cn\":\"" + String(1) + "\",\"cn\":\"" + cn_str + "\",\"set_bitrate\":\"" + String(readFile(SPIFFS, "/set_bitrate.txt")) + "\",\"en_anglewarning\":\"" + en_anglewarning + "\",\"limit_angle\":\"" + limit_angle + "\"}");
    Serial.println(F("Set SSID WiFi by CN Unit....."));
    String APssid2 = cn_str;
    WiFi.softAP(APssid2.c_str(), "");
    WiFi.mode(WIFI_AP);
    AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
    delay(100);
  }

  if (xdate != "null" and xdate != "") {
    writeFile(SPIFFS, "/set_date.txt", xdate.c_str());
  }
  if (xtime != "null" and xtime != "") {
    writeFile(SPIFFS, "/set_time.txt", xtime.c_str());

    delay(500);
    String set_date = readFile(SPIFFS, "/set_date.txt");
    String set_time = readFile(SPIFFS, "/set_time.txt") + ":0";
    parsing_setDateTime(set_date, set_time);
    delay(500);
    Rtc.SetDateTime(RtcDateTime(value_year.toInt(), value_month.toInt(), value_day.toInt(), value_hour.toInt(), value_minute.toInt(), value_second.toInt())); //tahun, bulan, tanggal, jam, menit, detik
    Serial.println("/n===============================");
    Serial.println("Set Jam Sukses");
    Serial.println("data_set: " + set_date + " " + set_time);
    Serial.println("===============================/n");
    delay(1000);
  }

  if (xen_lte != "null" and xen_lte != "") {
    en_lte = xen_lte;
    writeFile(SPIFFS, "/en_lte.txt", xen_lte.c_str());
  }
  if (xen_traccar != "null" and xen_traccar != "") {
    en_traccar = xen_traccar;
    writeFile(SPIFFS, "/en_traccar.txt", xen_traccar.c_str());
  }
  if (xserver_traccar != "null" and xserver_traccar != "") {
    server_traccar = xserver_traccar;
    writeFile(SPIFFS, "/server_traccar.txt", xserver_traccar.c_str());
  }
  if (xport_traccar != "null" and xport_traccar != "") {
    port_traccar = xport_traccar;
    writeFile(SPIFFS, "/port_traccar.txt", xport_traccar.c_str());
  }
  if (xinterval_traccar != "null" and xinterval_traccar != "") {
    interval_traccar = xinterval_traccar;
    writeFile(SPIFFS, "/interval_traccar.txt", xinterval_traccar.c_str());
  }
  if (xen_http != "null" and xen_http != "") {
    en_http = xen_http;
    writeFile(SPIFFS, "/en_http.txt", xen_http.c_str());
  }
  if (xserver_http != "null" and xserver_http != "") {
    server_http = xserver_http;
    writeFile(SPIFFS, "/server_http.txt", xserver_http.c_str());
  }
  if (xresource != "null" and xresource != "") {
    resource = xresource;
    writeFile(SPIFFS, "/resource.txt", xresource.c_str());
  }
  if (xinterval_http != "null" and xinterval_http != "") {
    interval_http = xinterval_http;
    writeFile(SPIFFS, "/interval_http.txt", xinterval_http.c_str());
  }
  if (xen_mqtt != "null" and xen_mqtt != "") {
    en_mqtt = xen_mqtt;
    writeFile(SPIFFS, "/en_mqtt.txt", xen_mqtt.c_str());
  }
  if (xbroker != "null" and xbroker != "") {
    broker = xbroker;
    writeFile(SPIFFS, "/broker.txt", xbroker.c_str());
  }
  if (xusername != "null" and xusername != "") {
    user = xusername;
    writeFile(SPIFFS, "/username.txt", xusername.c_str());
  }
  if (xpass != "null" and xpass != "") {
    pass = xpass;
    writeFile(SPIFFS, "/pass.txt", xpass.c_str());
  }
  if (xinterval_mqtt != "null" and xinterval_mqtt != "") {
    interval_mqtt = xinterval_mqtt;
    writeFile(SPIFFS, "/interval_mqtt.txt", xinterval_mqtt.c_str());
  }

  if (xserver_ota != "null" and xserver_ota != "") {
    server_ota = xserver_ota;
    writeFile(SPIFFS, "/server_ota.txt", xserver_ota.c_str());
  }
  if (xresource_ota != "null" and xresource_ota != "") {
    resource_ota = xresource_ota;
    writeFile(SPIFFS, "/resource_ota.txt", xresource_ota.c_str());
  }
  if (xno_simcard != "null" and xno_simcard != "") {
    no_simcard = xno_simcard;
    writeFile(SPIFFS, "/no_simcard.txt", xno_simcard.c_str());
  }
}

void receivedData() {
  if (Serial2.available()) {
    Serial.println();
    Serial.println("================= json received =================");
    input = Serial2.readStringUntil('\n');
    Serial.println(input);
    if (check_json(input) == true) {
      Serial.println("parsing json prosess");
      DynamicJsonDocument doc(2048);
      //      StaticJsonDocument<2048> doc;
      DeserializationError error = deserializeJson(doc, input);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        Serial.println();
      }
      else {
        JsonObject obj = doc.as<JsonObject>();

        String xenCn_str  = obj["en_cn"].as<String>();
        String xreceiveCN = obj["cn"].as<String>();
        String xbrand            = obj["brand"].as<String>();
        String xdateLog_str      = obj["date_gps"].as<String>();
        String xdatePost_str     = obj["date_gps"].as<String>();
        String xtime_str         = obj["time_gps"].as<String>();
        String xlat_str          = obj["lat"].as<String>();
        String xlng_str          = obj["lng"].as<String>();
        String xalt_str          = obj["alt"].as<String>();
        String xspd_str          = obj["spd"].as<String>();
        String xheading_str      = obj["heading"].as<String>();
        String xagl_str          = obj["agl"].as<String>();
        String xst_str           = obj["st"].as<String>();
        String xfatigue_str      = obj["fatigue"].as<String>();
        String xengTorque        = obj["engTorque"].as<String>();
        String xengSpeed         = obj["engSpeed"].as<String>();
        String xtacVehSpeed      = obj["tacVehSpeed"].as<String>();;
        String xaccPed           = obj["accPed"].as<String>();
        String xengLoad          = obj["engLoad"].as<String>();
        String xactRet           = obj["actRet"].as<String>();
        String xbrakePedPos      = obj["brakePedPos"].as<String>();
        String xairPress1        = obj["airPress1"].as<String>();
        String xairPress2        = obj["airPress2"].as<String>();
        String xairPress3        = obj["airPress3"].as<String>();
        String xengEr            = obj["engEr"].as<String>();
        String xfuelRate         = obj["fuelRate"].as<String>();
        String xengHm            = obj["engHm"].as<String>();
        String xengClnTemp       = obj["engClnTemp"].as<String>();
        String xfuelLvl          = obj["fuelLvl"].as<String>();
        String xvehSpeed         = obj["vehSpeed"].as<String>();
        String xdump_status      = obj["dump_status"].as<String>();
        String xrelay_dump       = obj["relay_dump"].as<String>();
        String xrelay_buzzer     = obj["relay_buzzer"].as<String>();
        String xadc_pto          = obj["adc_pto"].as<String>();
        String xignition         = obj["ignition"].as<String>();

        String xstate_canbus        = obj["state_canbus"].as<String>();
        String xstate_lcd           = obj["state_lcd"].as<String>();
        String xstate_gps           = obj["state_gps"].as<String>();
        String xstate_rs485         = obj["state_rs485"].as<String>();
        String xstate_communication = obj["state_communication"].as<String>();

        if (xstate_canbus != "null" and xstate_canbus != "") {
          eror_canbus = xstate_canbus.toInt();
        }
        if (xstate_lcd != "null" and xstate_lcd != "") {
          eror_lcd = xstate_lcd.toInt();
        }
        if (xstate_gps != "null" and xstate_gps != "") {
          eror_gps = xstate_gps.toInt();
        }
        if (xstate_rs485 != "null" and xstate_rs485 != "") {
          eror_rs485 = xstate_rs485.toInt();
        }
        if (xstate_communication != "null" and xstate_communication != "") {
          eror_communication = xstate_communication.toInt();
        }

        if (xenCn_str != "null" and xenCn_str != "") {
          if (number_detect(xtacVehSpeed)) {
            enCn_str = xenCn_str;
          }
        }
        if (xreceiveCN != "null" and xreceiveCN != "") {
          if (total_char(xreceiveCN) < 8) {
            receiveCN = xreceiveCN;
          }
        }
        if (xbrand != "null" and xbrand != "") {
          if (total_char(xbrand) < 8) {
            brand = xbrand;
          }
        }
        if (xdateLog_str != "null" and xdateLog_str != "") {
          if (total_char(xdateLog_str) < 22) {
            dateLog_str = xdateLog_str;
          }
        }
        if (xdatePost_str != "null" and xdatePost_str != "") {
          if (total_char(xdatePost_str) < 22) {
            datePost_str = xdatePost_str;
          }
        }
        if (xtime_str != "null" and xtime_str != "") {
          if (total_char(xtime_str) < 10) {
            time_str = xtime_str;
          }
        }
        if (xlat_str != "null") {
          if (total_char(xlat_str) < 15) {
            lat_str = xlat_str;
            writeFile(SPIFFS, "/lat_str.txt", xlat_str.c_str());
          }
        }
        if (xlng_str != "null") {
          if (total_char(xlng_str) < 15) {
            lng_str = xlng_str;
            writeFile(SPIFFS, "/lng_str.txt", xlng_str.c_str());
          }
        }
        if (xalt_str != "null") {
          if (total_char(xalt_str) < 7) {
            alt_str = xalt_str;
            writeFile(SPIFFS, "/alt_str.txt", xalt_str.c_str());
          }
        }
        if (xspd_str != "null") {
          if (total_char(xspd_str) < 7) {
            spd_str = xspd_str;
            writeFile(SPIFFS, "/spd_str.txt", xspd_str.c_str());
          }
        }
        if (xheading_str != "null") {
          if (total_char(xheading_str) < 10) {
            heading_str = xheading_str;
            writeFile(SPIFFS, "/heading_str.txt", xheading_str.c_str());
          }
        }
        if (xagl_str != "null") {
          if (total_char(xagl_str) < 14) {
            agl_str = xagl_str;
            if (number_detect(agl_str)) {
              agl_float = agl_str.toFloat();
            }
          }
        }
        if (xst_str != "null") {
          if (total_char(xst_str) < 4) {
            st_str = xst_str;
            writeFile(SPIFFS, "/st_str.txt", xst_str.c_str());
          }
        }
        if (xfatigue_str != "null") {
          if (total_char(xfatigue_str) < 20) {
            fatigue_str = xfatigue_str;
          }
        }
        if (xengTorque != "null") {
          if (number_detect(xengTorque) or xengTorque == "") {
            engTorque = xengTorque;
          }
        }
        if (xengSpeed != "null") {
          if (number_detect(xengSpeed) or xengSpeed == "") {
            engSpeed = xengSpeed;
          }
        }

        if (xtacVehSpeed != "null") {
          if (number_detect(xtacVehSpeed) or xtacVehSpeed == "") {
            tacVehSpeed = xtacVehSpeed;
          }
        }
        if (xaccPed != "null") {
          if (number_detect(xaccPed) or xaccPed == "") {
            accPed = xaccPed;
          }
        }

        if (xengLoad != "null") {
          if (number_detect(xengLoad) or xengLoad == "") {
            engLoad = xengLoad;
          }
        }
        if (xactRet != "null") {
          if (number_detect(xactRet) or xactRet == "") {
            actRet = xactRet;
          }
        }
        if (xbrakePedPos != "null") {
          if (number_detect(xbrakePedPos) or xbrakePedPos == "") {
            brakePedPos = xbrakePedPos;
          }
        }
        if (xairPress1 != "null") {
          if (number_detect(xairPress1) or xairPress1 == "") {
            airPress1 = xairPress1;
          }
        }
        if (xairPress2 != "null") {
          if (number_detect(xairPress2) or xairPress2 == "") {
            airPress2 = xairPress2;
          }
        }
        if (xairPress3 != "null") {
          if (number_detect(xairPress3) or xairPress3 == "") {
            airPress3 = xairPress3;
          }
        }
        if (xengEr != "null") {
          if (number_detect(xengEr) or xengEr == "") {
            engEr = xengEr;
          }
        }
        if (xfuelRate != "null") {
          if (number_detect(xfuelRate) or xfuelRate == "") {
            fuelRate = xfuelRate;
          }
        }
        if (xengHm != "null" and xengHm != "" and xengHm != "0") {
          if (number_detect(xengHm)) {
            engHm = xengHm;
          }
        }
        if (xengClnTemp != "null") {
          if (number_detect(xengClnTemp) or xengClnTemp == "") {
            engClnTemp = xengClnTemp;
          }
        }
        if (xfuelLvl != "null") {
          if (number_detect(xfuelLvl) or xfuelLvl == "") {
            fuelLvl = xfuelLvl;
          }
        }
        if (xvehSpeed != "null") {
          if (number_detect(xvehSpeed) or xvehSpeed == "") {
            vehSpeed = xvehSpeed;
          }
        }
        if (xdump_status != "null") {
          if (total_char(xdump_status) < 12) {
            dump_status = xdump_status;
          }
        }
        if (xrelay_dump != "null") {
          if (total_char(xrelay_dump) < 4) {
            relay_dump = xrelay_dump;
          }
        }
        if (xrelay_buzzer != "null") {
          if (total_char(xrelay_buzzer) < 4) {
            relay_buzzer = xrelay_buzzer;
          }
        }
        if (xadc_pto != "null") {
          if (total_char(xadc_pto) < 8) {
            adc_pto = xadc_pto;
          }
        }
        if (xignition != "null") {
          if (total_char(xignition) < 4) {
            ignition = xignition;
          }
        }

        String output;
        serializeJson(doc, output);

        if (receiveCN.length() > 0) {
          if (enCn_str == "1") {
            cn_str = receiveCN;
            writeFile(SPIFFS, "/cn_str.txt", receiveCN.c_str());
            String readSpiffs = readFile(SPIFFS, "/cn_str.txt");
            Serial.println();
            Serial.println("# Set CN from ATmega2560 : " + readSpiffs + " # [success]");
            Serial.println();
            Serial.println(F("Set SSID WiFi by CN Unit....."));
            String APssid2 = cn_str;
            WiFi.softAP(APssid2.c_str(), "");
            WiFi.mode(WIFI_AP);
            AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
            delay(100);
            enCn_str = "0";
          }
        }

        dataJson_str = "{\"date\":\" " + dates + "\",\"time\":\" " + times + "\",\"cn\":\" " + cn_str + "\",\"lat\":\" " + lat_str + "\",\"long\":\" " + lng_str + "\",\"heading\":\" " + heading_str + "\",\"spd\":\" " + spd_str + "\",\"kemiringan\":\" " + agl_str + "\",\"devTemp\":\"\"}";
        dataLog_str = cn_str + "," + dates + "," + times + "," + brand + "," + lat_str + "," + lng_str + "," + alt_str + "," + spd_str + "," + heading_str + "," + st_str + "," + agl_str + "," + fatigue_str + "," + adc_pto + "," + relay_dump + "," + relay_buzzer + "," + dump_status + "," + engTorque + "," + engSpeed + "," + tacVehSpeed + "," + accPed + "," + engLoad + "," + actRet + "," + brakePedPos + "," + airPress1 + "," + airPress2 + "," + airPress3 + "," + engEr + "," + fuelRate + "," + engHm + "," + engClnTemp + "," + fuelLvl + "," + vehSpeed + "\n";
      }
    }
    else {
      Serial.println("not parsing, retry json parsing");
    }
    Serial.println("================= end =================");
    Serial.println();
  }
}

bool number_detect(String str) {
  if (str.length() == 0) {
    return false;
  }

  for (unsigned int i = 0; i < str.length(); i++) {
    char currentChar = str.charAt(i);
    if (i == 0 && (currentChar == '+' || currentChar == '-')) {
      continue;
    }
    if (!isdigit(currentChar) && currentChar != '.') {
      return false;
    }
  }
  return true;
}

int total_char(String inputString) {
  int total = inputString.length();
  return total;
}

bool check_json(String data) {
  bool json_status = false;
  if (data.indexOf('{') != -1 and data.indexOf('}') != -1) {
    json_status = true;
    Serial.println("JSON lengkap");
  } else {
    Serial.println("JSON tidak lengkap");
  }
  return json_status;
}
