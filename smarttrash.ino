#include <HCSR04.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "uTimerLib.h"

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.108", 1883);
Adafruit_MQTT_Publish niveauPub(&mqttClient, "/trash");

UltraSonicDistanceSensor distanceSensor(27, 26);


void limite(){

double distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
    if(distance < 10 && distance > 0){
      niveauPub.publish("attention");
      }
  }

void setup() {
  
WiFi.begin("createch2019", "createch2019");
delay(4000);

Serial.begin(115200);

TimerLib.setInterval_s(limite, 2);

}

void loop() {

  


if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  }

}
