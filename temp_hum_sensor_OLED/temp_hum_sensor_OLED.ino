#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define HEIGHT 128
#define WIDTH 64

#define OLED_PIN_RESET 4

Adafruit_SSD1306 oled(HEIGHT,WIDTH, &Wire);
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC,0X3C); 
}

void loop() {
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Temp");

  oled.setCursor(10,0);
  oled.print("Humidity");

  oled.display();
}
