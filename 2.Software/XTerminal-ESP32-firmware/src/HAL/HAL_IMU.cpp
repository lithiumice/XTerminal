#include "HAL/HAL_IMU.h"
#include "App/Accounts/Account_Master.h"
#include <stdlib.h>
#include <MadgwickAHRS.h>

#if defined(USE_MPU6050)
#include "MPU6050.h"
MPU6050 mpu;
#elif defined(USE_MPU6050_DMP)
#include "MPU6050.h"
MPU6050 mpu;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
#elif defined(USE_ICM20602)
#include "App/icm20602_i2c.h"
ICM20602 mpu;
#else
#endif

Madgwick filter;
int16_t ax, ay, az;
int16_t gx, gy, gz;
HAL::IMU_Info_t imuInfo;
ACTIVE_TYPE mpu_action = ACTIVE_TYPE_MAX;
uint8_t mpu_act_valid = 0;

float convertRawAcceleration(int aRaw)
{
    // since we are using 2G range
    // -2g maps to a raw value of -32768
    // +2g maps to a raw value of 32767

    float a = (aRaw * 2.0) / 32768.0;
    return a;
}

float convertRawGyro(int gRaw)
{
    // since we are using 250 degrees/seconds range
    // -250 maps to a raw value of -32768
    // +250 maps to a raw value of 32767

    float g = (gRaw * 250.0) / 32768.0;
    return g;
}

void mpu_action_judge()
{
    if (!mpu_act_valid)
    {
        if (imuInfo.ay > 0.244) // 4000
        {
            mpu_act_valid = 1;
            mpu_action = TURN_LEFT;
        }
        else if (imuInfo.ay < -0.244)
        {
            mpu_act_valid = 1;
            mpu_action = TURN_RIGHT;
        }
        else if (imuInfo.ax > 0.3) // 0.3 --> 5000
        {
            mpu_act_valid = 1;
            mpu_action = TURN_UP;
            // delay(500);
            // mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
            // if (ax > 5000)
            // {
            //     mpu_act_valid = 1;
            //     mpu_action = FORWORD;
            // }
        }
        else if (imuInfo.ax < -0.3)
        {
            mpu_act_valid = 1;
            mpu_action = TURN_DOWN;
            // delay(500);
            // mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
            // if (ax < -5000)
            // {
            //     mpu_act_valid = 1;
            //     mpu_action = BACKWARD;
            // }
        }
        else
        {
            mpu_act_valid = 0;
            mpu_action = TURN_NONE;
        }
    }
}

void HAL::IMU_Init()
{
#if defined(USE_MPU6050)

    mpu.initialize();
    filter.begin(50);

    Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    HAL::config_mpu_load();
    mpu.setXGyroOffset(HAL::config.mpu_config.x_gyro_offset);
    mpu.setYGyroOffset(HAL::config.mpu_config.y_gyro_offset);
    mpu.setZGyroOffset(HAL::config.mpu_config.z_gyro_offset);
    mpu.setXAccelOffset(HAL::config.mpu_config.x_accel_offset);
    mpu.setYAccelOffset(HAL::config.mpu_config.y_accel_offset);
    mpu.setZAccelOffset(HAL::config.mpu_config.z_accel_offset);
#elif defined(USE_MPU6050_DMP)

    filter.begin(50);
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    mpu.setDMPEnabled(true);

    Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    HAL::config_mpu_load();
    mpu.setXGyroOffset(HAL::config.mpu_config.x_gyro_offset);
    mpu.setYGyroOffset(HAL::config.mpu_config.y_gyro_offset);
    mpu.setZGyroOffset(HAL::config.mpu_config.z_gyro_offset);
    mpu.setXAccelOffset(HAL::config.mpu_config.x_accel_offset);
    mpu.setYAccelOffset(HAL::config.mpu_config.y_accel_offset);
    mpu.setZAccelOffset(HAL::config.mpu_config.z_accel_offset);

#elif defined(USE_ICM20602)

    mpu.init(Wire1, I2C_SPEED_FAST);
    mpu.setAccRange(AFS_2G);
    mpu.setGyroRange(GFS_250DPS);
    mpu.whoAmI();
    filter.begin(50);

#else
#endif
}

