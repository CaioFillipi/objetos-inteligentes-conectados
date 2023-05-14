#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

#define btnPushBroker 12

WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);

const char* SSID = "Primarada";
const char* PASSWORD = "@RTX1080";
                      
const char* BROKER_MQTT = "test.mosquitto.org";
int BROKER_PORT = 1883;

#define ID_MQTT  "RTX42"
#define QUEE_TOPIC "Fish_Feeder_Project_Mackenzie"

void MQTTConnection();
void sendPackage();
void keepConnectionsAlive();
void WifiConnection();

void setup() {
  pinMode(btnPushBroker, INPUT_PULLUP);         

  Serial.begin(115200);

  WifiConnection();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
}

void loop() {
  keepConnectionsAlive();
  sendMessageToBroker();
  MQTT.loop();
}

void keepConnectionsAlive() {
    if (!MQTT.connected()) {
       MQTTConnection(); 
    }
    WifiConnection();
}

void WifiConnection() {

  if (WiFi.status() == WL_CONNECTED) {
     return;
  }
        
  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);

  WiFi.begin(SSID, PASSWORD); 
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Conectado na rede: ");
  Serial.print(SSID);  
  Serial.print("  IP: ");
  Serial.println(WiFi.localIP()); 
}

void MQTTConnection() { 
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conexão com Broker realizada com sucesso!");
        } 
        else {
            Serial.println("Conexão com o Broker ");
            Serial.println(BROKER_MQTT);
            Serial.println(" falhou!");
            Serial.println("Nova tentatica de conexão em 10 segundos");
            delay(10000);
        }
    }
}

void sendMessageToBroker() {
static bool statePushButton = HIGH;
static bool statePushButtonAnt = HIGH;
static unsigned long debouncePushButton;

  statePushButton = digitalRead(btnPushBroker);
  if (  (millis() - debouncePushButton) > 30 ) {
     if (!statePushButton && statePushButtonAnt) {    
        MQTT.publish(QUEE_TOPIC, "1");
        debouncePushButton = millis();
     } else if (statePushButton && !statePushButtonAnt) {
        MQTT.publish(QUEE_TOPIC, "0");
        debouncePushButton = millis();
     }
  }
  statePushButtonAnt = statePushButton;
}
