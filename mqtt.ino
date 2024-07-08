void setup_mqtt() {
  Serial.println();
  Serial.println("Searching for provider.");
  byte count_network = 0;
  while (!modem.waitForNetwork() and count_network < 3)
  {
    count_network++;
    Serial.println("fail, count return: " + String(count_network));
  }

  if (!modem.waitForNetwork()) {
    Serial.println("Not Connect to provider.");
  }
  else {
    Serial.println("Connected to provider.");
    Serial.println("Signal Quality: " + String(modem.getSignalQuality()));
    Serial.println();
  }

  Serial.println("Connecting to GPRS network.");
  byte count_gprs = 0;
  while (!modem.gprsConnect("internet", "", "") and count_gprs < 3)
  {
    count_gprs++;
    Serial.println("fail, count return: " + String(count_gprs));
  }

  if (!modem.gprsConnect("internet", "", "")) {
    Serial.println("Not Connect to GPRS: " + String(apn));
    Serial.println();
  }
  else {
    Serial.println("Connected to GPRS: " + String(apn));
    Serial.println();
  }

  mqtt.setServer((char*) broker.c_str(), 1883);
  mqtt.setCallback(callback);

  Serial.println("Connecting to MQTT Broker: " + String(broker));
  byte count_mqtt = 0;
  while (mqttConnect() == false and count_mqtt < 3) {
    count_mqtt++;
    Serial.println("fail, count return: " + String(count_mqtt));
  }
  Serial.print("mqtt state: " + String(mqtt.state()));
  Serial.println();

  topic_sub = "fms/dt/remote/" + cn_str;
  char _jsonDataStringChar[topic_sub.length() + 1];
  topic_sub.toCharArray(_jsonDataStringChar, topic_sub.length() + 1);
  mqtt.subscribe(_jsonDataStringChar);

  String topic_sub1 = "fms/dt/remote";
  char _jsonDataStringChar1[topic_sub1.length() + 1];
  topic_sub1.toCharArray(_jsonDataStringChar1, topic_sub1.length() + 1);
  mqtt.subscribe(_jsonDataStringChar1);
}

void loop_mqtt() {
  if (!mqtt.connected()) {
    mqtt_state = "Not_Connect";
    Serial.println("disconnect, waiting to reconnect");
    reconnect();
  }
  else {
    mqtt.loop();
    mqtt_state = "Connect";
  }
}

void pub(String topic, String _jsonDataString)
{
  if (mqtt.connected()) {
    char _jsonDataStringChar[_jsonDataString.length() + 1];
    char topicChar[topic.length() + 1];
    _jsonDataString.toCharArray(_jsonDataStringChar, _jsonDataString.length() + 1);
    topic.toCharArray(topicChar, topic.length() + 1);

    mqtt.publish(topicChar, _jsonDataStringChar);
    Serial.println();
    Serial.println(topic);
    Serial.println(_jsonDataString);
    Serial.println(_jsonDataString.length());
    Serial.println();
  }
}

void reconnect() {
  reconnect_mqtt();
  topic_sub = "fms/dt/remote/" + cn_str;
  char _jsonDataStringChar[topic_sub.length() + 1];
  topic_sub.toCharArray(_jsonDataStringChar, topic_sub.length() + 1);
  mqtt.subscribe(_jsonDataStringChar);

  String topic_sub1 = "fms/dt/remote";
  char _jsonDataStringChar1[topic_sub1.length() + 1];
  topic_sub1.toCharArray(_jsonDataStringChar1, topic_sub1.length() + 1);
  mqtt.subscribe(_jsonDataStringChar1);
}

boolean mqttConnect()
{
  if (!mqtt.connect(cn_str.c_str(), user.c_str(), pass.c_str()))
  {
    Serial.print(".");
    return false;
  }
  topic_sub = "fms/dt/remote/" + cn_str;
  char _jsonDataStringChar[topic_sub.length() + 1];
  topic_sub.toCharArray(_jsonDataStringChar, topic_sub.length() + 1);
  mqtt.subscribe(_jsonDataStringChar);

  String topic_sub1 = "fms/dt/remote";
  char _jsonDataStringChar1[topic_sub1.length() + 1];
  topic_sub1.toCharArray(_jsonDataStringChar1, topic_sub1.length() + 1);
  mqtt.subscribe(_jsonDataStringChar1);

  Serial.println("Connected to broker.");
  return mqtt.connected();
}

