#include <ESP32Servo.h>

#include <ESP32Tone.h>
#include <ESP32PWM.h>

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

Servo myservo;  // Create a servo object

#define otp_Length 5

const char* ssid = "Manjunath's iPhone";
const char* password = "manjunath1122";

String phoneNumber = "+919945761637";
String apiKey = "3144812";


char Master[otp_Length] = "1111";
char Data[otp_Length];
char otp[otp_Length] = "1478";

byte data_count = 0;

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {13, 14, 15, 16};
byte colPins[COLS] = {17, 18, 19}; 

LiquidCrystal_I2C lcd(0x27,16,2); 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

 
void sendMessage(String message){


  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}



void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("--IoTCrew--");
  lcd.setCursor(1,1);
  lcd.print("OTP PROJECT");
  delay(3000);
  lcd.clear();

  myservo.attach(12);  // Attach the servo to pin 9
  myservo.write(0);  // Set the initial position of the servo
  delay(2000);  // Wait for the servo to reach the initial position

  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());



}
  
void loop()
{
  char customKey = customKeypad.getKey();
  

  lcd.setCursor(0, 0);
  lcd.print("OPEN LID:         ");

  if (customKey) 
  {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == otp_Length - 1) 
  {
    lcd.clear();
  
    if (!strcmp(Data, Master)) {
      lcd.print("...UNLOCKED...");
      rotateServo(90);  // Rotate the servo 90 degrees
      delay(5000);  // Wait for 5 minutes
      rotateServo(0);  // Return the servo to the original position
      delay(5000);  // Wait for 5 minutes before repeating
      lcd.clear();
      clearData();
      lock();

    }

    else
    {
      lcd.print("**ERROR**");
      delay(2000);
      lcd.clear();
      clearData();
    }

  }

}

void lock()
{
  lcd.clear();
  lcd.print("Generating OTP...");
  delay(2000);

  String otp = generateRandomOTP();
  sendMessage(otp);

  Serial.print(otp);
  lcd.clear();
  lcd.print("Enter OTP:");
  lcd.setCursor(0, 1);
  lcd.blink();

  String input;  // Variable to store user input

  while (input.length() < otp_Length) {
    char key = customKeypad.getKey();

    if (key) {
      input += key;
      lcd.print('*');
    }
  }

  lcd.noBlink();

  if (input == otp) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access granted");
    rotateServo(90);  // Rotate the servo 90 degrees
    delay(5000);  // Wait for 5 minutes
    rotateServo(0);  // Return the servo to the original position
    delay(5000);  // Wait for 5 minutes before repeating

  } else {
    lcd.clear();
    lcd.print("Incorrect OTP");
    delay(2000);  // Display the message for 2 seconds before retrying
    lock();
  }
}

String generateRandomOTP() {
  String otp;

  for (int i = 0; i < otp_Length; i++) {
    char digit = random(10) + '0';
    otp += digit;
  }

  return otp;
}


void clearData() 
{

  while (data_count != 0)
  {
    Data[data_count--] = 0;
  }
  return;
}

void rotateServo(int angle) {
  int currentAngle = myservo.read();
  if (currentAngle < angle) {
    for (int i = currentAngle; i <= angle; i++) {
      myservo.write(i);
      delay(15);
    }
  } else {
    for (int i = currentAngle; i >= angle; i--) {
      myservo.write(i);
      delay(15);
    }
  }
}