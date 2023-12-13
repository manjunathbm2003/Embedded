#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 10
#define in4 11
#define relay1 9 //Y-Axis Rotation Relay
#define relay2 8 //Y-Axis Rotation Relay
#define relay3 7 //X-Axis Rotation Relay
#define relay4 3 //X-Axis Rotation Relay
#define relayW 4 //PUMP Relay



int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
boolean lightFront = false;
boolean lightBack = false;
boolean horn = false;

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //pinMode(light_FR, OUTPUT);
  //pinMode(light_FL, OUTPUT);
  //pinMode(light_BR, OUTPUT);
  //inMode(light_BL, OUTPUT);
  //pinMode(horn_Buzz, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relayW, OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.read();
    Stop(); //Initialize with motors stoped.

    if (lightFront)
    {
      
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
    }
    if (!lightFront)
    {
      
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
    }
    if (lightBack)
    {
      digitalWrite(relay2, LOW);
      digitalWrite(relay1, HIGH);
      
    }
    if (!lightBack)
    {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      
    }
    if (horn)
    {
      digitalWrite(relayW, LOW);
      
    }
    if (!horn)
    {
      digitalWrite(relayW, HIGH);
      
    }
    switch (command)
    {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
      case 'W':
        lightFront = true;
        break;
      case 'w':
        lightFront = false;
        break;
      case 'U':
        lightBack = true;
        break;
      case 'u':
        lightBack = false;
        break;
      case 'V':
        horn = true;
        break;
      case 'v':
        horn = false;
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1)
    {
      brakeOn();
    }
    else
    {
      brakeOff();
    }
  }
}

void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}
void forwardleft() {

  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}
void forwardright()
{
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}
void backright()
{

}
void backleft()
{

}

void Stop()
{
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void brakeOn()
{
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState)
  {
    // if the state has changed, increment the counter
    if (buttonState == 'S')
    {
      if (lastButtonState != buttonState)
      {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff()
{

}
