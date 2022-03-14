#include "mbed.h"
#include "icm20602_i2c.h"
//Serial pc1(USBTX,USBRX); 
I2C  ICM20602_i2c(D14,D15); // I2C0_SDA, I2C0_SCL

// Acc Full Scale Range  +-2G 4G 8G 16G 
enum Ascale
{
    AFS_2G=0,  
    AFS_4G,
    AFS_8G,
    AFS_16G
};

// Gyro Full Scale Range +-250 500 1000 2000 Degrees per second
enum Gscale
{
    GFS_250DPS=0,   
    GFS_500DPS,
    GFS_1000DPS,
    GFS_2000DPS
};

// Scale resolutions per LSB for the sensors
float aRes, gRes; 
int Ascale = AFS_2G;
int Gscale = GFS_1000DPS;

void ICM20602_WriteByte(uint8_t ICM20602_reg, uint8_t ICM20602_data)
{
    char data_out[2];
    data_out[0]=ICM20602_reg;
    data_out[1]=ICM20602_data;
    ICM20602_i2c.write(ICM20602_slave_addr, data_out, 2, 0);
}

uint8_t ICM20602_ReadByte(uint8_t ICM20602_reg)
{
    char data_out[1], data_in[1];
    data_out[0] = ICM20602_reg;
    ICM20602_i2c.write(ICM20602_slave_addr, data_out, 1, 1);
    ICM20602_i2c.read(ICM20602_slave_addr, data_in, 1, 0);
    return (data_in[0]);
}

// Communication test: WHO_AM_I register reading 
void ICM20602::whoAmI()
{
    uint8_t whoAmI = ICM20602_ReadByte(ICM20602_WHO_AM_I);   // Should return 0x68
    pc.printf("I AM ICM20602: 0x%x \r\n",whoAmI);
    
    if(whoAmI==0x12)//0x68)
    {
        pc.printf("ICM20602 is online... \r\n");  
//        led2=1;
//        ledToggle(2);
    }
    else
    {
        pc.printf("Could not connect to ICM20602 \r\nCheck the connections... \r\n");  
//        toggler1.attach(&toggle_led1,0.1);     // toggles led1 every 100 ms
    }  
    
}

void ICM20602::init()
{
    ICM20602_i2c.frequency(400000);    
    ICM20602_WriteByte(ICM20602_PWR_MGMT_1, 0x00);    // CLK_SEL=0: internal 8MHz, TEMP_DIS=0, SLEEP=0 
    ICM20602_WriteByte(ICM20602_SMPLRT_DIV, 0x07);  // Gyro output sample rate = Gyro Output Rate/(1+SMPLRT_DIV)
    ICM20602_WriteByte(ICM20602_CONFIG, 0x01); //176Hz     // set TEMP_OUT_L, DLPF=3 (Fs=1KHz):0x03
//    ICM20602_WriteByte(ICM20602_GYRO_CONFIG, 0x00); // bit[4:3] 0=+-250d/s,1=+-500d/s,2=+-1000d/s,3=+-2000d/s :0x18
//    ICM20602_WriteByte(ICM20602_ACCEL_CONFIG, 0x00);// bit[4:3] 0=+-2g,1=+-4g,2=+-8g,3=+-16g, ACC_HPF=On (5Hz):0x01
    setAccRange(Ascale);
    setGyroRange(Gscale);
}

int16_t ICM20602::getAccXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_ACCEL_XOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_ACCEL_XOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
//    pc1.printf("accx:%d,%d\r\n",HiByte,LoByte);  // send data to matlab
}

int16_t ICM20602::getAccYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_ACCEL_YOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_ACCEL_YOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t ICM20602::getAccZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_ACCEL_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_ACCEL_ZOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t ICM20602::getGyrXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_GYRO_XOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_GYRO_XOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t ICM20602::getGyrYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_GYRO_YOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_GYRO_YOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t ICM20602::getGyrZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_GYRO_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_GYRO_ZOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t ICM20602::getIMUTemp()
{
    uint8_t LoByte, HiByte;
    LoByte = ICM20602_ReadByte(ICM20602_TEMP_OUT_L); // read Accelerometer X_Low  value
    HiByte = ICM20602_ReadByte(ICM20602_TEMP_OUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}


// Calculates Acc resolution
float ICM20602::setAccRange(int Ascale)
{
    switch(Ascale)
    {
        case AFS_2G:
            aRes = 2.0/32768.0;
            break;
        case AFS_4G:
            aRes = 4.0/32768.0;
            break;
        case AFS_8G:
            aRes = 8.0/32768.0;
            break;
        case AFS_16G:
            aRes = 16.0/32768.0;
            break;         
    }
    ICM20602_WriteByte(ICM20602_ACCEL_CONFIG, Ascale<<3);// bit[4:3] 0=+-2g,1=+-4g,2=+-8g,3=+-16g, ACC_HPF=On (5Hz)
    return aRes;
}

// Calculates Gyro resolution
float ICM20602::setGyroRange(int Gscale)
{
    switch(Gscale)
    {
        case GFS_250DPS:
            gRes = 250.0/32768.0;
            break;
        case GFS_500DPS:
            gRes = 500.0/32768.0;
            break;
        case GFS_1000DPS:
            gRes = 1000.0/32768.0;
            break;
        case GFS_2000DPS:
            gRes = 2000.0/32768.0;
            break;
    }
    ICM20602_WriteByte(ICM20602_GYRO_CONFIG, Gscale<<3); // bit[4:3] 0=+-250d/s,1=+-500d/s,2=+-1000d/s,3=+-2000d/s
    return gRes;
}