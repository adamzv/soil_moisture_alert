// Used client library for Twilio API
// https://github.com/ademuri/twilio-esp32-client
#include "twilio.hpp"

#define uS_TO_S_FACTOR 1000000   // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  1800      // Time ESP32 will go to sleep (in seconds)

static const char *ssid = "";
static const char *password = "";

static const char *account_sid = "";
static const char *auth_token = "";

static const char *from_number = "+";
static const char *to_number = "+";

int sensorPin = 13;
int sensorValue = 0;

// better idea to get min/max values would be to test 
// the sensor in dry soil and then in soaking wet soil
// sensor placed in air
int sensorMin = 3600;
// sensor submerged in water
int sensorMax = 1840;

Twilio *twilio;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  // "warming up" moisture sensor
  sensorValue = analogRead(sensorPin);
  delay(500);
  // reading correct value from the sensor
  sensorValue = analogRead(sensorPin);
  // mapping analog value to range <0;100>
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 100);
  sensorValue = constrain(sensorValue, 0, 100);
  
  Serial.print("Soil moisture: ");
  Serial.println(sensorValue);

  // formatted SMS message with moisture level
  char message[80];
  sprintf(message, "My soil is drying out, please water me! Current soil moisture is at %d%%.", sensorValue);
  String response;
  if (sensorValue < 30) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.println("\nConnected!");
  
    twilio = new Twilio(account_sid, auth_token);
    delay(1000);

    bool request = twilio->send_message(to_number, from_number, message, response);
    if (request) {
      Serial.println("Sent message successfully!");
    } else {
      Serial.println(response);
    }
  }

  delay(100);
  esp_deep_sleep_start();
}

void loop() {
  // loop is not necessary
}
