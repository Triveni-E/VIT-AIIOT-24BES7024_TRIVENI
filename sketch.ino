#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("IIOT Position");
  display.println("Monitoring");
  display.display();

  delay(2000);
}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read MPU6050 values
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("ACCELEROMETER");

  display.print("AX:");
  display.println(ax);

  display.print("AY:");
  display.println(ay);

  display.print("AZ:");
  display.println(az);

  display.println();

  display.println("GYROSCOPE");

  display.print("GX:");
  display.println(gx);

  display.print("GY:");
  display.println(gy);

  display.print("GZ:");
  display.println(gz);

  display.display();

  // Print to Serial Monitor also
  Serial.print("AX=");
  Serial.print(ax);
  Serial.print(" AY=");
  Serial.print(ay);
  Serial.print(" AZ=");
  Serial.print(az);

  Serial.print(" GX=");
  Serial.print(gx);
  Serial.print(" GY=");
  Serial.print(gy);
  Serial.print(" GZ=");
  Serial.println(gz);

  delay(500);
}
