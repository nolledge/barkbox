#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
int D8_Input = 15;

// WiFi
const char* ssid = "YOUR-SSID";
const char* password = "YOUR-WIFI-PW";

// MQTT Broker
const char *mqtt_broker = "192.168.0.14";
const char *topic = "livingroom/barkbox";
const char *mqtt_username = "admin";
const char *mqtt_password = "admin123";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(9600);
  pinMode(D8_Input, INPUT); // Set pin D8 as digital output

 // attempt wifi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Connected to discstation MQTT broker");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
 
}

void loop(){
   client.loop();
  int val_digital = digitalRead(D8_Input);


  if (val_digital){
    Serial.print("Wooof");
     // publish and subscribe
    client.publish(topic, "1");
    delay(500);
    }
}
