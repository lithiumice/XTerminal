/**************************************************/
/* ICM20X Accelerometer Digital Low Pass Filter Demo
This example demonstrates the effect of changing the filter cutoff frequency
for an ICM20X accelerometer's Digital Low Pass Filter

A cutoff frequency is set in `setup()` and you should experiment with changing
it and observing the effect on the signal.
The effect of changing the accelerometer's cutoff frequency is
the most apparent when using the Serial Plotter.
/**************************************************/

#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
Adafruit_ICM20948 icm;

// uncomment to use the ICM20649
//#include <Adafruit_ICM20649.h>
// Adafruit_ICM20649 icm

Adafruit_Sensor *accel;

#define ICM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define ICM_SCK 13
#define ICM_MISO 12
#define ICM_MOSI 11

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  if (!icm.begin_I2C()) {
    // if (!icm.begin_SPI(ICM_CS)) {
    // if (!icm.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI)) {
    Serial.println("Failed to find ICM20X chip");
    while (1) {
      delay(10);
    }
  }

  /* Available cutoff frequencies:
    ICM20X_ACCEL_FREQ_246_0_HZ
    ICM20X_ACCEL_FREQ_111_4_HZ
    ICM20X_ACCEL_FREQ_50_4_HZ
    ICM20X_ACCEL_FREQ_23_9_HZ
    ICM20X_ACCEL_FREQ_11_5_HZ
    ICM20X_ACCEL_FREQ_5_7_HZ
    ICM20X_ACCEL_FREQ_473_HZ
  */
  icm.enableAccelDLPF(true, ICM20X_ACCEL_FREQ_5_7_HZ);

  // Get an Adafruit_Sensor compatible object for the ICM20X's accelerometer
  accel = icm.getAccelerometerSensor();
}

void loop() {
  /* Get a new normalized sensor event */
  sensors_event_t a;

  /* fill the event with the most recent data */
  accel->getEvent(&a);

  Serial.print(a.acceleration.x);
  Serial.print(","); Serial.print(a.acceleration.y);
  Serial.print(","); Serial.print(a.acceleration.z);

  Serial.println();

  delayMicroseconds((float)10/1000);

}
