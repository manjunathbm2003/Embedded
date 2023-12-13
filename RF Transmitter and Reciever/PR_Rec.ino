#include <RH_ASK.h> 
#include <SPI.h>  
RH_ASK driver; //pin 12
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11 
int ledPassive = 5; //standby light 
int ledActive = 7; //green LED's 
void setup() 
{ 
 pinMode(ledPassive,OUTPUT); 
 pinMode(ledActive,OUTPUT); 
 Serial.begin(9600); // Debugging only 
 if (!driver.init()) 
 Serial.println("init of receiver failed"); 
} 
void loop() 
{ 
 digitalWrite(ledPassive,HIGH); 
 noTone(8); 
 digitalWrite(ledActive,LOW); 
 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; 
 uint8_t buflen = sizeof(buf); 
 if (driver.recv(buf, &buflen)) { // if message received 
   for(int i=0;i<sizeof(buf);i++){ 
     Serial.print(char(buf[i])); //test display output 
   } 
   if(buf[0]=='a'){ // and if the first letter in message array is X 
     digitalWrite(ledPassive,LOW); 
     for(int i=0;i<10;i++){ // loop alternates between LED and buzzer 
       digitalWrite(ledActive,HIGH); 
       tone(8, 262); //pin 8
       delay(100); 
     } 
   } 
    else if(buf[0]!='a'){ 
     digitalWrite(ledPassive,HIGH); 
     noTone(8); 
    } 
   } 
}
