//SD writing code from Antony Cartwright, altered by Madeline Rotz
//Gyroscope code from basic_readings example, altered by Madeline Rotz
//Integration also by Madeline Rotz

#include <SPI.h>
#include <SD.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

File file;
Adafruit_MPU6050 mpu;

//int numTimes = 0;

void setup() {  
  Serial.begin(115200);
  //while (!(Serial)) delay(10); possibly needed
  Serial.println("SD, Nano, and Gyroscope Test\n");

  if (!(SD.begin(4))) {//Replace 0 with pin #
    Serial.println("SD not found\n");
  } 
  Serial.println("SD found\n");
  
  while (!(mpu.begin())) {
    Serial.println("Gyroscope not found\n");
    //delay(10) in while (1) ?
  }
  Serial.println("Gyroscope found\n");

  //create file
  Serial.println("Attempting file creation\n");
  file = SD.open("testlog.txt", FILE_WRITE);
  file.close();
  Serial.println("File created\n");
}

void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    file = SD.open("testlog.txt", FILE_WRITE);
    if (SD.exists("testlog.txt")) {
        Serial.println("File on SD found\n");
        if (file) {
          Serial.println("File on SD can be manipulated\n");
          
          file.println("Acceleration X: " + String(a.acceleration.x) + ", Y: " + 
            String(a.acceleration.y) + ", Z: " + String(a.acceleration.z) + "\n");
          file.println("Rotation X: " + String(g.gyro.x) + ", Y: " + String(g.gyro.y) + 
            ", Z: " + String(g.gyro.z) + "\n");
          file.println ("Temperature: " + String(temp.temperature) + "\n");

          file.close();
        }
        else {
          Serial.println("Problem with file on SD");
        }
      }
      else {
        Serial.println("File on SD not found");
      }
      delay(1000);
  


}
