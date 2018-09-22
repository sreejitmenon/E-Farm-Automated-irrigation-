#include <ArduinoHttpClient.h>

#include<ESP8266WiFi.h>
#include<Adafruit_MQTT_Client.h>



int dthv=0;
int soilv=0;
int inputPin1=16;
int inputPin2 = 17 ; 
#define wifi "Suraj" 
#define password "abcd1234"
#define server "io.adafruit.com"
#define port 1883
#define user "Sreejit"
#define pass "tijeers11"
#define key "4dad2145d0cb4a37a297c6b10b5d91d0"


//WiFiServer server(80);
WiFiClient esp;

Adafruit_MQTT_Client mqtt(&esp,server,port,user,key);

Adafruit_MQTT_Publish feed1= Adafruit_MQTT_Publish(&mqtt,user "/feeds/Data2");

Adafruit_MQTT_Publish feed2= Adafruit_MQTT_Publish(&mqtt,user "/feeds/Data");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.println(wifi);

  WiFi.begin(wifi,password);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

Serial.println("WiFi connected");
Serial.println("IP Address:");
Serial.println(WiFi.localIP());
Serial.println("Connecting to MQTT");
while(mqtt.connect())
  Serial.print(".");
   pinMode(inputPin1, INPUT); 
    pinMode(inputPin2,INPUT);
}

void loop() {

 soilv = digitalRead(inputPin1); 
 Serial.println(soilv);// read input value 
 dthv=analogRead(inputPin2);
 Serial.println(dthv);

  // put your main code here, to run repeatedly:
if(mqtt.connected())
{
  if(feed1.publish(dthv) && feed2.publish(soilv))
    Serial.println("Success");
  else
    Serial.println("Fail!!");
  delay(1000);
}

}
