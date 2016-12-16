
 
 //Read Logger Configurations from SD card
void GetLoggerConfig(){
    File commandFileConfig = SD.open("Config.txt");
    if (commandFileConfig)
      {
        //Reads the "Config.txt" to get GPS refresh rate
        GPS_Refresh_Rate = commandFileConfig.parseInt();
        //timeCorrection = commandFileConfig.parseInt();
        }
        commandFileConfig.close();
      }

//Get last saved file number and increase it with 1. Write first line to new log file
void startSD(){
    File commandFile = SD.open("COUNTER.txt");
    if (commandFile)
      {
        //Reads the "Last_File _Number.txt" to get last saved file number
        while(commandFile.available())
        {
      current_file = commandFile.parseInt();
        }
        commandFile.close();
    
      File commandFile = SD.open("COUNTER.txt", FILE_WRITE);
      commandFile.seek(0);
      current_file = ++ current_file;
      commandFile.print(current_file);
      fileName = current_file + fileType;
      fileNameCSV = current_file + fileTypeCSV;
      commandFile.close();
      }
    else
    {
    // Error Bliink LED
     for (int y = 0; y < 20; y++){
      digitalWrite(Led[0] [0], HIGH); //RED LED on
      delay(50);
      digitalWrite(Led[0] [0], LOW); //RED LED off
      delay(150);
     }
    return;// don't do anything more:
    }
    
    File dataFile = SD.open(fileName, FILE_WRITE);
      if (dataFile)
      {                   // Write first line(header) to the log file
        dataFile.println("Log saved by ArduinoLogger");
        dataFile.println("Time, Date, Clock, Latitude, Longitude, Speed, Altitude, Number_of_Satelites, Fix");
        dataFile.close();
      }

      //Start CSV log file
      File dataFileCSV = SD.open(fileNameCSV, FILE_WRITE);
      if (dataFileCSV)
      {                   // Write first line(header) to the log file
        dataFileCSV.println("ARDUINO_Time, Latitude, Longitude, Speed");
        dataFileCSV.close();
      }
      
       // Error Bliink LED
      for (int y = 0; y < 2; y++){
      digitalWrite(Led[0][0], HIGH); //RED LED on
      delay(50);
      digitalWrite(Led[0][0], LOW); //RED LED off
      delay(150);
     }
      SDSetup = HIGH;  //Set to High when Header is written and logfile is ready for data to be saved
      Start_millis = millis();    //Set start time of SD save to millis
    }

// Saves data to SD card
void SDSave(){
  // SD Card Saving  
    if (SDSetup == LOW){
      startSD();    //Start up the SD card and writes the header if not done
    }
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile)
    {
    dataFile.print((millis()- Start_millis)/1000.0f,1); dataFile.print(", ");
    dataFile.print(month()); dataFile.print("-"); dataFile.print(day()); dataFile.print("-");  dataFile.print(year());  dataFile.print(", "); 
    dataFile.print(hour());  dataFile.print(":"); dataFile.print(minute()); dataFile.print(".");  dataFile.print(second()); dataFile.print(", ");

    String lattitudeString = String(GPS.Lattitude,DEC);
    int stringLength = (lattitudeString.length());

    // Save Latitude
    dataFile.print(lattitudeString.substring(0,stringLength-7)); dataFile.print(".");
    dataFile.print(lattitudeString.substring(stringLength-7,stringLength)); dataFile.print(", ");

    String longitudeString = String(GPS.Longitude,DEC);
    stringLength = (longitudeString.length());
    
    // Save Longitude
    dataFile.print(longitudeString.substring(0,stringLength-7)); dataFile.print(".");
    dataFile.print(longitudeString.substring(stringLength-7,stringLength)); dataFile.print(", ");

    dataFile.print(GPS.Ground_Speed/1000.0f,2); dataFile.print(", "); // Speed
    dataFile.print(GPS.Altitude/1000.0f,2); dataFile.print(", "); // Altitude

    dataFile.print(GPS.numSV); dataFile.print(", "); // Type of Fix
    
    dataFile.println(GPS.Fix);  // Type of Fix
    dataFile.close();
    }
  

  //Log to CSV file
  File dataFileCSV = SD.open(fileNameCSV, FILE_WRITE);
    if (dataFileCSV)
    {
    dataFileCSV.print((millis()- Start_millis)/1000.0f,1); dataFileCSV.print(", ");

    String lattitudeString = String(GPS.Lattitude,DEC);
    int stringLength = (lattitudeString.length());
 
    dataFileCSV.print(lattitudeString.substring(0,stringLength-7));
    dataFileCSV.print(".");
    dataFileCSV.print(lattitudeString.substring(stringLength-7,stringLength)); dataFileCSV.print(", ");

    String longitudeString = String(GPS.Longitude,DEC);
    stringLength = (longitudeString.length());
 
    dataFileCSV.print(longitudeString.substring(0,stringLength-7));
    dataFileCSV.print(".");
    dataFileCSV.print(longitudeString.substring(stringLength-7,stringLength)); dataFileCSV.print(", ");
   
    dataFileCSV.println(GPS.Ground_Speed/1000.0f,2); //dataFile.print(", ");

    dataFileCSV.close();
    }
  }

 
//Trigger debounce function that controll log recording on and off
void triggerButton(){
  int reading = digitalRead(buttonIn); // Read the state of the switch into a local variable:
  if (reading != lastButtonState)  // Reset the debouncing timer
    lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) { // Only toggle if the new button state is HIGH and set the LED's new state
        recordState = !recordState;
          if (recordState == HIGH){
          Led[0][2] = 2; // Blinking on
          Led[0][1] = 1; // Blinking Slow
        }
       else
       Led[0][2] = 0; //Turn the bliinikng off
       SDSetup = LOW;
      }
    }
  }
  lastButtonState = reading;
}

//Starts up the Time library and set time from GPS
void SetTime(){
  {
    GPS.Read();
     if (GPS.NewData && GPS.Fix != 0)
     {
      if (GPS.Year != 0)
        {
        setTime(GPS.Hour,GPS.Min,GPS.Sec,GPS.Day,GPS.Month,GPS.Year); 
        adjustTime(-8 * SECS_PER_HOUR);
        TimeSetup = true;
        }       
     }
   }
}

//LED blink controller function
void blinkCheck(){
unsigned long currentMillis = millis(); //Set currentMillis whent he function starts so that same time ref is used for all LEDs, keeps the blinking in sync 
 if (millis() - lastMillis >= blinkInterval){ //Now checking if it's time to trigger a blink 
      for (int x = 0; x < NumbOfLeds; x++)
       if (Led[x][2] == 1)
        digitalWrite(Led[x][0], HIGH);
        else
        if (Led[x][1] <= loopCount && (Led[x][2] == 2))
        digitalWrite(Led[x][0], HIGH);
       loopCount = ++loopCount;
   if (loopCount >= 2)
      loopCount = 0;
      lastMillis = millis();
    }
    if (millis() - lastMillis >= blinkOnTime){
     for (int x = 0; x < NumbOfLeds; x++)
        if (Led[x][2] != 1)
        digitalWrite(Led[x][0], LOW);
    }
  }


