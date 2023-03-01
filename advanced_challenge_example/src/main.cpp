#include <Arduino.h>
#include <Wire.h>
#include <LPS.h>
#include <LIS3MDL.h>
#include <LSM6.h>
#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Servo.h>

#define RGB_LED_PIN D5
#define IR_RECEIVER_PIN D4
#define SERVO_PIN D3
#define I2C_SCL_PIN D1
#define I2C_SDA_PIN D2
#define GYRO_ADDRESS 0x6B
#define MAG_ADDRESS 0x1E
#define BARO_ADDRESS 0x5D
#define PHOTORESISTOR_PIN A0

#define BUTTON_CHMINUS 69
#define BUTTON_CHPLUS 71
#define BUTTON_CH 70
#define BUTTON_PREV 68
#define BUTTON_NEXT 64
#define BUTTON_PLAY 67
#define BUTTON_VOLDOWN 7
#define BUTTON_VOLUP 21
#define BUTTON_EQ 9
#define BUTTON_0 22
#define BUTTON_100 25
#define BUTTON_200 13
#define BUTTON_1 12
#define BUTTON_2 24
#define BUTTON_3 94
#define BUTTON_4 8
#define BUTTON_5 28
#define BUTTON_6 90
#define BUTTON_7 66
#define BUTTON_8 82
#define BUTTON_9 74

LPS baro;
LIS3MDL mag;
LSM6 imu;
Adafruit_NeoPixel led = Adafruit_NeoPixel(60, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(IR_RECEIVER_PIN);
Servo servo;
decode_results results;

float pressure_abs = 0;
float water_depth = 0;
const float gravity =  9.80665f;

char mag_report[80];
char imu_report[80];
uint32_t cur_ir_command = 0;

LIS3MDL::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

void setup() {
  Serial.begin(9600);
  led.begin();
  irrecv.enableIRIn();
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  Wire.begin();
  servo.attach(SERVO_PIN);
  delay(500);

  // led.setBrightness(255);
  // led.setPixelColor(0, 0xFFFFFF);
  // led.show();

  // if (!imu.init())
  // {
  //   Serial.println("Failed to detect and initialize IMU!");
  //   while (1);
  // }
  // if (!baro.init())
  // {
  //   Serial.println("Failed to detect and initialize Barometer!");
  //   while (1);
  // }
  // if (!mag.init())
  // {
  //   Serial.println("Failed to detect and initialize Magnetometer!");
  //   while (1);
  // }

  // mag.enableDefault();
  // baro.enableDefault();
  // imu.enableDefault();
}

void loop() {
  mag.read();
  imu.read();
  pressure_abs = baro.readPressureMillibars();
  water_depth = 

  // running_min.x = min(running_min.x, mag.m.x);
  // running_min.y = min(running_min.y, mag.m.y);
  // running_min.z = min(running_min.z, mag.m.z);

  // running_max.x = max(running_max.x, mag.m.x);
  // running_max.y = max(running_max.y, mag.m.y);
  // running_max.z = max(running_max.z, mag.m.z);

  // snprintf(mag_report, sizeof(mag_report), "min: {%+6d, %+6d, %+6d}   max: {%+6d, %+6d, %+6d}",
  //   running_min.x, running_min.y, running_min.z,
  //   running_max.x, running_max.y, running_max.z);
  // Serial.print("MAG: ");
  // Serial.println(mag_report);

  // float pressure = baro.readPressureMillibars();
  // float altitude = baro.pressureToAltitudeMeters(pressure);
  // Serial.print(" || BARO: ");
  // Serial.println(altitude);

  // imu.read();
    
  // snprintf(imu_report, sizeof(imu_report), "A: %6d %6d %6d    G: %6d %6d %6d",
  //   imu.a.x, imu.a.y, imu.a.z,
  //   imu.g.x, imu.g.y, imu.g.z);
  // Serial.print(" || IMU: ");
  // Serial.println(imu_report);
  if(irrecv.decode(&results)){
    switch(results.command){
      case BUTTON_VOLDOWN:
        cur_ir_command = BUTTON_VOLDOWN;
        break;
      case BUTTON_VOLUP:
        cur_ir_command = BUTTON_VOLUP;
        break;
      case 0:
        break;
      default:
        cur_ir_command = 0;
        break;
    }
    switch(cur_ir_command){
      case BUTTON_VOLDOWN:
        servo.writeMicroseconds(1000);
        break;
      case BUTTON_VOLUP:
        servo.writeMicroseconds(2000);
        break;
      default:
        servo.writeMicroseconds(1500);
        break;
    }
    irrecv.resume();
  }
  delay(100);
}