#include <Keyboard.h>
#include <Mouse.h>
int x_pin = A0;
int y_pin = A1;
int sw_pin = 2;


unsigned long prevTime_T1 = millis();
long interval_T1 = 1000;
bool enabled = false;
bool pedal = false;
unsigned long currentTime;

bool tolatas = false;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  Mouse.begin();
  Keyboard.begin();
}

void joystickX(int xdata)
{
  if(xdata < 500)
 {
   Serial.print("Balra\n");
   Keyboard.press(216); // Bal nyíl
 }
 else
 {
   Keyboard.release(216);
 }


 if (xdata > 520)
 {
   Serial.print("Jobbra\n");
   Keyboard.press(215); // Jobb nyíl
 }
 else
 {
   Keyboard.release(215);
 }
}
void joystickY(int ydata)
{ 
    tolatas = ydata > 950 ? true : false;
    if(ydata > 950)
    {
      Serial.print("Hátra\n");
      Keyboard.press(217);
    }
    else
    {
      Keyboard.release(217);
    }

    if(ydata < 300)
    {
      Serial.print("Előre\n");
      Keyboard.press(218);
    }
    else
    {
      Keyboard.release(218);
    }

}

void joystickForward(int magnet_data)
{
    if(magnet_data != 0 && !tolatas && !pedal)
    {
        pedal = true;
        prevTime_T1 = currentTime;
        Serial.print("Elore\n");
        Keyboard.press(218);
        enabled = true;
    }
    else if (magnet_data == 0)
    {
        pedal = false;
    }
    
    
  if(enabled)                           // Idő aktív
  {
      Serial.print("Lenyomva Előre\n");
      if(currentTime - prevTime_T1 >= interval_T1)
      {
          Keyboard.release(218);            // Fel engedi a pedált
          enabled = false;                  // Leállítja az időt
      }
  }
}

void joystickClick(int sw_data)
{
    if(sw_data == 0)
    {
        Serial.println("Click\n");
        //Mouse.press(MOUSE_LEFT);
        Keyboard.press(176);
    }
    else
    {
        //Mouse.release(MOUSE_LEFT);
        Keyboard.release(176);
    }
}

void loop()
{
  currentTime = millis();
  int x_data = analogRead(A0);
  int y_data = analogRead(A1);
  int sw_data = digitalRead(2);

  int magnet_data = analogRead(A2);
  int sw2_data = digitalRead(3);

  joystickX(x_data);
  joystickY(y_data);
  joystickClick(sw_data);
  joystickForward(sw2_data);

  delay(100);
 // Teszt
 /*
  Serial.print("Y : ");
  Serial.print(y_data);
  Serial.print("\tX : ");
  Serial.print(x_data);
  Serial.print("\n");
  Serial.print("Magnet : ");
  Serial.print(magnet_data);
  Serial.print("\tDig : ");
  Serial.print(sw2_data);
  Serial.print("\n");
  */  
}
