int sensorPin = 13;
int sensorValue = 0;

// better idea to get min/max values would be to test 
// the sensor in dry soil and then in soaking wet soil
// sensor placed in air
int sensorMin = 3600;
// sensor submerged in water
int sensorMax = 1840;

/*
 * sensor_calibration.ino
 * 
 * This simple program will allow the user to find  min / max values
 * used for calibration. From values printed in serial monitor user 
 * can pick values that will represent 0% and 100%. Moisture sensor 
 * should be tested in dry and wet soil to ensure best calibration.
 */
void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);

  // "warming up" moisture sensor
  sensorValue = analogRead(sensorPin);
  delay(500);
}

void loop() {
  // reading correct value from the sensor
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  delay(100);
}
