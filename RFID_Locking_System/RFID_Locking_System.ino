#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define RELAY_PIN 5


bool authorized = false;

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop()
{

  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "03 37 BF 02") //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(RELAY_PIN,LOW);
    Serial.println("Authorized access");
    authorized = true;
    delay(1000);
  }
  else
  {
    digitalWrite(RELAY_PIN,HIGH);
    Serial.println("Access denied");
    authorized = false;
    delay(1000);
  }
}

 
