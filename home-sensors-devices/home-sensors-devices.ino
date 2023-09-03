// #define DEBUG

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include "configuration.h"

// #define DHTPIN 14  // Digital pin connected to the DHT sensor = D5
#define DHTPIN 2      // Digital pin connected to the DHT sensor = D4
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  logIfDebug("Processing start.");

  configureIO();
  initWifiConnection();
  String json = buildJsonPayload();
  sendData(json, 30000, 30000);

  logIfDebug("Going to sleep.");

  ESP.deepSleep(600e6); // sleep 600s = 10min
}

void loop() {
  // nothing to do
}

void configureIO() {
  pinMode(A0, INPUT);
  dht.begin();
}

void initWifiConnection() {
  if (WiFi.SSID() != WIFI_SSID) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.persistent(true);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
  }
}

String buildJsonPayload() {
  logIfDebug("Reading sensor values ...");
  float humidity = dht.readHumidity() + HUMIDITY_OFFSET;
  float temperature = dht.readTemperature() + TEMPERATURE_OFFSET;

  unsigned int raw = analogRead(A0);
  float volt = raw / 1023.0 * MAX_VOLTAGE + VOLTAGE_OFFSET;

  logIfDebug("Building json payload ...");
  JSONVar payload;
  payload["sensorId"] = SENSOR_ID;
  payload["version"] = "1.0";
  payload["data"]["t"] = temperature;
  payload["data"]["h"] = humidity;
  payload["data"]["U"] = volt;

  return JSON.stringify(payload);
}

void sendData(String json, int wifiTimeout, int httpTimeout) {
  bool isReady = waitUntilWifiIsReady(wifiTimeout);
  if (isReady) {
    logIfDebug("Sending data ...");
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, ENDPOINT);
    http.setTimeout(httpTimeout);
    http.addHeader("Content-Type", "application/json");

    int responseCode = http.POST(json);

#ifdef DEBUG
    Serial.print("Sent data. Status code: ");
    Serial.println(responseCode);
#endif

    http.end();
  }
}

bool waitUntilWifiIsReady(int timeout) {
  const int waitTime = 2000;
  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < timeout)
  {
    delay(waitTime);
    i += waitTime;
    logIfDebug("Connecting to wifi ...");
  }

  logIfDebug("Connected to wifi.");

  return WiFi.status() == WL_CONNECTED;
}

void logIfDebug(char* message) {
#ifdef DEBUG
  Serial.println(message);
#endif
}
