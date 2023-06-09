#include <ESP8266WiFi.h> 
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define engine 12  
#define dados 13

WiFiClient wifiClient; 
PubSubClient MQTT(wifiClient);
OneWire oneWire(dados);
DallasTemperature sensors(&oneWire);

const char* SSID = "Primarada";               
const char* PASSWORD = "@RTX1080";                          
 
const char* BROKER_MQTT = "test.mosquitto.org"; 
int BROKER_PORT = 1883;
long int timeEngine = 0;           

#define ID_MQTT  "RTX43"             
#define TOPIC_SUBSCRIBE "Fish_Feeder_Project_Mackenzie"  

void startEngineAutomatic(long int timeToActiveEngine);
void startEngine();
void stopEngine();
void keepConnectionAlive();  
void WifiConnect();     
void MQTTConnect();     
void receivePackage(char* topic, byte* payload, unsigned int length);
void sendMessageToBroker();

void setup() {        
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(engine,OUTPUT);
  Serial.begin(115200);

  sensors.begin();
  WifiConnect();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);  
  MQTT.setCallback(receivePackage); 
}

void loop() {
  keepConnectionAlive();
  startEngineAutomatic(timeEngine);
  MQTT.loop();
}

void keepConnectionAlive() {
    if (!MQTT.connected()) {
       MQTTConnect(); 
    }
    
    WifiConnect();
}

void WifiConnect() {

  if (WiFi.status() == WL_CONNECTED) {
     return;
  }
        
  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");

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

void MQTTConnect() { 
    while (!MQTT.connected()) {
          Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conexão com Broker realizada com sucesso!");
            MQTT.subscribe(TOPIC_SUBSCRIBE);
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

void receivePackage(char* topic, byte* payload, unsigned int length) 
{
    String msg;
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }

    if (msg == "0") {
       stopEngine();
    }

    if (msg == "1") {
      startEngine();
    }
}

void startEngine(){
  digitalWrite(engine, HIGH);
  delay(3000);
}
void stopEngine(){
 digitalWrite(engine, LOW);
}

void startEngineAutomatic(long int timeToActiveEngine){
  if(timeToActiveEngine == 28800000){
      startEngine();
      stopEngine();
      timeEngine = 0;
    }
    timeEngine++;
}

void sendMessageToBroker() { 
 sensors.requestTemperatures();
 MQTT.publish(TOPIC_SUBSCRIBE, sensors.getTempCByIndex(0));
}
