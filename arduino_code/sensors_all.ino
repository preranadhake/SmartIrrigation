#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "realme 11x 5G";
const char* password = "tejas006";

// MQTT Broker details
const char* mqtt_server = "broker.emqx.io";
// const char* mqtt_user = "YOUR_MQTT_USERNAME";
// const char* mqtt_password = "YOUR_MQTT_PASSWORD";

// Define MQTT topics
const char* tempHumTopic = "sensor/dht11";
const char* soilMoistureTopic = "sensor/soil";
const char* pirTopic = "sensor/pir";

// Define DHT11 sensor parameters
#define DHTPIN 4  // DHT11 connected to GPIO15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Define other sensor pins
#define SOIL_MOISTURE_PIN 33  // Soil moisture analog pin
#define PIR_PIN 14            // PIR sensor connected to GPIO4

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
const long interval = 2000;  // Publish interval in milliseconds

// Calibration values
const int sensorMin = 350;  // Minimum reading for 0% moisture (dry)
const int sensorMax = 800;  // Maximum reading for 100% moisture (wet)

// Function to connect to WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect to the MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();

  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    // Read DHT11 data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
      String tempHumPayload = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";
      client.publish(tempHumTopic, tempHumPayload.c_str());
      Serial.println("DHT11 Data Published: " + tempHumPayload);
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }

    // Read Soil Moisture data
    int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    String soilMoisturePayload = "{\"soil_moisture\": " + String(soilMoistureValue) + "}";
    // Convert the reading to a percentage
    // int moisturePercentage = map(soilMoistureValue, sensorMin, sensorMax, 100, 0);
    // moisturePercentage = constrain(moisturePercentage, 0, 100);  // Ensure value is between 0 and 100
    // char moistureString[8];
    // itoa(moisturePercentage, moistureString, 10);

    float soilMoisturePercentage = 100.0 * ((float)(sensorMax - soilMoistureValue) / (sensorMax - sensorMin));
    soilMoisturePercentage = soilMoisturePercentage < 0 ? 0 : soilMoisturePercentage > 100 ? 100 : soilMoisturePercentage;
    soilMoisturePayload = "{\"soil_moisture\": " + String(soilMoisturePercentage) + "}";

    

    client.publish(soilMoistureTopic, soilMoisturePayload.c_str());
    // client.publish(soilMoistureTopic, moistureString);
    Serial.println("Soil Moisture Data Published: " + soilMoisturePayload);

    // Read PIR data
    int pirState = digitalRead(PIR_PIN);
    String pirPayload = "{\"motion\": " + String(pirState) + "}";
    client.publish(pirTopic, pirPayload.c_str());
    Serial.println("PIR Data Published: " + pirPayload);
  }
}
