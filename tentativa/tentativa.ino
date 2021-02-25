#include <Wire.h>
#include <SPI.h> 
#include <MFRC522.h> 
 
#define SS_PIN 10 
#define RST_PIN 9 
 
MFRC522 rfid(SS_PIN, RST_PIN); 

const int pinoLedVerde = 3; 
const int pinoLedVermelho = 2; 
 
void setup(){
 
  Wire.begin(); 
  SPI.begin(); 
  rfid.PCD_Init(); 

  pinMode(6,OUTPUT);
  
  pinMode(pinoLedVerde, OUTPUT); 
  pinMode(pinoLedVermelho, OUTPUT); 


  
  digitalWrite(pinoLedVerde, HIGH); 
  digitalWrite(pinoLedVermelho, HIGH); 
  delay(1000);
  
  tone(6,262,1000); 
  
  delay(1000);
  digitalWrite(pinoLedVerde, LOW); 
  digitalWrite(pinoLedVermelho, LOW); 
  
}
 
void loop() {
  leituraRfid();
}
 

void leituraRfid(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) 
    return; 
 
  String strID = ""; 
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
 
  if (strID.indexOf("27:F1:D9:29") >= 0) {
    digitalWrite(pinoLedVerde, HIGH); 
    tone(6,392,200);
    delay(500);
    tone(6,392,200);
     
    delay(3000); 
    digitalWrite(pinoLedVerde, LOW); 
  }else{
    digitalWrite(pinoLedVermelho, HIGH); 
     tone(6,349,1000);
    
    delay(3000); 
    digitalWrite(pinoLedVermelho, LOW); 
  }
 
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1(); 
  }
