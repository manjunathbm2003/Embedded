// WireData - Version: Latest 
#include <WireData.h>

// Adafruit GFX Library - Version: Latest 
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>
#include <splash.h

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>




const char* ssid = "Chandu";
const char* password = "Chandu018";

/*   Main Code start   */
const unsigned long BOT_MTBS = 1000;
const int flexPin1 = 33;  // Pin connected to voltage divider output
const int flexPin2 = 35;
const int flexPin3 = 32;
// Change these constants according to your project's design
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 22000.0;
unsigned long bot_lasttime;// resistor used to create a voltage divider
/*   Main Code start   */

#define BOTtoken "5574225837:AAGpmSSzJ3ettEfjzGtWIvjvF77sImgS72c"
#define CHAT_ID "1200895023"



#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(921600);

 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
 

  delay(2000);         // wait for initializing
  display.clearDisplay(); // clear display

  display.setTextSize(2);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 0);  // position to display
  /*   Main Code end  */
  
  
   // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    
    
  }

Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}


void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/Take Your Medicine")
    {
          display.clearDisplay();
        	display.setTextSize(2);
        	display.setTextColor(WHITE);
        	display.setCursor(0, 10);
        	display.print("Take Your Medicine");
        	display.display(); 
          delay(2000);
    }

    if (text == "/Kindly take your water")
    {
      display.clearDisplay();
    	display.setTextSize(2);
    	display.setTextColor(WHITE);
    	display.setCursor(0, 10);
    	display.print("Kindly take your water");
    	display.display();
      delay(2000);
    }

    if (text == "/Kindly come and eat")
    {
      display.clearDisplay();
  	  display.setTextSize(2);
    	display.setTextColor(WHITE);
    	display.setCursor(0, 10);
	    display.print("Kindly come and eat");
    	display.display();
      delay(2000);
      }
    if (text == "/start")
    {
      String welcome = "Welcome to Iot project on Deaf and Dumb, " + from_name + ".\n";
      welcome += "This is for your Deaf and Dumb friend.\n\n";
      welcome += "/Take Your Medicine : click to say him \n";
      welcome += "/Kindly take your water : click to say him\n";
      welcome += "/Kindly come and eat : click to say him\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }

}



void loop() 
{

if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();

  // Read the ADC, and calculate voltage and resistance from it
  int ADCflex1 = analogRead(flexPin1);
  int ADCflex2 = analogRead(flexPin2);
  int ADCflex3 = analogRead(flexPin3);
  
  
  
  Serial.print("Res1:" + String(ADCflex1) + " ohms\t");
  Serial.print("Res2:" + String(ADCflex2) + " ohms\t");
  Serial.print("Res3:" + String(ADCflex3) + " ohms\t");
  delay(500);

display.clearDisplay(); // clear display
if(ADCflex1>1320 && ADCflex2<1910 && ADCflex3<1400)
{
 display.clearDisplay();
 display.setTextSize(2);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);  // position to display
  display.print("FOOD"); // text to display
  display.display(); 
  delay(2000);
  
  bot.sendMessage(CHAT_ID, "I NEED FOOD", "");
    Serial.println("I NEED FOOD");
   
}
display.clearDisplay(); 
if(ADCflex1<1350 && ADCflex2>1910 && ADCflex3<1400)
{
 display.clearDisplay();
 display.setTextSize(2);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);  // position to display
  display.print("WATER"); // text to display
  display.display();
  delay(2000);
  
  bot.sendMessage(CHAT_ID, "I NEED WATER", "");
    Serial.println("I NEED WATER");
}
display.clearDisplay(); 
if(ADCflex1<1350 && ADCflex2<1910 && ADCflex3>1400)
{
 display.clearDisplay();
 display.setTextSize(2);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);  // position to display
  display.print("MEDICINE"); // text to display
  display.display();   
  delay(2000);
  
  bot.sendMessage(CHAT_ID, "I NEED MY MEDICINE", "");
    Serial.println("I NEED MEDICINE");
}
display.clearDisplay(); 
}
}