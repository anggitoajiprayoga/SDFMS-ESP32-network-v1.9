#define TINY_GSM_MODEM_SIM7600
#include <Arduino.h>
#include <esp_task_wdt.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
#include "SD.h"
#include <SPI.h>
#include <RtcDS3231.h>
#include <TimeLib.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Update.h>

#define WDT_TIMEOUT 60
#define SD_CS 5
#define RXD1 27
#define TXD1 26
#define PROTOCOL SERIAL_8N1
#define PKEY 14
#define RST 12
#define rx 33
#define tx 32
#define SerialMon Serial
#define SerialAT Serial1

String version = "Firm v1.7 - SDCMS FMS DT V1";
String firm_ver = "v1.9";
String xfirm_ver;
String type_board = "SDCMS V5 Board";
String timeZone_str = "+8:00";
String type_unit = "DT";
String sn_str = "1234";

String http_username;
String http_password;
String ssid_wifi_client;
String pass_wifi_client;
String ssid_wifi_ap;
String pass_wifi_ap;
String freesp, usedstr, totalstr;

String webpage = "";  //String to save the html code
const int time_push = 10000; // Post data per 10s
unsigned long cur_time_respon, old_time_respon;
unsigned long cur_time_led, old_time_led;
unsigned long cur_time_push, old_time_push;
unsigned long lastTime = 0;
String buf_message_push, date_time;
String brand, engTorque, engSpeed, tacVehSpeed, accPed, engLoad, actRet, brakePedPos, airPress1, airPress2, airPress3, engEr, fuelRate, engHm, engClnTemp, fuelLvl, vehSpeed;
bool hold = 0;

String ssid;
String wifipassword;
String httpuser;
String httppassword;
int webserverporthttp;

bool shouldReboot = false;
String listFiles(bool ishtml = false);

const String default_ssid = "";
const String default_wifipassword = "SS6";
const String default_httpuser = "admin";
const String default_httppassword = "admin";
const int default_webserverporthttp = 80;

String no_simcard;
const char apn[]      = "Internet";
const char gprsUser[] = "";
const char gprsPass[] = "";

const char server_gsm[] = "ss6api.ppa-mhu.net";
const int  port         = 80;

String keyword_subscribe, topic_sub, en_lte, en_traccar, server_traccar, port_traccar, en_http, server_http, resource, en_mqtt, broker, user, pass, mqtt_state, interval_http, interval_traccar, interval_mqtt;
uint64_t sizeTotal, sizeKB, totalKB, usedKB, usedB, spaceKB;
uint32_t usedByte;
bool SD_present = false, deleting = false;
char cn_charArray[15], date_chr[10], id_chr[10];
String titleFile, idDel_str, titleId, id_str, cn_softAP, dataJson_str, dataLog_str, cn_str, lat_str, lng_str, alt_str,
       spd_str, agl_str, st_str, heading_str, date_str, dateLog_str, datePost_str, time_str, fatigue_str;
String sn, sn_dev, ind, en_anglewarning, limit_angle;
String en_fatiq, en_fms, en_overspeed, overspeed, limit_speed, set_bitrate;
String state_gprs;
String relay_dump, relay_buzzer, status_sdcard, dump_status, adc_pto, ignition;
int enCn;
unsigned long intervalLogging = 600;  // ← Logging data to SD Card every 10 minutes
unsigned long lastMillisLogging = 0;
unsigned long lastMillis;
long prev_mqtt, prev_http, prev_traccar, prev_sermon;
int time_login, csq;
long prev_login, prev_config, prevmqtt;
bool user_login, state, simbol;

String times, dates;
String input, enCn_str, receiveCN;
String imei, ussd_phone_num, ccid;
char tanggalx[15];
char waktux[15];

int Year;
byte Month;
byte Day;
byte Hour;
byte Minute;
byte Second;

String server_ota, resource_ota;
const int port_ota = 80;

float hm_start, hm_stop, hm_opr;
byte shift, xshift;
String last_hm;
String timer_hmOn, timer_idleOn, timer_standbyOn, timer_dumpingOn;
String tanggal_hmOn, tanggal_idleOn, tanggal_standbyOn, tanggal_dumpingOn;
String timer_hmOff, timer_idleOff, timer_standbyOff, timer_dumpingOff;
String tanggal_hmOff, tanggal_idleOff, tanggal_standbyOff, tanggal_dumpingOff;
bool hm, standby, idle, dumping, en_writehm, en_writeidle, en_writestandby, en_writedumping;

String total_jamhm;
String total_jamidle;
String total_jamstandby;
String total_jamdumping;

String final_hm;
String final_idle;
String final_standby;
String final_payload;

