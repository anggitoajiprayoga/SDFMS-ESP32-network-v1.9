void post() {
  Serial.println("********** Push to server **********");
  byte _retry = 0;
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    delay(1000);
    return;
  }

  if (!client.connect(server_gsm, port)) {
    SerialMon.println(" fail");
    delay(1000);
    return;
  }
  SerialMon.println(F("Server connected."));
  Serial.println(dataJson_str);

  client.println("POST " + String(resource) + " HTTP/1.1");
  client.println("Host: " + String(server_http));
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(dataJson_str.length());
  client.println();
  client.println(dataJson_str);
  client.println();

  uint32_t timeout = millis();
  while (client.connected() and (millis() - timeout) < 5000) {
    while (client.available()) {
      char c = client.read();
      SerialMon.print(c);
      timeout = millis();

      // Jika tidak ada data lagi data yang terbaca
      if (!client.available()) {
        timeout = millis() - 10000;
        //break;
      }
    }
  }
  SerialMon.println();
  client.stop();
  SerialMon.println(F("Server disconnected."));
  modem.gprsDisconnect();
  Serial.println("*************** End ****************");
  prev_http = millis();
}
