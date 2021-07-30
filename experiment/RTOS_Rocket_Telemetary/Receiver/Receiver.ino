#include <LoRa.h>
#include <SPI.h>
 
void setup() 
{
  Serial.begin(115200);
  Serial.println("LoRa Receiver");
 
  while (!LoRa.begin(433E6))     
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xB3);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
  int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize) 
  {
    
    Serial.print("Received packet '");
 
    while (LoRa.available())              // read packet
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }
    Serial.print("' with RSSI ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }
}