int selisih_jamhm;
int selisih_mnthm;
int selisih_dtkhm;
int selisih_jamidle;
int selisih_mntidle;
int selisih_dtkidle;
int selisih_jamstandby;
int selisih_mntstandby;
int selisih_dtkstandby;
int selisih_jamdumping;
int selisih_mntdumping;
int selisih_dtkdumping;

char selisih_hm[15];
char selisih_idle[15];
char selisih_standby[15];
char selisih_dumping[15];
char time_updatehm[15];
char time_updateidle[15];
char time_updatestandby[15];
char time_updatedumping[15];

String jam_hmOn;
String jam_hmOff;
String mnt_hmOn;
String mnt_hmOff;
String dtk_hmOn;
String dtk_hmOff;

String jam_idleOn;
String jam_idleOff;
String mnt_idleOn;
String mnt_idleOff;
String dtk_idleOn;
String dtk_idleOff;

String jam_standbyOn;
String jam_standbyOff;
String mnt_standbyOn;
String mnt_standbyOff;
String dtk_standbyOn;
String dtk_standbyOff;

String jam_dumpingOn;
String jam_dumpingOff;
String mnt_dumpingOn;
String mnt_dumpingOff;
String dtk_dumpingOn;
String dtk_dumpingOff;

String tahun_hmOn, bulan_hmOn, hari_hmOn;
String tahun_hmOff, bulan_hmOff, hari_hmOff;
String tahun_idleOn, bulan_idleOn, hari_idleOn;
String tahun_idleOff, bulan_idleOff, hari_idleOff;
String tahun_standbyOn, bulan_standbyOn, hari_standbyOn;
String tahun_standbyOff, bulan_standbyOff, hari_standbyOff;
String tahun_dumpingOn, bulan_dumpingOn, hari_dumpingOn;
String tahun_dumpingOff, bulan_dumpingOff, hari_dumpingOff;

String value_day, value_month, value_year;
String value_hour, value_minute, value_second;
String tahun, bulan, jam, menit, detik, waktu;

String hm_starting, hm_stoping, dataLog, status_device, last_event, AP_state;
String standby_hmOff, standby_hmOn, idle_hmOn, idle_hmOff, dumping_hmOn, dumping_hmOff;
long prev_health, prev_Liveloc, prev_update;
float agl_float;
String last_updatehm, last_updateidle, last_updatesb, last_updatedumping, last_act;
bool hm_update, idle_update, sb_update, wifi_ap, en_update;
String parameter_update, adc_kontak, eng_state, time_update;
bool eror_rtc, eror_sd, eror_canbus, eror_lcd, eror_gps, eror_rs485, eror_communication;

//Config config;
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
WiFiServer serverAP(80);
RtcDS3231 <TwoWire> Rtc(Wire);
time_t prevDisplay = 0;
PubSubClient mqtt(client);
SoftwareSerial serial(rx, tx); //RS232

String payload() {
  //  DynamicJsonDocument buffer(1024);
  StaticJsonDocument<1024> buffer;
  JsonObject obj       = buffer.to<JsonObject>();
  obj["cn"]            = cn_str;
  obj["brand"]         = brand;
  obj["datetime"]      = dates + " " + times;
  obj["lat"]           = lat_str;
  obj["long"]          = lng_str;
  obj["alt"]           = alt_str;
  obj["spd"]           = spd_str;
  obj["heading"]       = heading_str;
  obj["sat"]           = st_str;
  obj["agl"]           = agl_str;
  obj["fatique"]       = fatigue_str;
  obj["ind"]           = ind;
  obj["state_network"] = state_gprs;
  obj["csq"]           = csq;
  obj["relay_dump"]    = relay_dump;
  obj["relay_buzzer"]  = relay_buzzer;
  obj["sd_card"]       = status_sdcard;
  obj["dump_status"]   = dump_status;
  obj["state_pto"]     = adc_pto;
  obj["engTorque"]     = engTorque;
  obj["engSpeed"]      = engSpeed;
  obj["tacVehSpeed"]   = tacVehSpeed;
  obj["accPed"]        = accPed;
  obj["engLoad"]       = engLoad;
  obj["actRet"]        = actRet;
  obj["brakePedPos"]   = brakePedPos;
  obj["airPress1"]     = airPress1;
  obj["airPress2"]     = airPress2;
  obj["airPress3"]     = airPress3;
  obj["fuelRate"]      = fuelRate;
  obj["engEr"]         = engEr;
  obj["engHm"]         = engHm;
  obj["engClnTemp"]    = engClnTemp;
  obj["fuelLvl"]       = fuelLvl;
  obj["vehSpeed"]      = vehSpeed;
  String jsonString;
  serializeJsonPretty(obj, jsonString);
  return jsonString;
}

