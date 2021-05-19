#include <ESP8266WiFi.h> // WiFi
#include <ESP8266HTTPClient.h> // HTTP
#include <DHT.h>

#define DHTTYPE DHT11 // maybe remove
#define DHT_PIN 13 // 7 in lua
#define RED_LED 0 // 3 in lua
#define GREEN_LED 12 // 6 in lua

const char * ssid = "Marian's iPhone";
const char * password = "vaccaaaa";

// VARIABLES
bool notificationSent = false;
float temperature_threshold = 0; // set number
float humidity_threshold = 0; // set number

DHT dht(DHT_PIN, DHTTYPE); // DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  callHook();
}

void loop() {
//  float humidity = dht.readHumidity();
//  float temperature = dht.readTemperature(); 
//   
//  if(temperature > temperature_threshold){
//    digitalWrite(GREEN_LED, LOW);
//    digitalWrite(RED_LED, HIGH);
//    if (notificationSent == false) {
//      callHook();
//      notificationSent = true;
//    }
//  } else {
//    digitalWrite(GREEN_LED, HIGH);
//    digitalWrite(RED_LED, LOW);
//    notificationSent = false;
//  }
  delay(1000);
}

void callHook(){
  char* FINGERPRINT = "b871167c629f5eaa3346832a7e95ad4be6b2b807";
  String endpoint = "https://maker.ifttt.com/trigger/HumidityAlarm/with/key/dBKze72tDrvKY-1GGB1UNb";
  HTTPClient http;
  Serial.print("Calling webhook");
  http.begin(endpoint, FINGERPRINT);
  int httpCode = http.GET();
  Serial.print("Response: "); Serial.println(httpCode);

  http.end();
}
