void startSD(){
    File commandFile = SD.open("FILE.txt");
    if (commandFile)
      {
        //Reads the "Last_File _Number.txt" to get last saved file number
        while(commandFile.available())
        {
      current_file = commandFile.parseInt();
        }
        commandFile.close();
    
      File commandFile = SD.open("FILE.txt", FILE_WRITE);
      commandFile.seek(0);
      current_file = ++ current_file;
      commandFile.print(current_file);
      fileName = current_file + fileType;
      commandFile.close();
      }
    else
    {
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
    File dataFile = SD.open(fileName, FILE_WRITE);
      if (dataFile)
      {
        dataFile.println("Time, Date, Clock, Latitude, Longitutde, Speed, Altitude, Number_of_Satelites, Fix");
        dataFile.close();
      }
      for (int y = 0; y < 2; y++){
      digitalWrite(Led[0][0], HIGH); //Set up all LED Output Pins
      delay(50);
      digitalWrite(Led[0][0], LOW); //Set up all LED Output Pins
      delay(150);
     }
     SDSetup = HIGH;
      Start_millis = millis();
    }

void SDSave(){
  // SD Card Saving  
    if (SDSetup == LOW){
      startSD();
    }
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile)
    {
    dataFile.print((millis()- Start_millis)/1000.0f,1); dataFile.print(", ");
    dataFile.print(month()); dataFile.print("-"); dataFile.print(day()); dataFile.print("-");  dataFile.print(year());  dataFile.print(", "); 
    dataFile.print(hour());  dataFile.print(":"); dataFile.print(minute()); dataFile.print(".");  dataFile.print(second()); dataFile.print(", ");
    dataFile.print(GPS.Lattitude/10000000.0f,7); dataFile.print(", ");
    dataFile.print(GPS.Longitude/10000000.0f,7); dataFile.print(", ");
    dataFile.print(GPS.Ground_Speed/1000.0f,2); dataFile.print(", ");
    dataFile.print(GPS.Altitude/1000.0f,2); dataFile.print(", ");
    dataFile.print(GPS.numSV); dataFile.print(", ");
    dataFile.println(GPS.Fix);
    dataFile.close();
    }
  }

 

void triggerButton(){
  int reading = digitalRead(buttonIn); // read the state of the switch into a local variable:
  if (reading != lastButtonState)  // reset the debouncing timer
    lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) { // only toggle if the new button state is HIGH
        recordState = !recordState;
          if (recordState == HIGH){
          Led[0][2] = 2; // Blinking on
          Led[0][1] = 1; // Blinking Slow
        }
       else
       Led[0][2] = 0; //Turn the bliinikng off
      }
    }
  }
  lastButtonState = reading;
}

void SetTime(){
  {
    GPS.Read();
     if (GPS.NewData && GPS.Fix != 0)
     {
      if (GPS.Year != 0)
        {
        setTime(GPS.Hour,GPS.Min,GPS.Sec,GPS.Day,GPS.Month,GPS.Year); 
        adjustTime(-7 * SECS_PER_HOUR);
        TimeSetup = true;
        }       
     }
   }
}

void blinkCheck(){
unsigned long currentMillis = millis(); //Set currentMillis whent he function starts so that same time ref is used 
 if (millis() - lastMillis >= blinkInterval){ // Now chekcing if it's time to trigger a blink 
  //Serial.print("Checktime, Loop count is "); Serial.println(loopCount);
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