String config_info() {
  String device_config = "";
  //  DynamicJsonDocument buffer(1024);
  StaticJsonDocument<1024> buffer;
  JsonObject obj         = buffer.to<JsonObject>();
  obj["cn"]              = cn_str;
  obj["sn"]              = sn_str;
  obj["en_fatiq"]        = en_fatiq;
  obj["en_anglewarning"] = en_anglewarning;
  obj["angle_warning"]   = limit_angle;
  obj["en_fms"]          = en_fms;
  obj["brand"]           = brand;
  obj["set_bitrate"]     = set_bitrate;
  obj["en_overspeed"]    = en_overspeed;
  obj["overspeed"]       = overspeed;
  obj["date"]            = "";
  obj["time"]            = "";
  obj["en_lte"]          = en_lte;
  obj["en_traccar"]      = en_traccar;
  obj["server_traccar"]  = server_traccar;
  obj["port_traccar"]    = port_traccar;
  obj["interval_traccar"] = interval_traccar;
  obj["en_mqtt"]         = en_mqtt;
  obj["broker"]          = broker;
  obj["username"]        = user;
  obj["pass"]            = pass;
  obj["interval_mqtt"]   = interval_mqtt;
  obj["server_ota"]      = server_ota;
  obj["resource_ota"]    = resource_ota;
  obj["imei"]            = imei;
  obj["no_simcard"]      = no_simcard;
  serializeJson(obj, device_config);
  return device_config;
}

String payload_health() {
  String json_health = "";
  //  DynamicJsonDocument buffer(1024);
  StaticJsonDocument<1024> buffer;
  JsonObject obj  = buffer.to<JsonObject>();
  obj["sn"]       = sn_str;
  obj["cn"]       = cn_str;
  obj["brand"]    = brand;
  obj["type"]     = type_unit;
  obj["shift"]    = shift;
  obj["dateTime"] = dates + " " + times;
  obj["timeZone"] = timeZone_str;
  obj["io33"]     = engTorque.toInt();
  obj["io2"]      = atof(engSpeed.c_str());
  obj["io34"]     = atof(tacVehSpeed.c_str());
  obj["io35"]     = atof(accPed.c_str());
  obj["io4"]      = atof(engLoad.c_str());
  obj["io25"]     = atof(actRet.c_str());
  obj["io22"]     = atof(brakePedPos.c_str());
  obj["io36"]     = atof(airPress1.c_str());
  obj["io37"]     = atof(airPress2.c_str());
  obj["io12"]     = atof(engHm.c_str());
  obj["io1"]      = atof(engClnTemp.c_str());
  obj["io24"]     = atof(fuelLvl.c_str());
  obj["io31"]     = atof(vehSpeed.c_str());

  JsonObject dataSupport = obj.createNestedObject("data");
  dataSupport["dateTime"] = dates + " " + times;
  dataSupport["timeZone"] = timeZone_str;
  dataSupport["lat"] = atof(lat_str.c_str());
  dataSupport["lng"] = atof(lng_str.c_str());
  dataSupport["alt"] = atof(alt_str.c_str());
  dataSupport["spd"] = atof(spd_str.c_str());
  dataSupport["hdg"] = atof(heading_str.c_str());
  serializeJsonPretty(obj, json_health);
  return json_health;
}

String eror_kode() {
  String state_eror = "";
  DynamicJsonDocument buffer(1024);
  JsonObject obj             = buffer.to<JsonObject>();
  obj["state_canbus"]        = eror_canbus;
  obj["state_lcd"]           = eror_lcd;
  obj["state_gps"]           = eror_gps;
  obj["state_rs485"]         = eror_rs485;
  obj["state_rtc"]           = eror_rtc;
  obj["state_sd"]            = eror_sd;
  obj["state_communication"] = eror_communication;
  serializeJsonPretty(obj, state_eror);
  return state_eror;
}

String liveLocations() {
  String livelocation = "";
  DynamicJsonDocument buffer(1024);
  JsonObject obj  = buffer.to<JsonObject>();
  obj["sn"]       = sn_str;
  obj["cn"]       = cn_str;
  obj["type"]     = type_unit;
  obj["dateTime"] = dates + " " + times;
  obj["timeZone"] = timeZone_str;
  obj["lat"]      = atof(lat_str.c_str());
  obj["lng"]      = atof(lng_str.c_str());
  obj["alt"]      = atof(alt_str.c_str());
  obj["spd"]      = atof(spd_str.c_str());
  obj["hdg"]      = atof(heading_str.c_str());
  obj["rssi"]     = csq;
  obj["firm"]     = firm_ver;
  serializeJson(obj, livelocation);
  return livelocation;
}

