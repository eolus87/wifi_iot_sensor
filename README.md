# wifi_iot_sensor
## Introduction
Repo to hold the steps to develop a WiFi IoT sensor based on ESP8266 (NodeMCU) microcontroller to measure different 
magnitudes like temperature, humidity, light, air quality ... and display the measure in a http server.

## Coding steps
1) Download Arduino IDE from [official website](https://www.arduino.cc/en/software).
2) Install ESP8266 Board in Arduino IDE following [these steps](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/).
3) Get the code for a Simple HTTP Web Server from [here](https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/)
4) Adapt (if required) the code depending on the sensor:
- [DHT11/DHT22](https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/)
- [TMP37F/Photoresistor (Analog Input)](https://mounishkokkula.wordpress.com/low-light-detecto-esp8266-nodemcu/)
- [DS18B20](https://randomnerdtutorials.com/esp8266-ds18b20-temperature-sensor-web-server-with-arduino-ide/)

NOTE: So far this repo uses DS18B20 and Photoresistor


5) Modify the initial section according to:
- ssid -> by the name of your WiFi network (it must be the 2.4Ghz)
- password -> include the password for your network
- oneWireBus -> Pin where you have connected the DS18B20 sensor (in case you are using one)
- Temperature calibration:
  - icing_measure -> Temperature measured by the sensor in water with ice
  - icing_reference -> Temperature reference when in water with ice (0 degrees)
  - boiling_measure -> Temperature measured by the sensor in boiling water
  - boiling_reference -> Temperature of boiling water (Check depending on altitude)
- installation_place -> Room/place of the house where the sensor will be installed. This will be 
the header of the http site.
6) Plug your ESP8266/NodeMCU using a micro USB cable to your computer.
7) Upload the sketch.
8) You can use the "Serial Monitor" to debug the application.

## Bill of Materials (per sensor):
- 1x[Plugs](https://www.amazon.co.uk/dp/B093HB26ZK)
- 1x[220V to 5V Mini Power Supply](https://www.amazon.co.uk/dp/B078Q2ZMPT)
- 1x[NodeMCU](https://www.amazon.co.uk/dp/B07Z68HYW1)
- 1x[DS18B20](https://www.amazon.co.uk/dp/B01LXQF9B5)
- 1x[Photoresistor](https://www.amazon.co.uk/Photoresistor-Resistor-Light-Dependent-Photoconductor-Sensitive/dp/B08QRRG4SN)
- 2x[10k Resistor](https://www.amazon.co.uk/250V-Axial-Lead-Carbon-Resistors/dp/B0087ZDSV8)
- Around 20cm of 220V cable
- Around 20cm of low voltage cable
- 1x3D Printed case - (This is WPI, at the moment but stay tuned!)

## 3D Printing case
This is WIP, it will be updated once I have designed and printed it and probably uploaded it to thingiverse/pinshape.

## Wiring
This is WIP as well. Stay tuned!