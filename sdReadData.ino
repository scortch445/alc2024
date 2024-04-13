//read sd card
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

File file;

void setup() {
  Serial.begin(115200);
  Serial.println("program start");
  if (!(SD.begin(4))){
    Serial.println("SD gone bye bye");
  }
  Serial.println("SD maybe working but honestly who knows");
  file = SD.open("testlog.txt", FILE_WRITE);
  file.close();
  file = SD.open("testlog.txt");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void loop() {
  
}
