
 String server = "";
 String ip = "192.168.0.36";
 String id_bd = "";
 
// Conexión a la red 

 const char *ssid = "HOME78";
 const char *password = "HOME781097";

 //Librerias necesarias
 
 #include <ArduinoJson.h>
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 #include <WiFiClient.h>

//Definicion de puertos y variables


#define D2   4  //GPIO4
#define D4   2  //GPIO2 - TXD1
int switch_pin1 = D2; //Derecha
int switch_pin2 = D4; //Izquierda
String dato = "";

void setup() {
  Serial.begin(115200);
  pinMode(switch_pin1, INPUT);
  pinMode(switch_pin2, INPUT);

  //Conexión Wi-fi
  Serial.println("Wifi Conectado");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("IP Address : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    //Codigo del interruptor
    if((digitalRead(switch_pin1) == 0)&&(digitalRead(switch_pin2) == 0)&&(dato != "Centro"))
    {
      Serial.println("Estado del switch Centro");
      dato = "Centro";
      post(dato);
    }
    if((digitalRead(switch_pin1) == 1)&&(dato !="Derecha"))
    {
      Serial.println("Estado del switch Derecha");
      dato = "Derecha";
      post(dato);
    }
    if((digitalRead(switch_pin2) == 1)&&(dato != "Izquierda"))
    {
      Serial.println("Estado del switch Izquierda");
      dato = "Izquierda";
      post(dato);
    }
    delay(1000);
  }
}

// Envio de datos a metodo PostDat/

void post(String est){
  Serial.println("Inicio Post");
  HTTPClient http;
  String json;
  server = "http://"+ip+":8080/PostDat/";

  StaticJsonDocument<256> doc;
  doc["estado"] = est;
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("\nTermino Post");
}
