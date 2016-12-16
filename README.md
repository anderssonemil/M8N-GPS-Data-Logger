# M8N-GPS-Data-Logger
GPS data logger uisng U-blox M8N gps, Arduino Nano, and SD card reader

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Component%20Assembly.jpg">


# Introduction
The goal for this project is a cheep and simple high frequence (10Hz) GPS datalogger that I can use during different activitis like motocrossing and mountain biking. I based it on Arduino Nano with U-blox M8N GPS, microSD card module, and a small 2s(7.4V) lithium battrey.
I wanted the data to be saved in a way that it could be imported to "DASHWARE"  http://www.dashware.net/ . DASHWARE is a free software that let you overlay video with data like speed, laptime, distance, map, etc. collected form a GPS but also other logged data like heartrate etc.

I searched the webb for a good M8N gps parser library and struggled to find one that could read the UBX-NAV-PVT protocol. I tried iforce2d's "10Hz U-blox binary GPS data in 66 lines of code (arduino)" https://youtu.be/TwhCX0c8Xe0  on youtube that did some of what I wanted but I could not modifie it for the PVT protocol. I came across a few more libaries and sattled for code shared by Jordi Muñoz and Jose Julio, DIYDrones.com. I made a few changes to adopt to the PVT protocol and it worked really well.

# Functions
Two LED's give feedback on SD card and GPS status.
A push button starts and stopps the data logging and it's saved to a new file for each log.
The GPS sends only the UBX-NAV-PVT protocol 10 times per second (10Hz).
The Arduino Nano parse  recieved GPS data and save it to two log files on the microSD card. One ".txt" file and one ".csv" file. I use the ".csv" for Dashware.

All info from the PVT protocol could be saved but I choosed some and formed the output to my liking.

Sample ".txt" file

Log saved by ArduinoLogger
Time, Date, Clock, Latitude, Longitude, Speed, Altitude, Number_of_Satelites, Fix
502.0, 12-16-2016, 8:21.54, 33.1941285, -117.2643490, 27.75, 95.48, 19, 3
502.1, 12-16-2016, 8:21.54, 33.1941316, -117.2643194, 27.80, 95.55, 19, 3
502.2, 12-16-2016, 8:21.54, 33.1941350, -117.2642899, 27.75, 95.62, 19, 3
502.3, 12-16-2016, 8:21.54, 33.1941379, -117.2642602, 27.80, 95.70, 18, 3
502.4, 12-16-2016, 8:21.54, 33.1941407, -117.2642306, 27.81, 95.76, 18, 3
502.5, 12-16-2016, 8:21.55, 33.1941437, -117.2642011, 27.70, 95.85, 18, 3
502.6, 12-16-2016, 8:21.55, 33.1941465, -117.2641715, 27.78, 95.88, 18, 3
502.7, 12-16-2016, 8:21.55, 33.1941493, -117.2641420, 27.67, 96.00, 18, 3
502.8, 12-16-2016, 8:21.55, 33.1941519, -117.2641123, 27.78, 96.04, 18, 3

Sample ".csv" file
ARDUINO_Time, Latitude, Longitude, Speed
548.0, 33.1949041, -117.2511381, 27.62
548.1, 33.1949031, -117.2511084, 27.67
548.2, 33.1949022, -117.2510786, 27.71
548.3, 33.1949005, -117.2510488, 27.80
548.4, 33.1948993, -117.2510192, 27.67
548.5, 33.1948979, -117.2509894, 27.84
548.6, 33.1948963, -117.2509596, 27.89
548.7, 33.1948947, -117.2509300, 27.74
548.8, 33.1948930, -117.2509003, 27.77


# New Hardware (In work)
I have some new hardware/layout. More descriptions and pictures coming soon. I'm currently designing a new enclosure to 3D print.

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Component%20Assembly.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Circuite%20Board%20Components.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Circuite%20Board%20Traces.jpg">

# Old Hardware
GPS M8N $30 http://www.readytoflyquads.com/ublox-m8n-gps-module-no-mounting-backplane  
Arduino Nano $5.50 eBay  
microSD card module $3 eBay

Neo Ublox M8N
Website https://www.u-blox.com/en/product/neo-m8-series  
Protocoll sheet https://www.u-blox.com/sites/default/files/products/documents/u-bloxM8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf 

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/GPS%20Logger%20Assembly.jpg">


