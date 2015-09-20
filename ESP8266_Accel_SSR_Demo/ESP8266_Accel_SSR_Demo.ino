/*
 Control a solid state relay based on orientation (shutdown if upside down)
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 17th, 2015
 License: This code is public domain but you buy me a beer if you use this and 
 we meet someday (Beerware license).

 Controls the relay remotely unless accelerometer detects that 
 we are upside down.

 Uses the SparkFun ESP8266 Thing, LSM6DS3 IMU, an SSR and the mobile app Blynk.
 The LSM6DS3 is I2C and has the SparkFun standard I2C pinout so it solders 
 directly onto the ESP8266 Thing. 

 In Blynk You'll need to have a data display tied to virtual pin V0,
 a button tied to virtual pin V2, and a value gauge tied to virtual pin
 V1 with min/max values of -2/2. If you want to receive push notifications
 you'll also need the notifications widget.
 
*/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>  

SimpleTimer timer;

#include "SparkFunLSM6DS3.h" //
#include "Wire.h"
#include "SPI.h"

char auth[] = "my auth code";
char ssid[] = "wifi id";
char pass[] = "wifi pw";

LSM6DS3 myIMU; //Default constructor is I2C, addr 0x6B

boolean notifyBlynkPlease = false;

boolean safetyOverride = false; //Keeps track of whether or not it's safe to fire cannon

#define RELAY 0
#define LED 5

void setup()
{
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(57600);

  myIMU.begin(); //Configure the IMU

  timer.setInterval(110L, sendUpdate); //Start timer to send report to blynk every 500ms
  timer.setInterval(1000L, blink); //Blink the status LED
  
  Blynk.begin(auth, ssid, pass); //Log into Blynk server
}

void loop()
{
  Blynk.run();
  timer.run();

  float z = myIMU.readFloatAccelZ();

  Serial.print("Z:");
  Serial.print(z, 2);

  if(z < 0)
  {
    Serial.println("You're upside down! Turning off flame cannon.");

    notifyBlynkPlease = true;
    safetyOverride = true; //Disable user control
    digitalWrite(RELAY, LOW);
  }
  else
    safetyOverride = false; //It's ok to fire the cannon
    
  Serial.print(" Temp:");
  Serial.print(myIMU.readTempF(), 2);
  Serial.print(" F ");

  Serial.println();

  delay(50);
}

//Send the latest data to blynk
void sendUpdate()
{
    
  //Display z on the phone
  Blynk.virtualWrite(V1, myIMU.readFloatAccelZ());
  
  //Display temp on the phone
  Blynk.virtualWrite(V0, myIMU.readTempF());

  if(notifyBlynkPlease == true)
  {
    notifyBlynkPlease = false;
    Blynk.notify("You're upside down! Turning off flame cannon."); //Push a message to the phone
  }
}

//Check if user pressed the flame cannon button on their phone
BLYNK_WRITE(V2)
{
  Serial.print("Got a value: ");
  Serial.println(param.asInt());

  if(param.asInt() == 1)
  {
    Serial.println("Phone button pressed");
    if(safetyOverride == false)
    {
      Serial.println("Activating fire cannon");
      digitalWrite(RELAY, HIGH);
    }
    else
      digitalWrite(RELAY, LOW);
  }
  else
    digitalWrite(RELAY, LOW);
}

//Show me you are alive
//Toggle/Blink the onboard LED every second
void blink()
{
  if(digitalRead(LED) == LOW) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}

