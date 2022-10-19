#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          15         // Configurable, see typical pin layout above
int statuss = 0;
int out = 0;

#include <ESP8266WiFi.h>
byte sendEmail(int x);
byte eRcv(WiFiClientSecure client);
void reading();
 String content= "";
  byte letter;
const char* SSID = "ssid username"; 
const char* PASS = "password"; 
const char* user_base64 = "Z2dnbXBtY0BnbWFpbC5jb20NCg=="; // https://www.base64encode.org/
const char* user_password_base64 = "Z2dnbXBtYzEyMw0K"; 
const char* from_email = "MAIL From: <gggmpmc@gmail.com>"; 
const char* admin_email = "RCPT TO: <dowlurisatyaashok@gmail.com>"; 
const char* user_email = "RCPT TO: <dowlurisatyaashok@gmail.com>"; 
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
void setup() {
   // ESP.wdtDisable();
   pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);   // Initialize serial communications with the PC
  Serial.println("");
  Serial.print("Connecting To ");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
 
}
void loop() {
  // Look for new cards

  delay(5000);
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   Serial.println();
  Serial.print(" UID tag :");
 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

//reading();
if (content.substring(1) == "62 19 57 73") //change UID of the card that you want to give access
  {
    //digitalWrite(LED_BUILTIN,HIGH);
     if (sendEmailadmin(1)) Serial.println(F("Email sent"));
    else Serial.println(F("Email failed"));
    Serial.println(" Access Granted ");
    Serial.println(" Welcome MPMC ");
   // delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
    statuss = 1;
    }
    /*
    else if(content.substring(1) == "62 19 57 73"){
     // digitalWrite(LED_BUILTIN,LOW);
       Serial.println(" Access Granted ");
    Serial.println(" Welcome Mr.Circuit ");
   // delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
        if (sendEmailuser(1)) Serial.println(F("Email sent"));
    else Serial.println(F("Email failed"));
        statuss = 1;
    }
    
   /* label:
     //delay(5000);
     if ( ! mfrc522.PICC_IsNewCardPresent()) {
    goto label;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
   goto label;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   Serial.println();
  Serial.print(" UID tag :");
 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

    //reading();
     
    if (content.substring(1) == "62 19 57 73") //change UID of the card that you want to give access
  {
    //delay(5000);
   // reading();
      
   // if (content.substring(1) == "01 5D 53 2E") //change UID of the card that you want to give access
  //{
    if (sendEmailuser(1)) Serial.println(F("Email sent"));
    else Serial.println(F("Email failed"));
  //}
  }
  else
  goto label;
  }
  // if (sendEmail(1)) Serial.println(F("Email sent"));
   //    else Serial.println(F("Email failed"));
  
  
  else   {
    Serial.println(" Access Denied ");
    delay(3000);
  }*/
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  //delay(1000);

}
void reading(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   Serial.println();
  Serial.print(" UID tag :");
 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();


  
}
byte sendEmailadmin(int x) 
{
  WiFiClientSecure client;
  if (client.connect("smtp.gmail.com", 465) == 1) Serial.println(F("connected"));
  else {   Serial.println(F("connection failed"));   return 0; }
  
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending EHLO")); client.println("EHLO 1.2.3.4"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending login")); client.println("AUTH LOGIN"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending User base64")); client.println(user_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending Password base64")); client.println(user_password_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending From")); client.println(from_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending To")); client.println(admin_email); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending To")); client.println(user_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending DATA")); client.println(F("DATA")); if (!eRcv(client)) return 0;
  client.println(F("Subject: Smart library\r\n"));
  client.println(F("Book XYZ issued to Mr. Ashok\n"));
  client.println(x);
  client.println(F("."));
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv(client)) return 0;
  client.stop();
  return 1;
}
byte sendEmailuser(int x) 
{
  WiFiClientSecure client;
  if (client.connect("smtp.gmail.com", 465) == 1) Serial.println(F("connected"));
  else {   Serial.println(F("connection failed"));   return 0; }
  
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending EHLO")); client.println("EHLO 1.2.3.4"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending login")); client.println("AUTH LOGIN"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending User base64")); client.println(user_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending Password base64")); client.println(user_password_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending From")); client.println(from_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending To")); client.println(user_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending DATA")); client.println(F("DATA")); if (!eRcv(client)) return 0;
  client.println(F("Subject: Smart library\r\n"));
  client.println(F("Book A issued\n"));
  client.println(x);
  client.println(F("."));
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv(client)) return 0;
  client.stop();
  return 1;
}
byte eRcv(WiFiClientSecure client)
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;
  while (!client.available()) {
    delay(1);
    loopCount++;
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }
  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }
  if (respCode >= '4')return 0;
  return 1;
}

