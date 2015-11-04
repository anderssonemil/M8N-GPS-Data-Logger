/*
  Example of GPS UBLOX library based on Code by Jordi Muñoz and Jose Julio. DIYDrones.com 

  Modified by Emil Andersson, https://github.com/anderssonemil/M8N-GPS-Data-Logger
  Modified to read UBX M8N PVT protocol
  Added SD logging, debounce and LED functions
 */

#include <GPS_UBLOXPVT.h> // UBLOX GPS Library
#include <SD.h>
#include <SPI.h>
#include <Time.h>  

//SD Card Variables
String fileName ="x.txt"; //Used to store last saved file number file name
int current_file = 0 ; //Used to store saved file number
String fileType = ".txt";  //String to add to new log file
const int chipSelect = 4; //For the SD card
int recordState; //Recording SD ON/OFF
boolean SDSetup = 0; //0 =S D not yet setup, 1 = SD setup and ready to go


//Button Variables
const int buttonIn =  9; //Trigger botton, Normal Low, Trigged High
long lastDebounceTime = 0;  // The last millis time output pin was toggled
long debounceDelay = 50;    // Dbounce time; increase if the output flickers
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin


//LED Variables
unsigned long lastMillis = 0; //Start timer for the LED's
const int blinkInterval = 1000; //Base Blink time in ms
const int blinkOnTime = 200;  //Time in ms LED stay's on when triggered
short loopCount =0; //Keeps track of loops for the blinking function

//LED array to set up and control the LED's state
//RED used for SD card
//Green for GPS status
int NumbOfLeds = 2; //Set number of LED's
int Led[2][3] ={ 
  {7, 0, 0 }, //RED --  Variables are  PIN, SPEED(# of cycle between blinks), LED function(1 = constant on, 0 = constant off, 2 =  blinking)
  {2, 0, 0 }  //Green --  Variables are  PIN, SPEED(# of cycle between blinks), LED function(1 = constant on, 0 = constant off, 2 =  blinking)
};

//GPS Variables
long GPS_time;  //Time in Seconds from recording starts that is written write to SD card
long Start_millis;    //Set to millis when SD card is set up and first line is written
boolean TimeSetup = false;    //For Time Library setup, FALSE = time not setup, TRUE = time is set up

void setup()
{  
    //Initiate Button
    pinMode(buttonIn, INPUT);
    
    //Initiate LED Pins
    for (int x = 0; x < NumbOfLeds; x++)
    pinMode(Led[x] [0], OUTPUT); //Set up all LED Output Pins

 //LED Test/Initiation message, blinks all LED's quickly a few times
    for (int y = 0; y < 2; y++){
      for (int x = 0; x < NumbOfLeds; x++)
      digitalWrite(Led[x] [0], HIGH); //All LED's on
      delay(100);
      for (int x = 0; x < NumbOfLeds; x++)
      digitalWrite(Led[x] [0], LOW); //All LED's off
      delay(200);
     }
    
    // GPS Initialization
    GPS.Init(); 
    digitalWrite(Led[1][0], HIGH); //Turn on Green LED
    Led[1][2] = 1;
    //delay (200);
    
    
  //SD Start
    if (!SD.begin(chipSelect)) { // see if the card is present and can be initialized:
     // Error Blink RED LED 20 times quickly
     for (int y = 0; y < 20; y++){
      digitalWrite(Led[0] [0], HIGH); //RED LED on
      delay(50);
      digitalWrite(Led[0] [0], LOW); //RED LED off
      delay(150);
     }
    return; // don't do anything more:
  }
    digitalWrite(Led[0][0], HIGH);
    Led[0][2] = 1; // Set RED LED on indicating SD card accessible
}


void loop()
{
 blinkCheck(); //Turns on LEDs that are in cycle for it
 triggerButton(); //Check if trigger is pressed
   if (TimeSetup == false) // Check if time is set
    SetTime(); // Set time if not set and GPS is FIXED
   else
   {
    GPS.Read();   //Start of GPS reading and SD saving
    if (GPS.NewData && recordState){  //Move on if there are any new GPS data and record state is set
        GPS.NewData = 0; // Message to GPS library that new data is recieved
        SDSave();   //Save new GPS data to SD card
        }
      if(GPS.Fix == 0)
        Led[1][2] = 0; //Set Green off if GPS gas no FIX
      else 
       Led[1][2] = 2; //Set Green to blink if GPS has FIX
       
       if (GPS.numSV >= 7)
         Led[1][1] = 0; //Set Green to blink fast if 7 or more satelite are used
          else 
            Led[1][1] = 1; //Set Green to blink slow if less then 7 satelites are used
    }
  }
