void setup_sim7600ce() {
  Serial1.begin(115200, PROTOCOL, RXD1, TXD1); // ← GSM Serial Port Baud

  pinMode(RST, OUTPUT);
  pinMode(PKEY, OUTPUT);

  digitalWrite(PKEY, LOW);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(PKEY, HIGH);
  digitalWrite(RST, HIGH);
  delay(500);
  digitalWrite(PKEY, LOW);
  digitalWrite(RST, LOW);
  delay(500);

  SerialMon.println("Initializing modem...");
  modem.restart();
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    state_gprs = "GPRS_disconnected";
  }
  else {
    state_gprs = "GPRS_connected";
  }

  //  getIMEI();
  //  getICCID();
  send_at("ATI");
  send_at("AT+CPIN?");
  send_at("AT+CSQ");
  send_at("AT+CPSI?");
  send_at("AT+IPR?");
  send_at("AT+CNUM");

  imei = send_at_and_get_response("AT+GSN");
  imei = parse_imei(imei);
  Serial.print("IMEI: ");
  Serial.println(imei);
}

String send_at_and_get_response(char *_command) {
  SerialAT.println(_command);
  return xwRespon(2000);
}

String xwRespon(long waktu) {
  long cur_time_respon = millis();
  long old_time_respon = cur_time_respon;
  String response = "";

  while (cur_time_respon - old_time_respon < waktu) {
    cur_time_respon = millis();
    while (SerialAT.available() > 0) {
      response += SerialAT.readString();
    }
  }
  return response;
}

// Fungsi untuk mengekstrak IMEI dari respon
String parse_imei(String response) {
  int imei_start = response.indexOf("AT+GSN");
  if (imei_start != -1) {
    response = response.substring(imei_start + 6); // +6 untuk panjang "AT+GSN"
    response.trim(); // Hilangkan whitespace tambahan
    int imei_end = response.indexOf("\n");
    if (imei_end != -1) {
      response = response.substring(0, imei_end); // Ambil IMEI sebelum newline
    }
  }
  response.trim(); // Hilangkan whitespace tambahan
  return response;
}

void send_at(char *_command) {
  SerialAT.println(_command);
  wRespon(2000);
}

void wRespon(long waktu) {
  cur_time_respon = millis();
  old_time_respon = cur_time_respon;
  while (cur_time_respon - old_time_respon < waktu ) {
    cur_time_respon = millis();
    while (SerialAT.available() > 0) {
      SerialMon.print(SerialAT.readString());
    }
  }
}

void reset_sim() {
  digitalWrite(RST, HIGH);
}

void getIMEI() {
  SerialAT.println("AT+CGSN");
  cur_time_respon = millis();
  old_time_respon = cur_time_respon;
  while (cur_time_respon - old_time_respon < 2000) {
    cur_time_respon = millis();
    while (SerialAT.available() > 0) {
      SerialMon.print(SerialAT.readString());
      String kode = kode + SerialAT.read();
      String kode_sn = kode.substring(kode.length() - 5);
      Serial.println("kode_sn: " + kode_sn);
    }
  }
}

void getICCID() {
  SerialAT.println("AT+CCID");
  cur_time_respon = millis();
  old_time_respon = cur_time_respon;
  while (cur_time_respon - old_time_respon < 2000) {
    cur_time_respon = millis();
    while (SerialAT.available() > 0) {
      SerialMon.print(SerialAT.readString());
      ccid = SerialAT.readString();
    }
  }
}

void wakeup_sim() {
  SerialMon.println("Wakeup SIM7600");
  digitalWrite(PKEY, LOW);
  digitalWrite(RST, LOW);
  delay(1000);
  digitalWrite(PKEY, HIGH);
  digitalWrite(RST, HIGH);
  delay(1000);
  digitalWrite(PKEY, LOW);
  digitalWrite(RST, LOW);
  delay(1000);
  wRespon(15000);
}
