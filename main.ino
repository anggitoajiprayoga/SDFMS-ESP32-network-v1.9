void mainn() {
  changeShift();
  if (en_lte == "true") {
    csq = -113 + (2 * modem.getSignalQuality());
    if (en_traccar == "true") {
      if ((millis() - prev_traccar) > (interval_traccar.toInt() * 1000)) {
        push_traccar();
      }
    }

    if (en_http == "true") {
      if ((millis() - prev_http) > (interval_http.toInt() * 1000)) {
        post();
      }
    }

    if (en_mqtt == "true") {
      loop_mqtt();
      if ((millis() - prev_mqtt) > (interval_mqtt.toInt() * 1000)) {
        String get_health = payload_health();
        pub("fms/dt/machineHealth/" + cn_str, get_health);
        delay(150);
        String get_location = payload_location();
        pub("fms/dt/liveLocations/cn/" + cn_str, get_location);
        delay(150);
        String get_liveLocations = liveLocations();
        pub("fms/liveLocations", get_liveLocations);
        delay(150);
        String config = config_info();
        pub("fms/dt/config/" + cn_str, config);
        delay(150);
        String state_eror = eror_kode();
        pub("fms/dt/state_eror/" + cn_str, state_eror);
        delay(150);
        last_update();
        prev_mqtt = millis();
      }
    }
  }

  if (cn_str == "null") {
    writeFile(SPIFFS, "/cn_str.txt", "SDFMS SS6");
    delay(1000);
    cn_str = readFile(SPIFFS, "/cn_str.txt");
    Serial.println(cn_str);
    String APssid2 = cn_str;
    WiFi.softAP(APssid2.c_str(), "");
    WiFi.mode(WIFI_AP);
    AP_state = "ssid: " + cn_str + "[" + sn_dev + "] password:  , ON";
    delay(100);
  }

  if ((millis() - prev_config) > 3000) {
    String get_payload = payload();
    serial.println(get_payload);
    String get_config = config_info();
    Serial.println();
    Serial.println("================ payload send ================");
    Serial.println(get_config);
    Serial2.println(get_config);
    Serial.println("================ end ================");
    Serial.println();
    prev_config = millis();
  }

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    StaticJsonDocument<1023> doc;
    Serial.println(data);

    deserializeJson(doc, data);
    JsonObject obj = doc.as<JsonObject>();

    engSpeed     = obj["engSpeed"].as<String>();
    engHm        = obj["engHm"].as<String>();
    vehSpeed     = obj["vehSpeed"].as<String>();
    Serial.println("engSpeed: " + engSpeed);
    Serial.println("engHm: " + engHm);
    Serial.println("vehSpeed: " + vehSpeed);

    String output;
    serializeJson(doc, output);
    Serial.println(output);
  }

  if (lat_str == "" and lng_str == "") {
    lat_str = readFile(SPIFFS, "/lat_str.txt");
    lng_str = readFile(SPIFFS, "/lng_str.txt");
    alt_str = readFile(SPIFFS, "/alt_str.txt");
    spd_str = readFile(SPIFFS, "/spd_str.txt");
    heading_str = readFile(SPIFFS, "/heading_str.txt");
    st_str = readFile(SPIFFS, "/st_str.txt");
  }

  if (lat_str.toInt() == 0 and lng_str.toInt() == 0) {
    lat_str = readFile(SPIFFS, "/lat_str.txt");
    lng_str = readFile(SPIFFS, "/lng_str.txt");
    alt_str = readFile(SPIFFS, "/alt_str.txt");
    spd_str = readFile(SPIFFS, "/spd_str.txt");
    heading_str = readFile(SPIFFS, "/heading_str.txt");
    st_str = readFile(SPIFFS, "/st_str.txt");
  }

  if (Hour == 7 and Second == 0) {
    if (hm_start != 0) {
      hm_stop = atof(last_hm.c_str());
      hm_opr = hm_stop - hm_start;
      hm_start = atof(last_hm.c_str());
      writeFile(SPIFFS, "/hm_start.txt", String(hm_start).c_str());
    }
    else {
      hm_start = last_hm.toFloat();
      writeFile(SPIFFS, "/hm_start.txt", String(hm_start).c_str());
    }
  }

  if (Hour == 19 and Second == 0) {
    if (hm_start != 0) {
      hm_stop = atof(last_hm.c_str());
      hm_opr = hm_stop - hm_start;
      hm_start = atof(last_hm.c_str());
      writeFile(SPIFFS, "/hm_start.txt", String(hm_start).c_str());
    }
    else {
      hm_start = atof(last_hm.c_str());
      writeFile(SPIFFS, "/hm_start.txt", String(hm_start).c_str());
    }
  }

  if (engHm != "") {
    last_hm = engHm;
    writeFile(SPIFFS, "/last_hm.txt", String(engHm).c_str());
  }

  if (last_hm != "" and hm_start != 0) {
    hm_opr = atof(last_hm.c_str()) - hm_start;
  }

  if (engSpeed.toInt() < 50 or engSpeed == "") {
    hm = 0;
    idle = 0;
    dumping = 0;
    if (standby == 0) {
      hm = 0;
      idle = 0;
      standby = 1;
      dumping = 0;
      en_writestandby = 1;
      timer_standbyOn = times;
      tanggal_standbyOn = dates;
      standby_hmOn = last_hm;
      timer_standbyOff = "";
      tanggal_standbyOff = "";
      writeFile(SPIFFS, "/hm.txt", "0");
      writeFile(SPIFFS, "/idle.txt", "0");
      writeFile(SPIFFS, "/standby.txt", "1");
      writeFile(SPIFFS, "/en_writestandby.txt", "1");
      writeFile(SPIFFS, "/timer_standbyOn.txt", times.c_str());
      writeFile(SPIFFS, "/tanggal_standbyOn.txt", dates.c_str());
      writeFile(SPIFFS, "/standby_hmOn.txt", standby_hmOn.c_str());
      writeFile(SPIFFS, "/timer_standbyOff.txt", timer_standbyOff.c_str());
      writeFile(SPIFFS, "/tanggal_standbyOff.txt", tanggal_standbyOff.c_str());
      Serial.println("Engine OFF");
    }
  }
  else {
    standby = 0;
    if (ignition == "ON" and hm == 0) {
      hm = 1;
      standby = 0;
      en_writehm = 1;
      timer_hmOn = times;
      tanggal_hmOn = dates;
      hm_starting = last_hm;
      timer_hmOff = "";
      tanggal_hmOff = "";
      writeFile(SPIFFS, "/hm.txt", "1");
      writeFile(SPIFFS, "/standby.txt", "0");
      writeFile(SPIFFS, "/en_writehm.txt", "1");
      writeFile(SPIFFS, "/timer_hmOn.txt", times.c_str());
      writeFile(SPIFFS, "/tanggal_hmOn.txt", dates.c_str());
      writeFile(SPIFFS, "/hm_starting.txt", hm_starting.c_str());
      writeFile(SPIFFS, "/timer_hmOff.txt", timer_hmOff.c_str());
      writeFile(SPIFFS, "/tanggal_hmOff.txt", tanggal_hmOff.c_str());
      Serial.println("Engine Running");
    }

    if (ignition == "ON" and (vehSpeed.toInt() == 0 or vehSpeed == "") and adc_pto.toInt() == 1) {
      if (dumping == 0) {
        hm = 1;
        idle = 0;
        dumping = 1;
        standby = 0;
        en_writedumping = 1;
        timer_dumpingOn = times;
        tanggal_dumpingOn = dates;
        dumping_hmOn = last_hm;
        timer_dumpingOff = "";
        tanggal_dumpingOff = "";
        writeFile(SPIFFS, "/idle.txt", "0");
        writeFile(SPIFFS, "/dumping.txt", "1");
        writeFile(SPIFFS, "/en_writedumping.txt", "1");
        writeFile(SPIFFS, "/timer_dumpingOn.txt", times.c_str());
        writeFile(SPIFFS, "/tanggal_dumpingOn.txt", dates.c_str());
        writeFile(SPIFFS, "/dumping_hmOn.txt", dumping_hmOn.c_str());
        writeFile(SPIFFS, "/timer_dumpingOff.txt", timer_dumpingOff.c_str());
        writeFile(SPIFFS, "/tanggal_dumpingOff.txt", tanggal_dumpingOff.c_str());
        Serial.println("Dumping");
      }
    }
    else {
      dumping = 0;
    }

    if (ignition == "ON" and (vehSpeed.toInt() == 0 or vehSpeed == "") and adc_pto.toInt() == 0) {
      if (idle == 0) {
        hm = 1;
        idle = 1;
        dumping = 0;
        standby = 0;
        en_writehm = 1;
        en_writeidle = 1;
        timer_idleOn = times;
        tanggal_idleOn = dates;
        idle_hmOn = last_hm;
        timer_idleOff = "";
        tanggal_idleOff = "";
        writeFile(SPIFFS, "/hm.txt", "1");
        writeFile(SPIFFS, "/idle.txt", "1");
        writeFile(SPIFFS, "/standby.txt", "0");
        writeFile(SPIFFS, "/en_writehm.txt", "1");
        writeFile(SPIFFS, "/en_writeidle.txt", "1");
        writeFile(SPIFFS, "/timer_idleOn.txt", times.c_str());
        writeFile(SPIFFS, "/tanggal_idleOn.txt", dates.c_str());
        writeFile(SPIFFS, "/idle_hmOn.txt", last_hm.c_str());
        writeFile(SPIFFS, "/timer_idleOff.txt", timer_idleOff.c_str());
        writeFile(SPIFFS, "/tanggal_idleOff.txt", tanggal_idleOff.c_str());
        Serial.println("Engine Idle");
      }
    }
    else {
      idle = 0;
    }
  }

  if (hm == 1) {
    parsing_hm();
    get_update("operation", jam_hmOn.toInt(), mnt_hmOn.toInt(), dtk_hmOn.toInt(), hari_hmOn.toInt(), bulan_hmOn.toInt(), tahun_hmOn.toInt());
    eng_state = "Engine Running";
  }
  if (idle == 1) {
    parsing_idle();
    get_update("idle", jam_idleOn.toInt(), mnt_idleOn.toInt(), dtk_idleOn.toInt(), hari_idleOn.toInt(), bulan_idleOn.toInt(), tahun_idleOn.toInt());
    eng_state = "Engine Idle";
  }
  if (standby == 1) {
    parsing_standby();
    get_update("standby", jam_standbyOn.toInt(), mnt_standbyOn.toInt(), dtk_standbyOn.toInt(), hari_standbyOn.toInt(), bulan_standbyOn.toInt(), tahun_standbyOn.toInt());
    eng_state = "Engine OFF";
  }
  if (dumping == 1) {
    parsing_dumping();
    get_update("dumping", jam_dumpingOn.toInt(), mnt_dumpingOn.toInt(), dtk_dumpingOn.toInt(), hari_dumpingOn.toInt(), bulan_dumpingOn.toInt(), tahun_dumpingOn.toInt());
    eng_state = "Dumping";
  }

  if (dumping == 0 and en_writedumping == true) {
    dumping_hmOff = last_hm;
    timer_dumpingOff = times;
    tanggal_dumpingOff = dates;
    parsing_dumping();
    total_waktu("dumping", jam_dumpingOn.toInt(), mnt_dumpingOn.toInt(), dtk_dumpingOn.toInt(), jam_dumpingOff.toInt(), mnt_dumpingOff.toInt(), dtk_dumpingOff.toInt(), hari_dumpingOn.toInt(), bulan_dumpingOn.toInt(), tahun_dumpingOn.toInt(), hari_dumpingOff.toInt(), bulan_dumpingOff.toInt(), tahun_dumpingOff.toInt());
    total_jamdumping = String(selisih_jamdumping) + ":" + String(selisih_mntdumping) + ":" + String(selisih_dtkdumping);
    String get_production = payload_production("Dumping", shift, (tanggal_dumpingOn + " " + timer_dumpingOn), (tanggal_dumpingOff + " " + timer_dumpingOff), total_jamdumping, dumping_hmOn, dumping_hmOff);
    last_updatedumping = get_production;
    last_act = "dumping-" + total_jamdumping;
    if (en_lte == "true") {
      pub("fms/dt/production/" + cn_str, get_production);
    }
    logging("dumping", String(shift), timer_dumpingOn, timer_dumpingOff, dumping_hmOn, dumping_hmOff, total_jamdumping, true);
    delay(200);
    logging("machineHealth", String(shift), "", "", "", "", "", true);
    Serial.println("send final dumping OK");
    Serial.println();
    en_writedumping = 0;
    writeFile(SPIFFS, "/timer_dumpingOff.txt", times.c_str());
    writeFile(SPIFFS, "/tanggal_dumpingOff.txt", dates.c_str());
    writeFile(SPIFFS, "/total_jamdumping.txt", total_jamdumping.c_str());
    writeFile(SPIFFS, "/en_writedumping.txt", "0");
  }

  if (hm == 0 and en_writehm == true) {
    hm_stoping = last_hm;
    timer_hmOff = times;
    tanggal_hmOff = dates;
    parsing_hm();
    total_waktu("eng_operation", jam_hmOn.toInt(), mnt_hmOn.toInt(), dtk_hmOn.toInt(), jam_hmOff.toInt(), mnt_hmOff.toInt(), dtk_hmOff.toInt(), hari_hmOn.toInt(), bulan_hmOn.toInt(), tahun_hmOn.toInt(), hari_hmOff.toInt(), bulan_hmOff.toInt(), tahun_hmOff.toInt());
    total_jamhm = String(selisih_jamhm) + ":" + String(selisih_mnthm) + ":" + String(selisih_dtkhm);
    String get_production = payload_production("Engine Running", shift, (tanggal_hmOn + " " + timer_hmOn), (tanggal_hmOff + " " + timer_hmOff), total_jamhm, hm_starting, hm_stoping);
    last_updatehm = get_production;
    last_act = "engine_running-" + total_jamhm;
    if (en_lte == "true") {
      pub("fms/dt/production/" + cn_str, get_production);
    }
    logging("engine_running", String(shift), timer_hmOn, timer_hmOff, hm_starting, hm_stoping, total_jamhm, true);
    delay(200);
    logging("machineHealth", String(shift), "", "", "", "", "", true);
    Serial.println("send final operation OK");
    Serial.println();
    en_writehm = 0;
    writeFile(SPIFFS, "/hm_stoping.txt", last_hm.c_str());
    writeFile(SPIFFS, "/timer_hmOff.txt", times.c_str());
    writeFile(SPIFFS, "/tanggal_hmOff.txt", dates.c_str());
    writeFile(SPIFFS, "/total_jamhm.txt", total_jamhm.c_str());
    writeFile(SPIFFS, "/en_writehm.txt", "0");
  }

  if (idle == 0 and en_writeidle == true) {
    idle_hmOff = last_hm;
    timer_idleOff = times;
    tanggal_idleOff = dates;
    parsing_idle();
    total_waktu("eng_idle", jam_idleOn.toInt(), mnt_idleOn.toInt(), dtk_idleOn.toInt(), jam_idleOff.toInt(), mnt_idleOff.toInt(), dtk_idleOff.toInt(), hari_idleOn.toInt(), bulan_idleOn.toInt(), tahun_idleOn.toInt(), hari_idleOff.toInt(), bulan_idleOff.toInt(), tahun_idleOff.toInt());
    total_jamidle = String(selisih_jamidle) + ":" + String(selisih_mntidle) + ":" + String(selisih_dtkidle);
    String get_production = payload_production("Engine Idle", shift, (tanggal_idleOn + " " + timer_idleOn), (tanggal_idleOff + " " + timer_idleOff), total_jamidle, idle_hmOn, idle_hmOff);
    last_updateidle = get_production;
    last_act = "engine_idle-" + total_jamidle;
    if (en_lte == "true") {
      pub("fms/dt/production/" + cn_str, get_production);
    }
    logging("engine_idle", String(shift), timer_idleOn, timer_idleOff, idle_hmOn, idle_hmOff, total_jamidle, true);
    delay(200);
    logging("machineHealth", String(shift), "", "", "", "", "", true);
    Serial.println("send final idle OK");
    Serial.println();
    en_writeidle = 0;
    writeFile(SPIFFS, "/idle_hmOff.txt", last_hm.c_str());
    writeFile(SPIFFS, "/timer_idleOff.txt", times.c_str());
    writeFile(SPIFFS, "/tanggal_idleOff.txt", dates.c_str());
    writeFile(SPIFFS, "/total_jamidle.txt", total_jamidle.c_str());
    writeFile(SPIFFS, "/en_writeidle.txt", "0");
  }

  if (standby == 0 and en_writestandby == true) {
    standby_hmOff = last_hm;
    timer_standbyOff = times;
    tanggal_standbyOff = dates;
    parsing_standby();
    total_waktu("eng_off", jam_standbyOn.toInt(), mnt_standbyOn.toInt(), dtk_standbyOn.toInt(), jam_standbyOff.toInt(), mnt_standbyOff.toInt(), dtk_standbyOff.toInt(), hari_standbyOn.toInt(), bulan_standbyOn.toInt(), tahun_standbyOn.toInt(), hari_standbyOff.toInt(), bulan_standbyOff.toInt(), tahun_standbyOff.toInt());
    total_jamstandby = String(selisih_jamstandby) + ":" + String(selisih_mntstandby) + ":" + String(selisih_dtkstandby);
    String get_production = payload_production("Engine OFF", shift, (tanggal_standbyOn + " " + timer_standbyOn), (tanggal_standbyOff + " " + timer_standbyOff), total_jamstandby, standby_hmOn, standby_hmOff);
    last_updatesb = get_production;
    last_act = "engine_off-" + total_jamstandby;
    if (en_lte == "true") {
      pub("fms/dt/production/" + cn_str, get_production);
    }
    logging("engine_off", String(shift), timer_standbyOn, timer_standbyOff, standby_hmOn, standby_hmOff, total_jamstandby, true);
    delay(200);
    logging("machineHealth", String(shift), "", "", "", "", "", true);
    Serial.println("send final standby OK");
    Serial.println();
    en_writestandby = 0;
    writeFile(SPIFFS, "/standby_hmOff.txt", last_hm.c_str());
    writeFile(SPIFFS, "/timer_standbyOff.txt", times.c_str());
    writeFile(SPIFFS, "/tanggal_standbyOff.txt", dates.c_str());
    writeFile(SPIFFS, "/total_jamstandby.txt", total_jamstandby.c_str());
    writeFile(SPIFFS, "/en_writestandby.txt", "0");
  }

  if ((millis() - prev_health) > 300000) {
    logging("machineHealth", String(shift), "", "", "", "", "", true);
    prev_health = millis();
  }

  if ((millis() - prev_Liveloc) > 600000) {
    logging("liveLocations", String(shift), "", "", "", "", "", true);
    prev_Liveloc = millis();
  }

  if (en_update == true) {
    if ((millis() - prev_update) > 300000) {
      pub("fms/dt/device/callback/" + cn_str, "retry update OTA proccess");
      Serial.println("Update Firmware by OTA");
      delay(2000);
      ota();
      prev_update = millis();
    }
  }

  if (firm_ver != xfirm_ver) {
    pub("fms/dt/device/callback/" + cn_str, "update OTA done");
    writeFile(SPIFFS, "/xfirm_ver.txt", firm_ver.c_str());
    xfirm_ver = readFile(SPIFFS, "/xfirm_ver.txt");
  }
}

