#include <SPI.h>
#include <SD.h>

File file;

void setup() {
  Serial.begin(115200);

  Serial.println("SD Test\n");
  //pinMode(11, OUTPUT);
  //pinMode(12, INPUT);

  //Serial.println("pins altered\n");

  if (!(SD.begin(4))) {  //Replace 0 with pin #11,12,13
    Serial.println("SD not found\n");
    return;
  }
  Serial.println("SD found\n");

  //create file
  Serial.println("Attempting file creation\n");
  file = SD.open("testlog.txt", FILE_WRITE);
  file.close();
  Serial.println("File created\n");
}

void loop() {
  
  if (SD.exists("testlog.txt")) {
    file = SD.open("testlog.txt", FILE_WRITE);
    Serial.println("File on SD found\n");
    if (file) {
      Serial.println("File on SDcan be manipulated");
      file = SD.open("testlog.txt", FILE_WRITE);
      file.println("Time: " + String(millis()));
      file.close();
    } else {
      Serial.println("Problem with file on SD");
    }
  } else {
    Serial.println("File on SD not found");
  }
  delay(1000);
}

