#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include "configuration.h"

// #define DHTPIN 14  // Digital pin connected to the DHT sensor = D5
#define DHTPIN 2      // Digital pin connected to the DHT sensor = D4
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

const char* ssid =  WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* endpoint = ENDPOINT;

const char* sensorId = "aiow1";
const float maxVolt = 5.15; // 220k resistor results in 5.15V max
const float voltOffset = 0.0;
const float temperatureOffset = 0.0;
const float humidityOffset = 0.0;

void setup() {
  Serial.begin(115200);
  
Serial.println("Processing start.");
  configureIO();
  initWifiConnection();
  String json = buildJsonPayload();
  sendData(json, 30000, 30000);

Serial.println("Going to sleep.");

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
  if (WiFi.SSID() != ssid) {
    WiFi.begin(ssid, password);
    WiFi.persistent(true);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
  }
}

String buildJsonPayload() {
  float humidity = dht.readHumidity() + humidityOffset;
  float temperature = dht.readTemperature() + temperatureOffset;

  unsigned int raw = analogRead(A0);
  float volt = raw / 1023.0 * maxVolt + voltOffset;

  JSONVar payload;
  payload["sensorId"] = sensorId;
  payload["version"] = "1.0";
  payload["data"]["t"] = temperature;
  payload["data"]["h"] = humidity;
  payload["data"]["U"] = volt;

  return JSON.stringify(payload);
}

void sendData(String json, int wifiTimeout, int httpTimeout) {
  bool isReady = waitUntilWifiIsReady(wifiTimeout);
  if (isReady) {
    Serial.println("Sending data ...");
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, endpoint);
    http.setTimeout(httpTimeout);
    http.addHeader("Content-Type", "application/json");

    int responseCode = http.POST(json);
    Serial.print("Sent data, response code was ");
    Serial.print(responseCode);

    http.end();
  }
}

bool waitUntilWifiIsReady(int timeout) {
  const int waitTime = 1000;
  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < timeout)
  {
    delay(waitTime);
    i += waitTime;
    Serial.println("Connecting to wifi ...");
  }

  Serial.println("Connected to wifi.");

  return WiFi.status() == WL_CONNECTED;
}
