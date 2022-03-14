#ifndef __ANO_DT__
#define __ANO_DT__
#include "Arduino.h"

#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

class data_send
{
private:
    void send_data(uint8_t *dataToSend, uint8_t length)
    {
        Serial.write(dataToSend, length);
    }

public:
    data_send() {}

    void send_vofa_4(float data1, float data2, float data3, float data4)
    {
        float data[4];
        data[0] = data1;
        data[1] = data2;
        data[2] = data3;
        data[3] = data4;
        send_data((uint8_t *)data, sizeof(float) * 4);

        char tail[4] = {0x00, 0x00, 0x80, 0x7f};
        send_data((uint8_t *)tail, 4);
    }

    void send_vofa_8(float data1, float data2, float data3, float data4,
                     float data5, float data6, float data7, float data8)
    {
        float data[8];
        data[0] = data1;
        data[1] = data2;
        data[2] = data3;
        data[3] = data4;
        data[4] = data5;
        data[5] = data6;
        data[6] = data7;
        data[7] = data8;
        send_data((uint8_t *)data, sizeof(float) * 8);

        char tail[4] = {0x00, 0x00, 0x80, 0x7f};
        send_data((uint8_t *)tail, 4);
    }

    // void send_ano_pid(uint8_t group, float p1_p, float p1_i, float p1_d, float p2_p,
    //                   float p2_i, float p2_d, float p3_p, float p3_i, float p3_d)
    // {
    //     uint8_t _cnt = 0;
    //     short _temp;

    //     ano_data_buff[_cnt++] = 0xAA;
    //     ano_data_buff[_cnt++] = 0xAA;
    //     ano_data_buff[_cnt++] = 0x10 + group - 1;
    //     ano_data_buff[_cnt++] = 0;

    //     _temp = (short)(p1_p * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p1_i * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p1_d * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p2_p * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p2_i * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p2_d * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p3_p * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p3_i * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);
    //     _temp = (short)(p3_d * 1000);
    //     ano_data_buff[_cnt++] = BYTE1(_temp);
    //     ano_data_buff[_cnt++] = BYTE0(_temp);

    //     ano_data_buff[3] = _cnt - 4;

    //     uint8_t sum = 0;
    //     for (uint8_t i = 0; i < _cnt; i++)
    //         sum += ano_data_buff[i];

    //     ano_data_buff[_cnt++] = sum;

    //     send_data(ano_data_buff, _cnt);
    // }

    // void send_ano_8(short data1, short data2, short data3, short data4,
    //                 short data5, short data6, short data7, short data8)
    // {
    //     uint8_t _cnt = 0;
    //     ano_data_buff[_cnt++] = 0xAA; //匿名协议帧头  0xAAAA
    //     ano_data_buff[_cnt++] = 0xAA;
    //     ano_data_buff[_cnt++] = 0xF1; //使用用户协议帧0xF1
    //     ano_data_buff[_cnt++] = 16;   //8个short 长度 16个字节

    //     ano_data_buff[_cnt++] = BYTE1(data1);
    //     ano_data_buff[_cnt++] = BYTE0(data1);

    //     ano_data_buff[_cnt++] = BYTE1(data2);
    //     ano_data_buff[_cnt++] = BYTE0(data2);

    //     ano_data_buff[_cnt++] = BYTE1(data3);
    //     ano_data_buff[_cnt++] = BYTE0(data3);

    //     ano_data_buff[_cnt++] = BYTE1(data4);
    //     ano_data_buff[_cnt++] = BYTE0(data4);

    //     ano_data_buff[_cnt++] = BYTE1(data5);
    //     ano_data_buff[_cnt++] = BYTE0(data5);

    //     ano_data_buff[_cnt++] = BYTE1(data6);
    //     ano_data_buff[_cnt++] = BYTE0(data6);

    //     ano_data_buff[_cnt++] = BYTE1(data7);
    //     ano_data_buff[_cnt++] = BYTE0(data7);

    //     ano_data_buff[_cnt++] = BYTE1(data8);
    //     ano_data_buff[_cnt++] = BYTE0(data8);

    //     uint8_t sum = 0;
    //     for (uint8_t i = 0; i < _cnt; i++)
    //         sum += ano_data_buff[i];
    //     ano_data_buff[_cnt++] = sum;

    //     send_data(ano_data_buff, _cnt);
    // }
};

#endif