void update(String status, int jam_awal, int menit_awal, int detik_awal, int jam_akhir, int menit_akhir, int detik_akhir, int tanggal_awal, int bulan_awal, int tahun_awal, int tanggal_akhir, int bulan_akhir, int tahun_akhir) {
  //dtk,mnt,jam,hari,tgl,bln,tahun
  tmElements_t tanggalPertama = {detik_awal, menit_awal, jam_awal, 0, tanggal_awal, bulan_awal, CalendarYrToTm(tahun_awal)};
  tmElements_t tanggalKedua = {detik_akhir, menit_akhir, jam_akhir, 0, tanggal_akhir, bulan_akhir, CalendarYrToTm(tahun_akhir)};
  tmElements_t selisih;
  breakTime(makeTime(tanggalKedua) - makeTime(tanggalPertama), selisih);

  if (status == "operation") {
    sprintf (time_updatehm, "%02d:%02d:%02d", selisih.Hour, selisih.Minute, selisih.Second);
    time_update = time_updatehm;
  }
  if (status == "idle") {
    sprintf (time_updateidle, "%02d:%02d:%02d", selisih.Hour, selisih.Minute, selisih.Second);
    time_update = time_updateidle;
  }
  if (status == "standby") {
    sprintf (time_updatestandby, "%02d:%02d:%02d", selisih.Hour, selisih.Minute, selisih.Second);
    time_update = time_updatestandby;
  }
}

