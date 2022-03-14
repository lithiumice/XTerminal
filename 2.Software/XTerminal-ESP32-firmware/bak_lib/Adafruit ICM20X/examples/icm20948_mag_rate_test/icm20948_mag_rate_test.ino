/**************************************************/
/* ICM20948 Magnetometer Data Rate Demo
This example demonstrates the effect of changing the data
rate for the ICM20948's onboard AK09916 magnetometer.

In the main `loop`, the sketch will read the magnetometer
MEASUREMENTS_PER_RATE times and then switch to the second data rate.
It will measure and print MEASUREMENTS_PER_RATE times again before starting over

The effect of changing the magnetometer's data rate is
the most apparent when using the Serial Plotter. You should see the "resolution"
of the graphed measurements change as the sensor switches data rates
/**************************************************/
#include <Adafruit_ICM20948.h>
#include <Adafruit_ICM20X.h>

/* Available Data Rates:
  AK09916_MAG_DATARATE_10_HZ // updates at 10Hz
  AK09916_MAG_DATARATE_20_HZ // updates at 20Hz
  AK09916_MAG_DATARATE_50_HZ // updates at 50Hz
  AK09916_MAG_DATARATE_100_HZ // updates at 100Hz
  AK09916_MAG_DATARATE_SHUTDOWN // Stops measurement updates!
  AK09916_MAG_DATARATE_SINGLE // Takes a single measurement then switches to AK09916_MAG_DATARATE_SHUTDOWN
*/
#define MAG_DATARATE_A AK09916_MAG_DATARATE_10_HZ
#define MAG_DATARATE_B AK09916_MAG_DATARATE_100_HZ

#define MEASUREMENTS_PER_RATE 500

Adafruit_ICM20948 icm;
Adafruit_Sensor *icm_mag;

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
    Serial.println("Failed to find ICM20948 chip");
    while (1) {
      delay(10);
    }
  }
  // Get an Adafruit_Sensor compatible object for the ICM20948's magnetometer
  icm_mag = icm.getMagnetometerSensor();
}

void loop() {
  printNum(MEASUREMENTS_PER_RATE);
  icm.setMagDataRate(MAG_DATARATE_A);

  printNum(MEASUREMENTS_PER_RATE);
  icm.setMagDataRate(MAG_DATARATE_B);

}

void printNum(uint16_t num_prints){
    /* Get a new normalized sensor event */
    sensors_event_t mag;
  for (uint16_t i=0; i<num_prints; i++){
    /* fill the event with the most recent data */
    icm_mag->getEvent(&mag);

    Serial.print(mag.magnetic.x);
    Serial.print(","); Serial.print(mag.magnetic.y);
    Serial.print(","); Serial.print(mag.magnetic.z);

    Serial.println();

    delayMicroseconds((float)10/1000);
  }
}
