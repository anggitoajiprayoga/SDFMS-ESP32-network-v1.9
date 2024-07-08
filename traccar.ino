void push_traccar() {
  Serial.println();
  Serial.println("Push to Traccar");
  byte count_network = 0;
  while (!modem.waitForNetwork() and count_network < 3)
  {
    count_network++;
    Serial.println("fail, count return: " + String(count_network));
  }
  Serial.println("Connected to provider.");
  Serial.println("Signal Quality: " + String(modem.getSignalQuality()));
  Serial.println();

  Serial.print("Connecting to GPRS network:  ");
  Serial.println(apn);
  byte count_gprs = 0;
  while (!modem.gprsConnect(apn, gprsUser, gprsPass) and count_gprs < 3)
  {
    count_gprs++;
    Serial.println("fail, count return: " + String(count_gprs));
  }
  Serial.println("Connected to GPRS: " + String(apn));
  Serial.println();

  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    state_gprs = "GPRS_disconnected";
  }
  else {
    state_gprs = "GPRS_connected";
  }

  if (modem.isGprsConnected()) {
    Serial.println("GPRS connected");
  }

  Serial.print("Connecting to ");
  Serial.print(server_traccar);
  Serial.print("...");
  if (client.connect(server_traccar.c_str(), port_traccar.toInt())) {
    Serial.println("OK");
  }
  else {
    Serial.println("failed push to traccar, wait and try again");
  }

  client.print(String("POST /?id=") + cn_str + "&brand=" + brand + "&lat=" + lat_str + "&lon=" + lng_str + "&alt=" + alt_str + "&speed=" + spd_str + "&heading=" + heading_str + "&satellites=" + st_str + "&angel=" + agl_str + "&eng_state=" + eng_state + "&duration=" + time_update +
               "&fatique=" + fatigue_str + "&state_network=" + state_gprs + "&csq=" + csq + "&relay_dump=" + relay_dump + "&relay_buzzer=" + relay_buzzer + "&sd_card=" + status_sdcard + "&dump_status=" + dump_status + "&ignition=" + ignition + "&state_pto=" + adc_pto + "&last_activity=" + last_act +
               "&engTorque=" + engTorque + "&engSpeed=" + engSpeed + "&tacVehSpeed=" + tacVehSpeed + "&accPed=" + accPed + "&actRet=" + actRet + "&brakePedPos=" + brakePedPos + "&airPress1=" + airPress1 + "&airPress2=" + airPress2 + "&airPress3=" + airPress3 +
               "&fuelRate=" + fuelRate + "&engEr=" + engEr + "&engHm=" + engHm + "&engClnTemp=" + engClnTemp + "&fuelLvl=" + fuelLvl + "&vehSpeed=" + vehSpeed + " HTTP/1.1\r\n" +
               "Host: " + server_traccar + "\r\n" +
               "Connection: keep-alive\r\n\r\n");
  Serial.print(String("GET /?id=") + cn_str + "&brand=" + brand + "&lat=" + lat_str + "&lon=" + lng_str + "&alt=" + alt_str + "&speed=" + spd_str + "&heading=" + heading_str + "&satellites=" + st_str + "&angel=" + agl_str + "&eng_state=" + eng_state + "&duration=" + time_update +
               "&fatique=" + fatigue_str + "&state_network=" + state_gprs + "&csq=" + csq + "&relay_dump=" + relay_dump + "&relay_buzzer=" + relay_buzzer + "&sd_card=" + status_sdcard + "&dump_status=" + dump_status + "&ignition=" + ignition + "&state_pto=" + adc_pto + "&last_activity=" + last_act +
               "&engTorque=" + engTorque + "&engSpeed=" + engSpeed + "&tacVehSpeed=" + tacVehSpeed + "&accPed=" + accPed + "&actRet=" + actRet + "&brakePedPos=" + brakePedPos + "&airPress1=" + airPress1 + "&airPress2=" + airPress2 + "&airPress3=" + airPress3 +
               "&fuelRate=" + fuelRate + "&engEr=" + engEr + "&engHm=" + engHm + "&engClnTemp=" + engClnTemp + "&fuelLvl=" + fuelLvl + "&vehSpeed=" + vehSpeed + " HTTP/1.1\r\n" +
               "Host: " + server_traccar + "\r\n" +
               "Connection: keep-alive\r\n\r\n");

  uint32_t t = millis();
  // output server response
  while (client.available() && millis() - t < 5000) {
    Serial.print((char)client.read());
  }

  // Shutdown
  client.stop();
  Serial.println(F("Server disconnected"));
  prev_traccar = millis();
}
