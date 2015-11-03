# M8N-GPS-Data-Logger
GPS data logger uisng U-blox M8N gps, Arduino Nano, and SD card reader

Introduction
The goal for this project is a cheep and simple high frequence (10Hz) GPS datalogger that I can use during different activitis like motocrossing and mountain biking. I based it on Arduino Nano with U-blox M8N GPS, microSD card module, and a small 2s(7.4V) lithium battrey.
I wanted the data to be saved in a way that it could be imported to "DASHWARE". DASHWARE is a free software that let you overlay video with data like speed, laptime, distance, map, etc. collected form a GPS but also other logged data like heartrate etc.

I searched the webb for a good M8N gps parser library and struggled to find one that could read the UBX-NAV-PVT protocol. I tried iforce2d's "10Hz U-blox binary GPS data in 66 lines of code (arduino) " on youtube with no success to modifie it for the PVT protocol. I came across a few more libaries and sattled for code shared by Jordi Muñoz and Jose Julio, DIYDrones.com. I made a few changes to adopt tothe PVT protocol and it worked really well.

Function
Two LED's give feedback on SD card and GPS status.
A push button starts and stopps the data logging and it's saved to a new file for each log.
The GPS sends only the UBX-NAV-PVT protocol 10 times per second (10Hz).
The Arduino Nano parse  recieved GPS data and save it to a log file on the microSD card.

All info from the PVT protocol could be saved but I choosed some and formed the output to look like this.

Time, Date, Clock, Latitude, Longitutde, Speed, Altitude, Number_of_Satelites, Fix
XXX.X, XX-X-XXXX, X:XX:XX, XX.XXXXXXX, -XXX.XXXXXXX, X.XX, XX.XX, X, X
528.4, 11-2-2015, 8:59.39, 33.1946182, -117.2495269, 4.15, 77.82, 4, 3
528.5, 11-2-2015, 8:59.39, 33.1946258, -117.2495269, 4.14, 77.32, 4, 3
528.6, 11-2-2015, 8:59.39, 33.1946372, -117.2495117, 4.29, 76.97, 4, 3
528.7, 11-2-2015, 8:59.39, 33.1946411, -117.2495117, 4.31, 76.83, 5, 3
528.8, 11-2-2015, 8:59.39, 33.1946372, -117.2495117, 4.21, 76.77, 5, 3
528.9, 11-2-2015, 8:59.39, 33.1946372, -117.2495269, 4.08, 76.75, 5, 3
