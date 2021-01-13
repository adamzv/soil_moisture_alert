# ESP32 Soil moisture alert system
 ESP32 with capacitive soil moisture sensor sends SMS using Twilio when soil moisture dips below given treshhold. Capacitive sensor is a better pick than moisture sensors with exposed plates because those will corrode after some time in moist environment. That can lead to contamination of soil. However, because of manufacturing, capacitive soil moisture sensors often have cut edges that would expose copper plate, so these edges should be coated to prevent corrosion. Even simpler solution is to put capacitive sensor in a small sealed bag. In this case sensor is easily waterproofed and would still work without problems.  

## What it does
 ESP32 is using deep-sleep to save a lot of energy when it is not reading data from sensor. When the ESP32 wakes up from deep-sleep, it reads actual analog value from sensor, which is then mapped to range of 0-100. If a sensor value is less than a specified range, the device will try to connect to Wi-Fi and if the connection was established, then it will try to send API request to Twilio API. 

## How we built it
 This project was built with a ESP32 development board, a capacitive moisture sensor (v2.0) and an Arduino IDE. Sending requests to Twillio API was handled by ![Twilio ESP32 library](https://github.com/ademuri/twilio-esp32-client).

## What's next for Soil moisture monitoring system with Twilio API
 This was a project that was sitting in my backlog for a quite some time, so I am happy that I was able to finally build it. The next step would be to make it even more power efficient, so that it could run on battery for a long time.
