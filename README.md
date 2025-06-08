# esp8266-temp

## Introduction
This example demonstrates the use of an ESP8266 ESP-12F D1 board
connected to a DS18B20 temperature sensor. It runs a simple program that
reads temperature data and publishes the readings via MQTT.

## Requirements
Install Arduino IDE. Follow the instructions **Installing with Boards Manager**
from `https://github.com/esp8266/Arduino`

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
