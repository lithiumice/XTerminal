// Once you import this library into an app on the web based IDE, modify the code to look something like the following.
// This code is a heavily modified version of the MPU6050_raw.ino example found elsewhere in this repo.
// This code has been tested against the MPU-9150 breakout board from Sparkfun.

// This #include statement was automatically added by the Particle IDE.
#include "MPU6050.h"

int ledPin = D7;

// MPU variables:
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;


bool ledState = false;
void toggleLed() {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

void setup() {
    pinMode(ledPin, OUTPUT);

    Wire.begin();
    Serial.begin(9600);

    // The following line will wait until you connect to the Spark.io using serial and hit enter. This gives
    // you enough time to start capturing the data when you are ready instead of just spewing data to the UART.
    //
    // So, open a serial connection using something like:
    // screen /dev/tty.usbmodem1411 9600
    while(!Serial.available()) SPARK_WLAN_Loop();
    
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // Cerify the connection:
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    Serial.print("a/g:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);
    
    toggleLed();
    
}