void callback(char* topic, byte* payload, unsigned int length)
{
  String pay = parsing_subscribe(topic, payload, length);
  Serial.print("Data Payload Subscribe : ");
  Serial.println(pay);
  websocket_parse(pay);
  pub("fms/dt/device/callback/" + cn_str, "device message received");

  if (pay == "update")
  {
    pub("fms/dt/device/callback/" + cn_str, "update OTA proccess");
    Serial.println("Update Firmware by OTA");
    delay(2000);
    ota();
  }

  if (pay == "restart")
  {
    pub("fms/dt/device/callback/" + cn_str, "send restart done");
    Serial2.println("{\"restart\":\"" + String(1) + "\"}");
    delay(3000);
    ESP.restart();
  }

  if (pay == "online_check")
  {
    pub("fms/dt/device/callback/" + cn_str, "send online check proccess");
    pub("fms/dt/device/online_check/" + cn_str, "online");
    pub("fms/dt/device/callback/" + cn_str, "send online check done");
  }

  if (pay == "config_info") {
    pub("fms/dt/device/callback/" + cn_str, "send config info proccess");
    String get_config = config_info();
    pub("fms/dt/device/config_info/" + cn_str, get_config);
    pub("fms/dt/device/callback/" + cn_str, "send config info done");
  }

  if (pay == "device_info") {
    pub("fms/dt/device/callback/" + cn_str, "send device info proccess");
    pub("fms/dt/device/device_info/" + cn_str, parameter_update);
    pub("fms/dt/device/callback/" + cn_str, "send device info done");
  }
}

String parsing_subscribe(char* topic, byte* payload, unsigned int length)
{
  String _receivedTopic = String(topic);
  String payloadString, parsedStringx;
  for (int i = 0; i < length; i++)
  {
    payloadString += char(payload[i]);
  }
  parsedStringx = payloadString;
  return parsedStringx;
}

void reconnect_mqtt() {
  Serial.println();
  Serial.println("Searching for provider.");
  byte count_network = 0;
  while (!modem.waitForNetwork() and count_network < 3)
  {
    if ((millis() - prevmqtt) > 5000) {
      loop_mqtt();
      prevmqtt = millis();
    }
    login();
    mainn();
    csq = modem.getSignalQuality();
    loop_RTC();
    receivedData();
    loop_wifi();
    serial_monitor();
    esp_task_wdt_reset();
    count_network++;
    Serial.println("fail, count return: " + String(count_network));
  }

  if (!modem.waitForNetwork()) {
    Serial.println("Not Connect to provider.");
  }
  else {
    Serial.println("Connected to provider.");
    Serial.println("Signal Quality: " + String(modem.getSignalQuality()));
    Serial.println();
  }


  Serial.println("Connecting to GPRS network.");
  byte count_gprs = 0;
  while (!modem.gprsConnect("internet", "", "") and count_gprs < 3)
  {
    if ((millis() - prevmqtt) > 5000) {
      loop_mqtt();
      prevmqtt = millis();
    }
    login();
    mainn();
    csq = modem.getSignalQuality();
    loop_RTC();
    receivedData();
    loop_wifi();
    serial_monitor();
    esp_task_wdt_reset();
    count_gprs++;
    Serial.println("fail, count return: " + String(count_gprs));
  }

  if (!modem.gprsConnect("internet", "", "")) {
    Serial.println("Not Connect to GPRS: " + String(apn));
    Serial.println();
  }
  else {
    Serial.println("Connected to GPRS: " + String(apn));
    Serial.println();
  }

  mqtt.setServer((char*) broker.c_str(), 1883);
  mqtt.setCallback(callback);

  Serial.println("Connecting to MQTT Broker: " + String(broker));
  byte count_mqtt = 0;
  while (mqttConnect() == false and count_mqtt < 3) {
    if ((millis() - prevmqtt) > 5000) {
      loop_mqtt();
      prevmqtt = millis();
    }
    login();
    mainn();
    csq = modem.getSignalQuality();
    loop_RTC();
    receivedData();
    loop_wifi();
    serial_monitor();
    esp_task_wdt_reset();
    count_mqtt++;
    Serial.println("fail, count return: " + String(count_mqtt));
  }
  Serial.print("mqtt state: " + String(mqtt.state()));
  Serial.println();

  topic_sub = "fms/dt/remote/" + cn_str;
  char _jsonDataStringChar[topic_sub.length() + 1];
  topic_sub.toCharArray(_jsonDataStringChar, topic_sub.length() + 1);
  mqtt.subscribe(_jsonDataStringChar);

  String topic_sub1 = "fms/dt/remote";
  char _jsonDataStringChar1[topic_sub1.length() + 1];
  topic_sub1.toCharArray(_jsonDataStringChar1, topic_sub1.length() + 1);
  mqtt.subscribe(_jsonDataStringChar1);
}
