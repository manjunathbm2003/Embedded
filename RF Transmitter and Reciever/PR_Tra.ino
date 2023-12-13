#include <RH_ASK.h> 
#include <SPI.h>  
const char *message = ""; 
int button = 4; 
RH_ASK driver(2000,12,2,0); 
void setup() { 
 Serial.begin(9600); // Debugging only 
 if (!driver.init()){ 
   Serial.println("init of receiver failed"); 
 } 
 pinMode(button,INPUT); 
} 
void loop(){ 
 if (digitalRead(button) == HIGH){ 
   message="a"; 
   driver.send((uint8_t *)message, strlen(message)); // send the message 
   driver.waitPacketSent(); // Wait until the whole message is gone 
   Serial.println(message); 
   Serial.println(strlen(message)); 
   delay(2000); 
   } 
  else
  { 
   //Serial.println("Low"); 
  } 
}  
