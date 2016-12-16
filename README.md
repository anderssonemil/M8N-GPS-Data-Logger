# M8N-GPS-Data-Logger
GPS data logger uisng U-blox M8N gps, Arduino Nano, and SD card reader

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Component%20Assembly.jpg">


# Introduction
The goal for this project is a cheap and simple high frequency (10Hz) GPS data logger that I can use during different activities like motor crossing, mountain biking, car racing and similar activities. I based it on Arduino Nano with U-blox M8N GPS, microSD card module, and a small 2s(7.4V) lithium battery.
I wanted the data to be saved in a way that it could be imported to "DASHWARE"  http://www.dashware.net/ . DASHWARE is a free software that let you overlay video with data like speed, lap time, distance, map, etc. collected form a GPS but also other logged data like heartrate etc.

I searched the web for a good M8N GPS parser library and struggled to find one that could read the UBX-NAV-PVT protocol. I tried iforce2d's "10Hz U-Blox binary GPS data in 66 lines of code (arduino)" https://youtu.be/TwhCX0c8Xe0  on YouTube that did some of what I wanted but I could not modified it for the PVT protocol. I came across a few more libraries and settled for code shared by Jordi Muñoz and Jose Julio, DIYDrones.com. I made a few changes to adopt to the PVT protocol and it worked really well.

I used CAD Soft's free version of EAGLE for the PCB layout https://cadsoft.io/

# Functions
Two LED's give feedback on SD card and GPS status.
A push button starts and stops the data logging and it's saved to a new file for each log.
The GPS sends only the UBX-NAV-PVT protocol 10 times per second (10Hz).
The Arduino Nano parse received GPS data and save it to two log files on the microSD card. One ".txt" file and one ".csv" file. I use the ".csv" for Dashware.

All info from the PVT protocol could be saved but I choose some and formed the output to my liking.

### Sample ".txt" file

|Time|Date|Clock|Latitude|Longitude|Speed|Altitude|Number_of_Satelites|Fix|
|---|---|---|---|---|---|---|---|---|
|XXX.X|XX-X-XXXX|X:XX:XX|XX.XXXXXXX|-XXX.XXXXXXX|X.XX|XX.X|X|X|
|502.0|12-16-2016|8:21.54|33.1941285|117.2643490|27.75|95.48|19|3|
|502.1|12-16-2016|8:21.54|33.1941316|-117.2643194|27.80|95.55|19|3|
|502.2|12-16-2016|8:21.54|33.1941350|-117.2642899|27.75|95.62|19|3|

### Sample ".csv" file

|ARDUINO_Time|Latitude|Longitude|Speed|
|---|---|---|---|
|548.0|33.1949041|-117.2511381|27.62|
|548.1|33.1949031|-117.2511084|27.67|
|548.2|33.1949022|-117.2510786|27.71|


# Second logger(In work)
Now that I have a 3D printer I decided to go for a cleaner layout with a circuit board eliminating all cables but the once for the GPS. I'm currently designing a new enclosure and I'll add pictures when done.

GPS M8N $20 http://www.banggood.com/Ublox-NEO-M8N-Flight-Controller-GPS-with-Protective-Shell-for-PIX-PX4-Pixhawk-p-1005394.html
Arduino Nano $5.50 eBay  
microSD card module $3 eBay

Neo Ublox M8N
Website https://www.u-blox.com/en/product/neo-m8-series  
Protocoll sheet https://www.u-blox.com/sites/default/files/products/documents/u-bloxM8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf 



<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Component%20Assembly.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Circuite%20Board%20Components.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Circuite%20Board%20Traces.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/Schematic.bmp">

# First Logger
I used this GPS for my first logger M8N $30 http://www.readytoflyquads.com/ublox-m8n-gps-module-no-mounting-backplane  

The first logger had a lot of cabels and hard to handle in and out it's case.

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/GPS%20Logger%20Box.jpg">

<img alt="GPS Logger Box" src="https://github.com/anderssonemil/M8N-GPS-Data-Logger/blob/master/GPS%20Logger%20Assembly.jpg">