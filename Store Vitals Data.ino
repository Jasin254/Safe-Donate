#include <SD.h>
#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

#define FILE_NAME "vital_sign_data.txt"

MAX30105 particleSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

File dataFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  if (!SD.begin(10)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
  particleSensor.begin(Wire, I2C_SPEED_FAST);
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

void loop() {
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
      writeDataToFile(beatAvg, particleSensor.getFIFO() & 0x3FF);
    }
  }
  delay(100);
}

void writeDataToFile(int heartRate, int bloodOxygen) {
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (dataFile) {
    dataFile.print("Heart Rate: ");
    dataFile.print(heartRate);
    dataFile.print(", ");
    dataFile.print("Blood Oxygen: ");
    dataFile.println(bloodOxygen);
    dataFile.close();
  } else {
    Serial.println("Error opening file!");
  }
}
