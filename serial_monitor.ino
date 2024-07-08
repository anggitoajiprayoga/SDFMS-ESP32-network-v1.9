void serial_monitor() {
  if ((millis() - prev_sermon) > 3000) {
    prev_sermon = millis();
    Serial.println();
    brand = readFile(SPIFFS, "/brand.txt");
    Serial.println("packet: " + input);
    Serial.println("state AP: " + AP_state + " | user login: " + String(user_login) + " | time off: " + String(time_login) + " | wifi_ap: " + String(wifi_ap));
    Serial.println("cn : " + cn_str + " | sn: " + sn_str + " | brand: " + brand);
    Serial.println("lat : " + lat_str + " | lng: " + lng_str + " | alt: " + alt_str + " | spd: " + spd_str + " | hdg: " + heading_str + " | st: " + st_str);
    Serial.println("date : " + dates + " | times: " + times);
    Serial.println("agl : " + agl_str);
    Serial.println("fatigue : " + fatigue_str);
    Serial.println("engTorque: " + engTorque);
    Serial.println("engSpeed : " + engSpeed);
    Serial.println("tacVehSpeed : " + tacVehSpeed);
    Serial.println("accPed : " + accPed);
    Serial.println("engLoad : " + engLoad);
    Serial.println("actRet : " + actRet);
    Serial.println("brakePedPos : " + brakePedPos);
    Serial.println("airPress1 : " + airPress1);
    Serial.println("airPress2 : " + airPress2);
    Serial.println("airPress3 : " + airPress3);
    Serial.println("engEr : " + engEr);
    Serial.println("fuelRate : " + fuelRate);
    Serial.println("engHm : " + engHm);
    Serial.println("engClnTemp : " + engClnTemp);
    Serial.println("fuelLvl : " + fuelLvl);
    Serial.println("vehSpeed : " + vehSpeed);
    Serial.println("csq : " + String(csq));
    Serial.println("state_gprs : " + state_gprs);
    Serial.println("dump_status : " + dump_status);
    Serial.println("relay_dump : " + relay_dump);
    Serial.println("relay_buzzer : " + relay_buzzer);
    Serial.println("status_sdcard : " + status_sdcard);
    Serial.println("ignition : " + ignition + " | adc_pto: " + adc_pto);
    Serial.println("interval traccar: " + interval_traccar + " | interval http: " + interval_http + " | interval mqtt: " + interval_mqtt);
    Serial.println("en_lte: " + en_lte + " | en_http: " + en_http + " | en_mqtt: " + en_mqtt + " | en_traccar: " + en_traccar);
    Serial.println("operation: " + String(hm) + " | idle: " + String(idle) + " | standby: " + String(standby) + " | dumping: " + String(dumping));
    Serial.println("eng_state: " + eng_state + " | duration: " + String(time_update));
    Serial.println("SBon: " + String(timer_standbyOn) + " | SBoff: " + String(timer_standbyOff) + " | tanggalSB: " + String(tanggal_standbyOn) + " | totalSB: " + total_jamstandby);
    Serial.println("OPon: " + String(timer_hmOn) + " | OPoff: " + String(timer_hmOff) + " | tanggalOP: " + String(tanggal_hmOn) + " | totalOP: " + total_jamhm);
    Serial.println("idleon: " + String(timer_idleOn) + " | idleoff: " + String(timer_idleOff) + " | tanggalidle: " + String(tanggal_idleOn) + " | totalidle: " + total_jamidle);
    Serial.println();
  }
}
