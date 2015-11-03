# M8N-GPS-Data-Logger
GPS data logger uisng U-blox M8N gps, Arduino Nano, and SD card reader

<img alt="GPS Logger Box" src="https://raw.githubusercontent.com/anderssonemil/M8N-GPS-Data-Logger/master/GPS%20Logger%20Box.jpg">


# Introduction
The goal for this project is a cheep and simple high frequence (10Hz) GPS datalogger that I can use during different activitis like motocrossing and mountain biking. I based it on Arduino Nano with U-blox M8N GPS, microSD card module, and a small 2s(7.4V) lithium battrey.
I wanted the data to be saved in a way that it could be imported to "DASHWARE"  http://www.dashware.net/ . DASHWARE is a free software that let you overlay video with data like speed, laptime, distance, map, etc. collected form a GPS but also other logged data like heartrate etc.

I searched the webb for a good M8N gps parser library and struggled to find one that could read the UBX-NAV-PVT protocol. I tried iforce2d's "10Hz U-blox binary GPS data in 66 lines of code (arduino)" https://youtu.be/TwhCX0c8Xe0  on youtube that did some of what I wanted but I could not  modifie it for the PVT protocol. I came across a few more libaries and sattled for code shared by Jordi Muñoz and Jose Julio, DIYDrones.com. I made a few changes to adopt to the PVT protocol and it worked really well.

# Functions
Two LED's give feedback on SD card and GPS status.
A push button starts and stopps the data logging and it's saved to a new file for each log.
The GPS sends only the UBX-NAV-PVT protocol 10 times per second (10Hz).
The Arduino Nano parse  recieved GPS data and save it to a log file on the microSD card.

All info from the PVT protocol could be saved but I choosed some and formed the output to look like this.

|Time|Date|Clock|Latitude|Longitutde|Speed|Altitude|Numb of Sats|Fix|
|---|---|---|---|---|---|---|---|---|
|XXX.X|XX-X-XXXX|X:XX:XX|XX.XXXXXXX|-XXX.XXXXXXX|X.XX|XX.X|X|X|
|528.4|11-2-2015|8:59.39|33.1946182|-117.2495269|4.15|77.82|4|3|
|528.5|11-2-2015|8:59.39|33.1946258|-117.2495269|4.14|77.32|4|3|



# Hardware
GPS M8N $30 http://www.readytoflyquads.com/ublox-m8n-gps-module-no-mounting-backplane  
Arduino Nano $5.50 eBay  
microSD card module $3 eBay

Neo Ublox M8N
Website https://www.u-blox.com/en/product/neo-m8-series  
Protocoll sheet https://www.u-blox.com/sites/default/files/products/documents/u-bloxM8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf 

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/GPS%20Logger%20Assembly.jpg">
