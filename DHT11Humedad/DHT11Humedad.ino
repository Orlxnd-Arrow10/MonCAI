#include "secrets.h"
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <DHT.h>
#include <Adafruit_CCS811.h>
#include <esp_system.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

Adafruit_CCS811 ccs;

char ID_DEVICE[13]; // Variable para almacenar el ID del dispositivo

char AWS_IOT_PUBLISH_TOPIC[23] = "IAQ/";

float h, t;

// Calibration offsets
float tempCalibrationOffset = -2.5; // Offset for temperature calibration
float humidityCalibrationOffset = -6.8; // Offset for humidity calibration
int co2CalibrationOffset = 44;

char payload[512];
DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure net;
PubSubClient client(net);

void setupWiFiManager()
{
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  if (!wifiManager.autoConnect("Bio-Data"))
  {
    Serial.println("Failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void saveConfigCallback()
{
  Serial.println("Configuration saved");
}

void connectAWS()
{
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  strcat(AWS_IOT_PUBLISH_TOPIC, ID_DEVICE);
  Serial.println(AWS_IOT_PUBLISH_TOPIC);
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  
  while (!client.connect(ID_DEVICE))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["h"] = h;
  doc["t"] = t;
  doc["c"] = ccs.geteCO2() + co2CalibrationOffset;
  doc["v"] = ccs.getTVOC();
  
  sprintf(payload, "{\"idDispositivo\":\"%s\",\"h\":%f,\"t\":%f,\"c\":%d,\"v\":%d}", ID_DEVICE, h, t, ccs.geteCO2()+ co2CalibrationOffset, ccs.getTVOC());
  client.publish(AWS_IOT_PUBLISH_TOPIC, payload);
}

void setup()
{
  Serial.begin(115200);
  uint64_t chipId = ESP.getEfuseMac();
  sprintf(ID_DEVICE, "%04X%08X", (uint16_t)(chipId >> 32), (uint32_t)chipId);
  setupWiFiManager();
  
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  
  dht.begin();
  connectAWS();
}

void loop()
{
  h = dht.readHumidity() + humidityCalibrationOffset;
  t = dht.readTemperature() + tempCalibrationOffset;

  if(ccs.available() && !ccs.readData()){
    Serial.print(ID_DEVICE);
    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
    Serial.print(" CO2: ");
    Serial.print(ccs.geteCO2()+ co2CalibrationOffset);
    Serial.print(" PPM ");
    Serial.print(" TVOC: ");
    Serial.println(ccs.getTVOC());
    Serial.print(" PPB ");
    
    publishMessage();
  }
  client.loop();
  delay(10000);
}
