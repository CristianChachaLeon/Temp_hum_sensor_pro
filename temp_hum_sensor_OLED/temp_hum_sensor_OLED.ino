#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>

#define DEBUG

#define HEIGHT 128
#define WIDTH 64

#define OLED_PIN_RESET 4

Adafruit_SSD1306 oled(HEIGHT, WIDTH, &Wire);

Adafruit_BME280 bme;
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();
void setup() {
  
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("BME280 Sensor event test"));
  #endif
  if (!bme.begin(0x76)) {
    #ifdef DEBUG
    Serial.println(F("No se ha encontrado el sensor BME280"));
    #endif
    while (1) delay(10);
  }

  bme_temp->printSensorDetails();
  bme_humidity->printSensorDetails();
}
void loop() {
  sensors_event_t temp_event, humidity_event;
  bme_temp->getEvent(&temp_event);
  bme_humidity->getEvent(&humidity_event);
  
  #ifdef DEBUG
  Serial.print(F("Temperatura = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Humedad = "));
  Serial.print(humidity_event.relative_humidity);
  Serial.println(" %");
  Serial.println();
  #endif
  
  show_temp_and_hum_in_oled(&oled, temp_event.temperature, humidity_event.relative_humidity);
  delay(1000);
}

void show_temp_and_hum_in_oled(Adafruit_SSD1306 *oled, float temp, float hum) {
#define X_POS_TEMP 10
#define Y_POS_TEMP 5
#define X_POS_HUM 40
#define Y_POS_HUM 40
  oled->clearDisplay();
  oled->setTextColor(WHITE);
  oled->setTextSize(3);
  oled->setCursor(X_POS_TEMP , Y_POS_TEMP );
  oled->print(temp, 1);
  oled->setTextSize(2);
  oled->setCursor(X_POS_TEMP + 75, Y_POS_TEMP + 10);
  oled->print("C");
  oled->drawLine(10, 32, 118, 32, WHITE);

  oled->setCursor(X_POS_HUM, Y_POS_HUM);
  oled->setTextSize(3);
  oled->print(hum, 0);

  oled->setCursor(X_POS_HUM + 40, Y_POS_HUM + 5);
  oled->setTextSize(2);
  oled->print("%");
  oled->display();
}