void get_update(String status, int jam_on, int menit_on, int detik_on, int tanggal_on, int bulan_on, int tahun_on) {
  int jam_update = Hour;
  int menit_update = Minute;
  int detik_update = Second;
  int tanggal_update = Day;
  int bulan_update = Month;
  int tahun_update = Year;
  update(status, jam_on, menit_on, detik_on, jam_update, menit_update, detik_update, tanggal_on, bulan_on, tahun_on, tanggal_update, bulan_update, tahun_update);
}

void last_update() {
  if (en_writehm == 0) {
    if (last_updatehm != "") {
      pub("fms/dt/production/" + cn_str, last_updatehm);
      delay(150);
    }
  }

  if (en_writeidle == 0) {
    if (last_updateidle != "") {
      pub("fms/dt/production/" + cn_str, last_updateidle);
      delay(150);
    }
  }

  if (en_writestandby == 0) {
    if (last_updatesb != "") {
      pub("fms/dt/production/" + cn_str, last_updatesb);
      delay(150);
    }
  }

  if (en_writedumping == 0) {
    if (last_updatedumping != "") {
      pub("fms/dt/production/" + cn_str, last_updatedumping);
      delay(150);
    }
  }
}

void changeShift() {
  if (Hour >= 7 and Hour < 19) {       // Change shift siang
    shift = 1;
  }
  else if (Hour >= 19 and Hour < 24) {  // Change shift malam
    shift = 2;
  }
  else if (Hour > -1 and Hour < 7) {  // Change shift malam
    shift = 2;
  }

  if (Hour == 18) {
    xshift = shift;
  }

  if (Hour == 6) {
    xshift = shift;
  }

  if ((xshift != shift) or (Hour == 18 and Minute == 59 and Second == 59) or (Hour == 6 and Minute == 59 and Second == 59)) {
    if (hm == 1) {
      hm_stoping = last_hm;
      timer_hmOff = times;
      tanggal_hmOff = dates;
      parsing_hm();
      total_waktu("eng_operation", jam_hmOn.toInt(), mnt_hmOn.toInt(), dtk_hmOn.toInt(), jam_hmOff.toInt(), mnt_hmOff.toInt(), dtk_hmOff.toInt(), hari_hmOn.toInt(), bulan_hmOn.toInt(), tahun_hmOn.toInt(), hari_hmOff.toInt(), bulan_hmOff.toInt(), tahun_hmOff.toInt());
      total_jamhm = String(selisih_jamhm) + ":" + String(selisih_mnthm) + ":" + String(selisih_dtkhm);
      String get_production = payload_production("Engine Running", xshift, (tanggal_hmOn + " " + timer_hmOn), (tanggal_hmOff + " " + timer_hmOff), total_jamhm, hm_starting, hm_stoping);
      last_updatehm = get_production;
      last_act = "engine_running-" + total_jamhm;
      if (en_lte == "true") {
        pub("fms/dt/production/" + cn_str, get_production);
        delay(500);
        pub("fms/dt/production/" + cn_str, get_production);
      }
      logging("engine_running", String(xshift), timer_hmOn, timer_hmOff, hm_starting, hm_stoping, total_jamhm, true);
      delay(200);
      logging("machineHealth", String(xshift), "", "", "", "", "", true);
      Serial.println("send final operation OK");
      Serial.println();
      en_writehm = 0;
      writeFile(SPIFFS, "/hm_starting.txt", "");
      writeFile(SPIFFS, "/hm_stoping.txt", "");
      writeFile(SPIFFS, "/timer_hmOn.txt", "");
      writeFile(SPIFFS, "/tanggal_hmOn.txt", "");
      writeFile(SPIFFS, "/timer_hmOff.txt", "");
      writeFile(SPIFFS, "/tanggal_hmOff.txt", "");
      writeFile(SPIFFS, "/total_jamhm.txt", "");
      writeFile(SPIFFS, "/en_writehm.txt", "0");
      writeFile(SPIFFS, "/hm.txt", "0");
    }
    if (idle == 1) {
      idle_hmOff = last_hm;
      timer_idleOff = times;
      tanggal_idleOff = dates;
      parsing_idle();
      total_waktu("eng_idle", jam_idleOn.toInt(), mnt_idleOn.toInt(), dtk_idleOn.toInt(), jam_idleOff.toInt(), mnt_idleOff.toInt(), dtk_idleOff.toInt(), hari_idleOn.toInt(), bulan_idleOn.toInt(), tahun_idleOn.toInt(), hari_idleOff.toInt(), bulan_idleOff.toInt(), tahun_idleOff.toInt());
      total_jamidle = String(selisih_jamidle) + ":" + String(selisih_mntidle) + ":" + String(selisih_dtkidle);
      String get_production = payload_production("Engine Idle", xshift, (tanggal_idleOn + " " + timer_idleOn), (tanggal_idleOff + " " + timer_idleOff), total_jamidle, idle_hmOn, idle_hmOff);
      last_updateidle = get_production;
      last_act = "engine_idle-" + total_jamidle;
      if (en_lte == "true") {
        pub("fms/dt/production/" + cn_str, get_production);
        delay(500);
        pub("fms/dt/production/" + cn_str, get_production);
      }
      logging("engine_idle", String(xshift), timer_idleOn, timer_idleOff, idle_hmOn, idle_hmOff, total_jamidle, true);
      delay(200);
      logging("machineHealth", String(xshift), "", "", "", "", "", true);
      Serial.println("send final idle OK");
      Serial.println();
      en_writeidle = 0;
      writeFile(SPIFFS, "/idle_hmOn.txt", "");
      writeFile(SPIFFS, "/idle_hmOff.txt", "");
      writeFile(SPIFFS, "/timer_idleOn.txt", "");
      writeFile(SPIFFS, "/tanggal_idleOn.txt", "");
      writeFile(SPIFFS, "/timer_idleOff.txt", "");
      writeFile(SPIFFS, "/tanggal_idleOff.txt", "");
      writeFile(SPIFFS, "/total_jamidle.txt", "");
      writeFile(SPIFFS, "/en_writeidle.txt", "0");
      writeFile(SPIFFS, "/idle.txt", "0");
    }
    if (standby == 1) {
      standby_hmOff = last_hm;
      timer_standbyOff = times;
      tanggal_standbyOff = dates;
      parsing_standby();
      total_waktu("eng_off", jam_standbyOn.toInt(), mnt_standbyOn.toInt(), dtk_standbyOn.toInt(), jam_standbyOff.toInt(), mnt_standbyOff.toInt(), dtk_standbyOff.toInt(), hari_standbyOn.toInt(), bulan_standbyOn.toInt(), tahun_standbyOn.toInt(), hari_standbyOff.toInt(), bulan_standbyOff.toInt(), tahun_standbyOff.toInt());
      total_jamstandby = String(selisih_jamstandby) + ":" + String(selisih_mntstandby) + ":" + String(selisih_dtkstandby);
      String get_production = payload_production("Engine OFF", xshift, (tanggal_standbyOn + " " + timer_standbyOn), (tanggal_standbyOff + " " + timer_standbyOff), total_jamstandby, standby_hmOn, standby_hmOff);
      last_updatesb = get_production;
      last_act = "engine_off-" + total_jamstandby;
      if (en_lte == "true") {
        pub("fms/dt/production/" + cn_str, get_production);
        delay(500);
        pub("fms/dt/production/" + cn_str, get_production);
      }
      logging("engine_off", String(xshift), timer_standbyOn, timer_standbyOff, standby_hmOn, standby_hmOff, total_jamstandby, true);
      delay(200);
      logging("machineHealth", String(xshift), "", "", "", "", "", true);
      Serial.println("send final standby OK");
      Serial.println();
      en_writestandby = 0;
      writeFile(SPIFFS, "/standby_hmOn.txt", "");
      writeFile(SPIFFS, "/standby_hmOff.txt", "");
      writeFile(SPIFFS, "/timer_standbyOn.txt", "");
      writeFile(SPIFFS, "/tanggal_standbyOn.txt", "");
      writeFile(SPIFFS, "/timer_standbyOff.txt", "");
      writeFile(SPIFFS, "/tanggal_standbyOff.txt", "");
      writeFile(SPIFFS, "/total_jamstandby.txt", "");
      writeFile(SPIFFS, "/en_writestandby.txt", "0");
      writeFile(SPIFFS, "/standby.txt", "0");
    }

    if (dumping == 1) {
      dumping_hmOff = last_hm;
      timer_dumpingOff = times;
      tanggal_dumpingOff = dates;
      parsing_dumping();
      total_waktu("dumping", jam_dumpingOn.toInt(), mnt_dumpingOn.toInt(), dtk_dumpingOn.toInt(), jam_dumpingOff.toInt(), mnt_dumpingOff.toInt(), dtk_dumpingOff.toInt(), hari_dumpingOn.toInt(), bulan_dumpingOn.toInt(), tahun_dumpingOn.toInt(), hari_dumpingOff.toInt(), bulan_dumpingOff.toInt(), tahun_dumpingOff.toInt());
      total_jamdumping = String(selisih_jamdumping) + ":" + String(selisih_mntdumping) + ":" + String(selisih_dtkdumping);
      String get_production = payload_production("Dumping", xshift, (tanggal_dumpingOn + " " + timer_dumpingOn), (tanggal_dumpingOff + " " + timer_dumpingOff), total_jamdumping, dumping_hmOn, dumping_hmOff);
      last_updatedumping = get_production;
      last_act = "dumping-" + total_jamdumping;
      if (en_lte == "true") {
        pub("fms/dt/production/" + cn_str, get_production);
        delay(500);
        pub("fms/dt/production/" + cn_str, get_production);
      }
      logging("dumping", String(xshift), timer_dumpingOn, timer_dumpingOff, dumping_hmOn, dumping_hmOff, total_jamdumping, true);
      delay(200);
      logging("machineHealth", String(xshift), "", "", "", "", "", true);
      Serial.println("send final dumping OK");
      Serial.println();
      en_writedumping = 0;
      writeFile(SPIFFS, "/dumping_hmOn.txt", "");
      writeFile(SPIFFS, "/dumping_hmOff.txt", "");
      writeFile(SPIFFS, "/timer_dumpingOn.txt", "");
      writeFile(SPIFFS, "/tanggal_dumpingOn.txt", "");
      writeFile(SPIFFS, "/timer_dumpingOff.txt", "");
      writeFile(SPIFFS, "/tanggal_dumpingOff.txt", "");
      writeFile(SPIFFS, "/total_jamdumping.txt", "");
      writeFile(SPIFFS, "/en_writedumping.txt", "0");
      writeFile(SPIFFS, "/dumping.txt", "0");
    }

    if (Hour == 6 and Minute == 59 and Second == 59) {
      shift = 1;
    }
    if (Hour == 18 and Minute == 59 and Second == 59) {
      shift = 2;
    }

    xshift = shift;
    writeFile(SPIFFS, "/xshift.txt", String(shift).c_str());
    Serial.println("Restart Device Change Shift");
    Serial2.println("{\"restart\":\"" + String(1) + "\"}");
    ESP.restart();
  }
}