String payload_location() {
  String json_location = "";
  //  DynamicJsonDocument buffer(1024);
  StaticJsonDocument<1024> buffer;
  JsonObject obj   = buffer.to<JsonObject>();
  obj["sn"]        = sn_str;
  obj["cn"]        = cn_str;
  obj["brand"]     = brand;
  obj["type"]      = type_unit;
  obj["shift"]     = shift;
  obj["dateTime"]  = dates + " " + times;
  obj["timeZone"]  = timeZone_str;
  obj["tilt"]      = agl_str;
  obj["pto"]       = adc_pto.toInt();
  obj["ignition"]  = ignition;
  obj["eng_state"] = eng_state;
  obj["duration"]  = String(time_update);
  obj["firm"]      = firm_ver;
  obj["rssi"]      = csq;

  JsonObject dataSupport = obj.createNestedObject("data");
  dataSupport["dateTime"] = dates + " " + times;
  dataSupport["timeZone"] = timeZone_str;
  dataSupport["lat"] = atof(lat_str.c_str());
  dataSupport["lng"] = atof(lng_str.c_str());
  dataSupport["alt"] = atof(alt_str.c_str());
  dataSupport["spd"] = atof(spd_str.c_str());
  dataSupport["hdg"] = atof(heading_str.c_str());
  serializeJsonPretty(obj, json_location);
  return json_location;
}

String payload_production(String condition, int _shift, String time_start, String time_stop, String duration, String hmstart, String hmstop) {
  String json_production = "";
  //  DynamicJsonDocument buffer(1024);
  StaticJsonDocument<1024> buffer;
  JsonObject obj  = buffer.to<JsonObject>();
  obj["sn"]       = sn_str;
  obj["cn"]       = cn_str;
  obj["brand"]    = brand;
  obj["type"]     = type_unit;
  obj["shift"]    = _shift;
  obj["dateTime"] = dates + " " + times;
  obj["timeZone"] = timeZone_str;
  obj["cdt"]      = condition;
  obj["str"]      = time_start;
  obj["stp"]      = time_stop;
  obj["drt"]      = duration;
  obj["hmstr"]    = atof(hmstart.c_str());
  obj["hmstp"]    = atof(hmstop.c_str());

  JsonObject dataSupport = obj.createNestedObject("data");
  dataSupport["dateTime"] = dates + " " + times;
  dataSupport["timeZone"] = timeZone_str;
  dataSupport["lat"] = atof(lat_str.c_str());
  dataSupport["lng"] = atof(lng_str.c_str());
  dataSupport["alt"] = atof(alt_str.c_str());
  dataSupport["spd"] = atof(spd_str.c_str());
  dataSupport["hdg"] = atof(heading_str.c_str());
  serializeJsonPretty(obj, json_production);
  return json_production;
}

void notifyClients(String payload) {
  ws.textAll(payload);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    Serial.println((char*)data);
    websocket_parse(String((char*)data));
    String get_payload = payload();
    //    Serial.println("//web_socket_payload_receive//");
    //    Serial.println(get_payload);
    notifyClients(get_payload);

    if (strcmp((char*)data, "kalibrasi") == 0) {
      Serial2.println("{\"kalibrasi\":\"1\"}");
      Serial.println("kalibrasi trigger");
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      user_login = true;
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      user_login = false;
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      Serial.printf("WebSocket client #%u pong received\n", client->id());
      break;
    case WS_EVT_ERROR:
      Serial.println("WebSocket error occurred. Restarting ESP32...");
      user_login = false;
      delay(2000);
      ESP.restart();
      break;
  }
}


void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() {
  Serial.begin(115200); // ← Debug Serial Monitor Baud
  serial.begin(9600);
  setup_esp32_to_atmega2560();
  setup_sd_card();
  SPIFFS.begin();
  read_setting();
  setup_webserver();
  setup_wifi();
  initWebSocket();
  setup_rtc();
  status_device = "booting";

  if (en_lte == "true") {
    Serial.println("LTE Enable");
    setup_sim7600ce();
  }
  else {
    Serial.println("LTE Disable");
  }

  if (en_mqtt == "true" and en_lte == "true") {
    Serial.println("mqtt Enable");
    setup_mqtt();
  }
  else {
    Serial.println("mqtt Disable");
  }
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
}

void loop() {
  parameter_update = payload();
  login();
  loop_RTC();
  receivedData();
  loop_wifi();
  mainn();
  serial_monitor();
  esp_task_wdt_reset();
  status_device = "looping";
}
