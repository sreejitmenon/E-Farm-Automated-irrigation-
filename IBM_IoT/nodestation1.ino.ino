#include "DHT.h"
#define dht_apin 2 // Analog Pin sensor is connected to
#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;//Server

dht DHT;//Humididty and Temp sensor
 
void setup(){
  pinMode(A1,OUTPUT);
  pinMode(A0,OUTPUT);
  Serial.begin(9600);
  while (!Serial) ;
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 
  DHT.read11(dht_apin);
    if (nrf24.available())
  {  
    uint8_t buf[2];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf,&len))
    {//nrf24.recv(buf,&len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
      
     
    }}
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    Serial.print("%  ");
    Serial.print("moisture : ");
    int sensorValue = analogRead(A0);
    // print out the value of moisture:
    Serial.println(sensorValue);
    delay(1);
    // value of water level
    Serial.print("water level");
    Serial.println(analogRead(A1));
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
 
}// end loop() 
