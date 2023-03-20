//Data Over Air>>Connectivity
#include <SoftwareSerial.h>
#include <WiFi.h>

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* host = "your_server_address";
const int port = 80;

SoftwareSerial btSerial(2, 3); // RX, TX for Bluetooth module
WiFiClient client;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int heartRate = getHeartRate();
  int bloodOxygen = getBloodOxygen();
  float batteryVoltage = getBatteryVoltage();
  
  // Send data to mobile app via Bluetooth
  btSerial.print("HR:");
  btSerial.print(heartRate);
  btSerial.print(" O2:");
  btSerial.print(bloodOxygen);
  btSerial.print(" BV:");
  btSerial.println(batteryVoltage);
  
  // Send data to server via WiFi
  if (client.connect(host, port)) {
    String data = "HR=" + String(heartRate) + "&O2=" + String(bloodOxygen) + "&BV=" + String(batteryVoltage);
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    client.println();
    Serial.println("Data sent to server");
  } else {
    Serial.println("Connection to server failed");
  }
  delay(5000); // wait for 5 seconds before sending data again
}

int getHeartRate() {
  // get heart rate from sensor
}

int getBloodOxygen() {
  // get blood oxygen from sensor
}

float getBatteryVoltage() {
  // get battery voltage from ADC
}
