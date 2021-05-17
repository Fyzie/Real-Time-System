#include <Arduino.h>

#include <SPI.h>

#include <LoRa.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int counter = 0;

#define ss 10
#define rst 9
#define dio0 2

void setup() {

  //Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.backlight();//To Power ON the back light

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("LoRa Receiver");
  delay(3000);
  lcd.clear();

  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(433E6)) {
    //lcd.setCursor(0,0);
    lcd.print(".");
    delay(500);
    counter++;
    if (counter > 3) {
      lcd.clear();
      counter = 0;
    }
  }
  LoRa.setSyncWord(0xF3);
}

void loop() {

  // try to parse packet

  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(LoRaData);
    }

    // print RSSI of packet
    lcd.setCursor(0,1);
    lcd.print("with RSSI ");
    lcd.print(LoRa.packetRssi());
  }
}
