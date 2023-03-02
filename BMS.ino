#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int BATTERY_PIN = A0;
const int BATTERY_MAX = 1023; // 10-bit ADC resolution
const float BATTERY_VOLTAGE_DIVIDER = 2.0; // R1 = 10K, R2 = 10K

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  int batteryReading = analogRead(BATTERY_PIN);
  float batteryVoltage = (batteryReading / (float)BATTERY_MAX) * BATTERY_VOLTAGE_DIVIDER * 3.3;
  display.clearDisplay();
  drawBars(0, 0, "Heart Rate", beatsPerMinute);
  drawBars(0, 16, "Blood Oxygen", bloodOxygen);
  drawBars(0, 32, "Battery Voltage", batteryVoltage);
  display.display();
  delay(1000);
}

void drawBars(int x, int y, String label, float value) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print(label);
  display.setCursor(70, y);
  display.print(value, 1);
  display.drawRect(0, y+8, SCREEN_WIDTH-1, 7, WHITE);
  int barWidth = map(value, 0, 5, 0, SCREEN_WIDTH-2);
  display.fillRect(1, y+9, barWidth, 5, WHITE);
}