void HAL::IMU_Calibrate()
{
    // mpu.CalibrateAccel(7);
    // mpu.CalibrateGyro(7);
    // mpu.PrintActiveOffsets();

    // HAL::config.mpu_config.x_gyro_offset = mpu.getXGyroOffset();
    // HAL::config.mpu_config.y_gyro_offset = mpu.getYGyroOffset();
    // HAL::config.mpu_config.z_gyro_offset = mpu.getZGyroOffset();
    // HAL::config.mpu_config.x_accel_offset = mpu.getXAccelOffset();
    // HAL::config.mpu_config.y_accel_offset = mpu.getYAccelOffset();
    // HAL::config.mpu_config.z_accel_offset = mpu.getZAccelOffset();
    // HAL::config_mpu_save();

    // HAL::TerminalPrintln("mpu calibrate done!");
}

void HAL::IMU_Update()
{
#if defined(USE_MPU6050)
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax = convertRawAcceleration(ax);
    ay = convertRawAcceleration(ay);
    az = convertRawAcceleration(az);
    gx = convertRawGyro(gx);
    gy = convertRawGyro(gy);
    gz = convertRawGyro(gz);

    imuInfo.ax = (float)ax;
    imuInfo.ay = (float)ay;
    imuInfo.az = (float)az;
    imuInfo.gx = (float)gx;
    imuInfo.gy = (float)gy;
    imuInfo.gz = (float)gz;
    imuInfo.mx = 0;
    imuInfo.my = 0;
    imuInfo.mz = 0;

    filter.updateIMU(gx, gy, gz, ax, ay, az);

    imuInfo.roll = filter.getRoll();
    imuInfo.pitch = filter.getPitch();
    imuInfo.yaw = filter.getYaw();

    if (imuInfo.roll < 0)
        imuInfo.roll += 180;
    else
        imuInfo.roll -= 180;

    mpu_action_judge();
    AccountSystem::IMU_Commit(&imuInfo);

#elif defined(USE_MPU6050_DMP)

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
    {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        Serial.print("ypr\t");
        Serial.print(ypr[0] * 180 / M_PI);
        Serial.print("\t");
        Serial.print(ypr[1] * 180 / M_PI);
        Serial.print("\t");
        Serial.println(ypr[2] * 180 / M_PI);
    }

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax = convertRawAcceleration(ax);
    ay = convertRawAcceleration(ay);
    az = convertRawAcceleration(az);
    gx = convertRawGyro(gx);
    gy = convertRawGyro(gy);
    gz = convertRawGyro(gz);

    imuInfo.ax = (float)ax;
    imuInfo.ay = (float)ay;
    imuInfo.az = (float)az;
    imuInfo.gx = (float)gx;
    imuInfo.gy = (float)gy;
    imuInfo.gz = (float)gz;
    imuInfo.mx = 0;
    imuInfo.my = 0;
    imuInfo.mz = 0;

    filter.updateIMU(gx, gy, gz, ax, ay, az);

    imuInfo.roll = filter.getRoll();
    imuInfo.pitch = filter.getPitch();
    imuInfo.yaw = filter.getYaw();

    if (imuInfo.roll < 0)
        imuInfo.roll += 180;
    else
        imuInfo.roll -= 180;

    mpu_action_judge();
    AccountSystem::IMU_Commit(&imuInfo);

#elif defined(USE_ICM20602)
    ax = mpu.getAccXvalue();
    ay = mpu.getAccYvalue();
    az = mpu.getAccZvalue();
    gx = mpu.getGyrXvalue();
    gy = mpu.getGyrYvalue();
    gz = mpu.getGyrZvalue();

    // printf("ax: %d, ay: %d, az: %d, gx: %d, gy: %d, gz: %d\n",
    //        (int)ax, (int)ay,  (int)az,  (int)gx,  (int)gy,  (int)gz);



    
    imuInfo.ax = (float)ax;
    imuInfo.ay = (float)ay;
    imuInfo.az = (float)az;
    imuInfo.gx = (float)gx;
    imuInfo.gy = (float)gy;
    imuInfo.gz = (float)gz;
    imuInfo.mx = 0;
    imuInfo.my = 0;
    imuInfo.mz = 0;
    
ax = convertRawAcceleration(ax);
    ay = convertRawAcceleration(ay);
    az = convertRawAcceleration(az);
    gx = convertRawGyro(gx);
    gy = convertRawGyro(gy);
    gz = convertRawGyro(gz);
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    imuInfo.roll = filter.getRoll();
    imuInfo.pitch = filter.getPitch();
    imuInfo.yaw = filter.getYaw();

    if (imuInfo.roll < 0)
        imuInfo.roll += 180;
    else
        imuInfo.roll -= 180;

    mpu_action_judge();
    AccountSystem::IMU_Commit(&imuInfo);
#else
#endif
}
