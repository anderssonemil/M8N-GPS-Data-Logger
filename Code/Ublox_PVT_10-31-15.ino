/*
  Example of GPS UBLOX library. Code by Jordi Muñoz and Jose Julio. DIYDrones.com 

  Modified by Emil Andersson, emil.and@gmail.com
  Modified to read UBX M8N PVT protocol
  Added SD logging, debounce and LED functions
 */

#include <GPS_UBLOXPVT.h> // UBLOX GPS Library
#include <SD.h>
#include <SPI.h>
#include <Time.h>  

//SD Card Variables
String fileName ="x.txt"; //Last saved file number file name
int current_file = 0 ; //Last saved file number
String fileType = ".txt";
const int chipSelect = 4; //For the SD card
int recordState; //Recording SD ON/OFF
boolean SDSetup = 0;


//Button Variables
const int buttonVcc =  5; //Set 5v for the butotn
const int buttonIn =  9; //Normal low, high when triggered
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin


//LED Variables
unsigned long lastMillis = 0;
const int blinkInterval = 1000;
const int blinkOnTime = 200;
short loopCount =0;
int NumbOfLeds = 2; //Set number of LED's
int Led[2][3] ={ // Led setup -> Pin, Speed (# of cycle between blink), over right of code(1=keep on, 0=keep off, 2= keep blinking)
  {7, 0, 0 }, //Red
  {2, 0, 0 }  //Green
};

//GPS Variables
long GPS_time;
long Start_millis;
boolean TimeSetup = false;

void setup()
{  
    //Initiate Button
    pinMode(buttonIn, INPUT);
    
    //Initiate LED Pins
    for (int x = 0; x < NumbOfLeds; x++)
    pinMode(Led[x] [0], OUTPUT); //Set up all LED Output Pins

 //LED test
    for (int y = 0; y < 2; y++){
      for (int x = 0; x < NumbOfLeds; x++)
      digitalWrite(Led[x] [0], HIGH); //Set up all LED Output Pins
      delay(100);
      for (int x = 0; x < NumbOfLeds; x++)
      digitalWrite(Led[x] [0], LOW); //Set up all LED Output Pins
      delay(200);
     }
    
    // GPS Initialization
    GPS.Init(); 
    digitalWrite(Led[1][0], HIGH); //Turn the Green on
    Led[1][2] = 1;
    //delay (200);
    
    
  //SD Start
    if (!SD.begin(chipSelect)) { // see if the card is present and can be initialized:
     // Error Bliink LED
     for (int y = 0; y < 20; y++){
      digitalWrite(Led[0] [0], HIGH); //Set up all LED Output Pins
      delay(50);
      digitalWrite(Led[0] [0], LOW); //Set up all LED Output Pins
      delay(150);
     }
    // don't do anything more:
    return;
  }
    digitalWrite(Led[0][0], HIGH);
    Led[0][2] = 1; // Set Red High indicating SD card active
}
  
void loop()
{
 blinkCheck(); //Turns on LEDs that are in cycle for it
 triggerButton(); //Check if trigger is pressed
   if (TimeSetup == false) // Set time when GPS first have it avalible
    SetTime(); // Set up the time from GPS if avalible
   else
   {
    GPS.Read();
    if (GPS.NewData && recordState){  // New GPS data and in record state then get new GPS data
        GPS.NewData = 0; // We have read the data
        SDSave();
        }
      if(GPS.Fix == 0)
        Led[1][2] = 0; //Set the Green off
      else 
       Led[1][2] = 2; //Start blink
       
       if (GPS.numSV >= 7)
         Led[1][1] = 0; //Set led blink to fast
          else 
            Led[1][1] = 1; //Set led blink to fast
    }
  }




