# esp8266-temp
ESP8266 temperature sensor

## Introduction
This example demonstrates the use of an ESP8266 ESP-12F D1 board
connected to a DS18B20 temperature sensor. It runs a simple program that
reads temperature data and publishes the readings via MQTT.  To save
power the program wakes the ESP8266 from deep sleep mode every 15
minutes to perform measurement and report.

## Requirements
Install Arduino IDE. Follow the instructions **Installing with Boards Manager**
from `https://github.com/esp8266/Arduino`

## Hardware

* ESP8266 module after I soldered rails to.
  * ![ESP8266 module](/assets/images/esp8266-12.jpg)
* Development board that came with the module
  * ![Development board](/assets/images/devboard.jpg)
* 2 AA battery carrier
  * ![Battery carrier](/assets/images/carrier.jpg)
* I bought a D1 mini board, which already had an ESP8266 module. I removed its module and soldered on pins that could accept my module.
  * ![Programmer](/assets/images/programmer.jpg)
* The assembled parts
  * ![Assembled parts](/assets/images/assembled.jpg)

## Wiring

I adapted the instructions from <http://technicalstuffhopefullyuseful.blogspot.com/2016/12/connecting-esp8266-12-to-ds1820.html>

## Installation
In the IDE install these libraries via *Tools->Manage Libraries*
* OneWire
* DallasTemperature
* PubSubClient

Create project directory
```
mkdir -p ~/Arduino/project/esp8266-temp
```

Copy `esp8266-temp.ino` into `~/Arduino/project/esp8266-temp`

## Compile
* Use *File->Open* to select the sketch `esp8266-temp.ino`
* Use *Sketch->Verify/Compile* to compile the sketch
* Use *Sketch->Upload* to upload the sketch
