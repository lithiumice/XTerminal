#include "HAL.h"
#include <Wire.h>

// float gvar.bmp_pressure;
// float gvar.bmp_altitude;


#if defined(USE_BMP280)
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;
float bmp_temp;


void bmp_get()
{
    gvar.bmp_pressure = bmp.readPressure()/1000;
    // gvar.bmp_pressure = 0;
    gvar.bmp_altitude = bmp.readAltitude(1013.25);
    bmp_temp = bmp.readTemperature();

    Serial.print(F("Temperature = "));
    Serial.print(bmp_temp);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(gvar.bmp_pressure);
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(gvar.bmp_altitude); /* Adjusted to local forecast! */
    Serial.println(" m");
}
#endif

#if defined(USE_MAX30102)
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

float beatsPerMinute;
float beatAvg;
long irValue;
long redValue;
long greenValue;

MAX30105 particleSensor;
uint32_t irBuffer[100];   // infrared LED sensor data
uint32_t redBuffer[100];  // red LED sensor data
long samplesTaken = 0;    // Counter for calculating the Hz or read rate
long unblockedValue;      // Average IR at power up
long startTime;           // Used to calculate measurement rate
int32_t bufferLength;     // data length
int32_t spo2;             // SPO2 value
int8_t validSPO2;         // indicator to show if the SPO2 calculation is valid
int32_t heartRate;        // heart rate value
int8_t validHeartRate;    // indicator to show if the heart rate calculation is valid
const byte RATE_SIZE = 5; // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];    // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;

void spo_init()
{

    byte ledBrightness = 60; // Options: 0=Off to 255=50mA
    byte sampleAverage = 4;  // Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2;        // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100;   // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411;    // Options: 69, 118, 215, 411
    int adcRange = 4096;     // Options: 2048, 4096, 8192, 16384

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

    bufferLength = 100; // buffer length of 100 stores 4 seconds of samples running at 25sps

    // read the first 100 samples, and determine the signal range
    for (byte i = 0; i < bufferLength; i++)
    {
        while (particleSensor.available() == false) // do we have new data?
            particleSensor.check();                 // Check the sensor for new data

        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample(); // We're finished with this sample so move to next sample

        Serial.print(F("red="));
        Serial.print(redBuffer[i], DEC);
        Serial.print(F(", ir="));
        Serial.println(irBuffer[i], DEC);
    }

    // calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
}

void spo_get()
{

    // Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
    while (1)
    {
        // dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
        for (byte i = 25; i < 100; i++)
        {
            redBuffer[i - 25] = redBuffer[i];
            irBuffer[i - 25] = irBuffer[i];
        }

        // take 25 sets of samples before calculating the heart rate.
        for (byte i = 75; i < 100; i++)
        {
            while (particleSensor.available() == false) // do we have new data?
                particleSensor.check();                 // Check the sensor for new data

            // digitalWrite(readLED, !digitalRead(readLED)); // Blink onboard LED with every data read

            redBuffer[i] = particleSensor.getRed();
            irBuffer[i] = particleSensor.getIR();
            particleSensor.nextSample(); // We're finished with this sample so move to next sample

            // send samples and calculation result to terminal program through UART
            Serial.print(F("red="));
            Serial.print(redBuffer[i], DEC);
            Serial.print(F(", ir="));
            Serial.print(irBuffer[i], DEC);

            Serial.print(F(", HR="));
            Serial.print(heartRate, DEC);

            Serial.print(F(", HRvalid="));
            Serial.print(validHeartRate, DEC);

            Serial.print(F(", SPO2="));
            Serial.print(spo2, DEC);

            Serial.print(F(", SPO2Valid="));
            Serial.println(validSPO2, DEC);
        }

        // After gathering 25 new samples recalculate HR and SP02
        maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    }
}

void temp_get()
{
    float temperature = particleSensor.readTemperature();

    Serial.print("temperatureC=");
    Serial.print(temperature, 4);
}

void hr_init()
{
    particleSensor.setup();                    // Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0);  // Turn off Green LED
}

void hr_get()
{
    irValue = particleSensor.getIR();
    redValue = particleSensor.getRed();
    // greenValue = particleSensor.getGreen();

    if (checkForBeat(irValue) == true)
    {
        // We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 35)
        {
            rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
            rateSpot %= RATE_SIZE;                    // Wrap variable

            // Take average of readings
            beatAvg = 0;
            for (byte x = 0; x < RATE_SIZE; x++)
                beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
        }
    }

    // Serial.print("IR=");
    // Serial.print(irValue);
    // Serial.print(", BPM=");
    // Serial.print(beatsPerMinute);
    // Serial.print(", Avg BPM=");
    // Serial.print(beatAvg);

    // // if (irValue < 50000)
    // //     Serial.print(" No finger?");

    // Serial.println();
}
#endif

void HAL::sensors_init()
{
#if defined(USE_MAX30102)
    if (!particleSensor.begin(Wire1, I2C_SPEED_FAST))
    {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
    }

    hr_init();
#endif

#if defined(USE_BMP280)
    bmp=Adafruit_BMP280(&Wire1);
    if (!bmp.begin(BMP280_ADDRESS_ALT,BMP280_CHIPID))
    {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                         "try a different address!"));
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
#endif
}

void HAL::sensors_max30102_data()
{
#if defined(USE_MAX30102)
    hr_get();
#endif

#if defined(USE_BMP280)
    bmp_get();
#endif
}
