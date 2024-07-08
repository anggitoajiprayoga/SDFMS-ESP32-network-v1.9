void setup_sd_card() {
  if (!SD.begin(SD_CS)) {
    Serial.println(F("Card failed or not present, no SD Card data logging possible..."));
    eror_sd = true;
  } else {
    Serial.println(F("Card initialised... file access enabled..."));
    eror_sd = false;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println(F("Tidak Ada Kartu SD"));
    eror_sd = true;
    status_sdcard = "Not_Available";
    return;
  }
  else {
    status_sdcard = "Available";
  }
  Serial.println(F("Succes initialization SD Card"));
}

void check_dir() {
  File file = SD.open("/machineHealth.csv");
  if (!file) {
    Serial.println("File /machineHealth.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/machineHealth.csv", "cn, sn, date, time, shift, brand, eng_torque, eng_speed, tac_veh_speed, acc_ped, eng_load, act_ret, brake_ped_pos, air_press1, air_press2, air_press3, eng_Er, fuel_rate, eng_hm, eng_cln_temp, fuel_lvl, veh_speed, status_device\n");
  }
  else {
    Serial.println("File /machineHealth.csv already exists");
  }
  file.close();

  File file1 = SD.open("/eng_operation.csv");
  if (!file1) {
    Serial.println("File /engine_running.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/engine_running.csv", "cn, sn, date, time, shift, brand, lat, long, alt, spd, hdg, condition, start, stop, duration, hm_start, hm_stop, status_device\n");
  }
  else {
    Serial.println("File /engine_running.csv already exists");
  }
  file1.close();

  File file2 = SD.open("/engine_idle.csv");
  if (!file2) {
    Serial.println("File /engine_idle.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/engine_idle.csv", "cn, sn, date, time, shift, brand, lat, long, alt, spd, hdg, condition, start, stop, duration, hm_start, hm_stop, status_device\n");
  }
  else {
    Serial.println("File /engine_idle.csv already exists");
  }
  file2.close();

  File file3 = SD.open("/engine_off.csv");
  if (!file3) {
    Serial.println("File /engine_off.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/engine_off.csv", "cn, sn, date, time, shift, brand, lat, long, alt, spd, hdg, condition, start, stop, duration, hm_start, hm_stop, status_device\n");
  }
  else {
    Serial.println("File /engine_off.csv already exists");
  }
  file3.close();

  File file4 = SD.open("/activity_flow.csv");
  if (!file4) {
    Serial.println("File /activity_flow.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/activity_flow.csv", "cn, sn, date, time, shift, brand, lat, long, alt, spd, hdg, condition, start, stop, duration, hm_start, hm_stop, status_device\n");
  }
  else {
    Serial.println("File /activity_flow.csv already exists");
  }
  file4.close();

  File file5 = SD.open("/liveLocations.csv");
  if (!file5) {
    Serial.println("File /liveLocations.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/liveLocations.csv", "cn, sn, date, time , shift, brand, tilt, firm, rssi, lat, long, alt, spd, hdg, st, status_device\n");
  }
  else {
    Serial.println("File /liveLocations.csv already exists");
  }
  file5.close();

  File file6 = SD.open("/dumping.csv");
  if (!file6) {
    Serial.println("File /dumping.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/dumping.csv", "cn, sn, date, time , shift, brand, tilt, firm, rssi, lat, long, alt, spd, hdg, st, status_device\n");
  }
  else {
    Serial.println("File /dumping.csv already exists");
  }
  file6.close();

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void logging(String kondisi, String shift, String time_On, String time_Off, String hm_on, String hm_off, String total_waktu, bool en_log) {
  while (kondisi == "machineHealth" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + engTorque + "," + engSpeed + "," + tacVehSpeed + "," + accPed + "," +
              engLoad + "," + actRet + "," + brakePedPos + "," + airPress1 + "," + airPress2 + "," + airPress3 + "," + engEr + "," + fuelRate + "," + engHm + "," + engClnTemp +
              "," + fuelLvl + "," + vehSpeed + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/machineHealth.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "liveLocations" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + agl_float + "," + firm_ver + "," + csq + "," + lat_str + "," + lng_str + "," + alt_str +
              "," + spd_str + "," + heading_str + "," + st_str + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/liveLocations.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_running" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + lat_str + "," + lng_str + "," + alt_str + "," + spd_str + "," +
              heading_str + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + hm_on + "," + hm_off + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/engine_running.csv", dataLog.c_str());
    appendFile(SD, "/activity_flow.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_idle" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + lat_str + "," + lng_str + "," + alt_str + "," + spd_str + "," +
              heading_str + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + hm_on + "," + hm_off + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/engine_idle.csv", dataLog.c_str());
    appendFile(SD, "/activity_flow.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_off" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + lat_str + "," + lng_str + "," + alt_str + "," + spd_str + "," +
              heading_str + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + hm_on + "," + hm_off + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/engine_off.csv", dataLog.c_str());
    appendFile(SD, "/activity_flow.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "dumping" and en_log == true) {
    dataLog = cn_str + "," + sn_str + "," + dates + "," + times + "," + shift + "," + brand + "," + lat_str + "," + lng_str + "," + alt_str + "," + spd_str + "," +
              heading_str + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + hm_on + "," + hm_off + "," + status_device + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/dumping.csv", dataLog.c_str());
    appendFile(SD, "/activity_flow.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
}
