#include "HAL/HAL.h"

//todo
#undef USE_IIC1
#undef USE_IIC2

void HAL::I2C_Scan(TwoWire *Wire)
{

    uint8_t error, address;
    int nDevices;

    Serial.println("I2C: device scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire->beginTransmission(address);
        error = Wire->endTransmission();

        if (error == 0)
        {
            Serial.print("I2C: device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println(" !");

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("I2C: unknow error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }

    Serial.printf("I2C: %d devices was found\r\n", nDevices);
}

void HAL::I2C_Init(bool startScan)
{
#ifdef USE_IIC1
    Wire.begin(CONFIG_IIC1_SDA_PIN, CONFIG_IIC1_SCL_PIN);
    HAL::I2C_Scan(&Wire);
#endif

#ifdef USE_IIC2
    Wire1.begin(CONFIG_IIC2_SDA_PIN, CONFIG_IIC2_SCL_PIN);
    HAL::I2C_Scan(&Wire1);
#endif
}
