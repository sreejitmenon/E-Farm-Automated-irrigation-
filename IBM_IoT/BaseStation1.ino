
#include <SPI.h>
#include <RH_NRF24.h>


RH_NRF24 nrf24;

int command;

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{
  if(Serial.available() > 0)
  {
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  command=Serial.read();
  uint8_t data =command;
  //uint8_t strdata[10];
  Serial.println(data);
  if(data==49)
  nrf24.send("49", sizeof(49));
   if(data==50)
  nrf24.send("50", sizeof(50));
   if(data==51)
  nrf24.send("51", sizeof(51));
   if(data==52)
  nrf24.send("52", sizeof(52));
  nrf24.waitPacketSent();
  }

}

