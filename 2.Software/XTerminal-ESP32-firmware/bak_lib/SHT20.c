/***************************************************************
*   File name    :  SHT20.c  
*   Description  :  SHT20 Humidity and Temperature Sensors 
*     M C U      :  STC89C52RC
*   Compiler     :  Keil uVision V4.00a (C51)
*   Created by   :  dingshidong
*   Copyright    :  Copyright(c) https://wclh.taobao.com/   
*   Created data :  2015.05.08  
*   Vision       :  V1.0
*****************************************************************/
#include <STC89.H> //stc89cxx head file
#include "SHT20.H" //sht20 head file 
/*================================================================
【  Name  】Pin Description
【Function】模拟IIC使用的引脚定义，注意要上拉电阻，SDA和SCL均上拉10KΩ电阻
【  Notes 】
================================================================*/
/*************Pin Description*************
   P2.6------SCK     (SHT20)
   P2.7------DATA    (SHT20)
*****************************************/
sbit SDA=P2^7;                 // define data pin
sbit SCL=P2^6;                 // define clock pin

/*================================================================
【  Name  】
【Function】SHT20的I2C地址
【  Notes 】
================================================================*/
#define SHT20ADDR 0x80
/*================================================================
【  Name  】
【Function】应答位电平定义
【  Notes 】
================================================================*/
#define ACK            0            //应答信号
#define NACK        1             //非应答信号

/*================================================================
【  Name  】void Delay(uint t)
【Function】delay Nms
【  Notes 】
================================================================*/
void Delay(uint t)
{
        uchar i;
        while(t--)
        {
                for(i=0;i<200;i++);
        }                                           
}
/*------------------------------------------------------------*/
/**********************Simulation I2C Function*****************/
/*------------------------------------------------------------*/

/*================================================================
【  Name  】void I2CDelay (uchar t)
【Function】模拟IIC用的短延时 us
【  Notes 】
================================================================*/
void I2CDelay (uchar t)          
{
        while(t--);
}

/*================================================================
【  Name  】void I2CInit(void)
【Function】I2C初始化，空闲状态
【  Notes 】
================================================================*/
void I2CInit(void)
{
        SDA = 1;
        I2CDelay(1); 
        SCL = 1;
        I2CDelay(1);
}

/*================================================================
【  Name  】void I2CStart(void)
【Function】I2C起始信号
【  Notes 】SCL、SDA同为高，SDA跳变成低之后，SCL跳变成低          
================================================================*/
void I2CStart(void)
{        
          SDA = 1;                            //发送起始条件的数据信号--ZLG
          SCL = 1;
          I2CDelay(5);                    //起始条件建立时间大于4.7us,延时--ZLG
          SDA = 0;                            //发送起始信号-ZLG
        I2CDelay(5);                    //起始条件锁定时间大于4μs--ZLG
          SCL = 0;                            //钳住I2C总线，准备发送或接收数据--ZLG
        I2CDelay(5);         
}

/*================================================================
【  Name  】void I2CStop(void)
【Function】I2C停止信号
【  Notes 】SCL、SDA同为低，SCL跳变成高之后，SDA跳变成高           
================================================================*/
void I2CStop(void)
{        
          SDA = 0;                        //发送结束条件的数据信号--ZLG
          SCL = 0;
        I2CDelay(5);
          SCL = 1;                        //发送结束条件的时钟信号--ZLG
          I2CDelay(5);                //结束条件建立时间大于4μs--ZLG
          SDA = 1;                        //发送I2C总线结束信号--ZLG
          I2CDelay(5); 
}

/*================================================================
【  Name  】uchar I2C_Write_Byte(uchar WRByte)
【Function】I2C写一个字节数据，返回ACK或者NACK
【  Notes 】从高到低，依次发送
================================================================*/
uchar I2C_Write_Byte(uchar Write_Byte)         //Sendbyte
{
        uchar i;      
        for(i=0;i<8;i++)              //要传送的数据长度为8位--ZLG
        {         
                if(Write_Byte&0x80)              //判断发送位--ZLG
                {
                        SDA = 1;        
                }
                else
                {
                        SDA = 0;
                }
                I2CDelay(1);                
                SCL=1;                                  //输出SDA稳定后，拉高SCL给出上升沿，从机检测到后进行数据采样      
                I2CDelay(5);                        //保证时钟高电平周期大于4μs--ZLG
                SCL=0;
                I2CDelay(1);
                Write_Byte <<= 1;
        } 
        I2CDelay(4);
        SDA = 1;                                  //8位发送完后释放数据线，准备接收应答位-ZLG
    SCL = 1;                      //MCU告知SHT2X数据发送完毕，等待从机的应答信号        
        I2CDelay(5);                   
        /*以下是判断I2C总线接收应到应答信号是ACK还是NACK*/
        if(SDA==1)                                   //SDA为高，收到NACK
                return NACK;        
        else                                           //SDA为低，收到ACK                
                return ACK;        
        SCL=0;
        I2CDelay(15);   
}

/*================================================================
【  Name  】uchar I2C_Read_Byte(uchar AckValue)
【Function】I2C读一个字节数据，入口参数用于控制应答状态，ACK或者NACK
【  Notes 】从高到低，依次接收
================================================================*/
uchar I2C_Read_Byte(uchar AckValue)//receivebyte
{
        uchar i,RDByte=0;
        SCL=0;                                                  //置时钟线为低，准备接收数据位--ZLG
        SDA = 1;                                  //释放总线,置数据线为输入方式--ZLG        
        for (i=0;i<8;i++) 
        {        
                SCL = 1;                          //SCL高电平期间，采集SDA信号，并作为有效数据 //置时钟线为高使数据线上数据有效--ZLG 
                I2CDelay(2);
                RDByte <<= 1;                  //移位
                if(SDA==1)                           //采样获取数据
                {
                        RDByte |= 0x01;
                }
                else
                {
                        RDByte &= 0xfe;
                }
                I2CDelay(1);
                SCL = 0;                             //下降沿，从机给出下一位值
                I2CDelay(6);
        }   
        /*以下是I2C总线发送应答信号ACK或者NACK*/
        SDA = AckValue;                      //应答状态        
        I2CDelay(3);
        SCL = 1;                         
          I2CDelay(5);                  //时钟低电平周期大于4μs--ZLG
          SCL = 0;                                  //清时钟线，钳住I2C总线以便继续接收--ZLG               
          I2CDelay(15);
        //SDA = 1;        
        return RDByte;
}

/*================================================================
【  Name  】void SoftReset(void)
【Function】SHT20软件复位，主函数中调用
【  Notes 】从高到低，依次接收
================================================================*/
void SoftReset(void)                    
{
        I2CInit();                       //I2C initialize
        I2CStart();                      //start I2C
        I2C_Write_Byte(SHT20ADDR&0xfe);  //I2C address + write
        I2C_Write_Byte(0xfe);                         //soft reset
        I2CStop();                       //stop I2C
}

/*================================================================
【  Name  】void SET_Resolution(void)
【Function】写寄存器，设置分辨率
【  Notes 】
================================================================*/
void SET_Resolution(void)                    
{
  I2CStart();                                                                         //Start I2C 
  if(I2C_Write_Byte(SHT20ADDR&0xfe)==ACK)       //I2C address + write + ACK
  {
   if(I2C_Write_Byte(0xe6)==ACK)                            //写用户寄存器
    {  
     if(I2C_Write_Byte(0x83)==ACK);                            //设置分辨率   11bit RH% 测量时间：12ms(typ.) & 11bit T℃ 测量时间：9ms(typ.) 
    }
  }
   I2CStop();                                   //Stop I2C         
}
 
/*================================================================
【  Name  】float ReadSht20(char whatdo)
【Function】非主机模式，读取函数函数
【  Notes 】
================================================================*/
float ReadSht20(char whatdo)
{
        float temp;
        uchar MSB,LSB;
        float Humidity,Temperature;

        SET_Resolution();
        I2CStart();        
        if(I2C_Write_Byte(SHT20ADDR&0xfe)==ACK)                  //I2C address + write + ACK
        {        
            if(I2C_Write_Byte(whatdo)==ACK)                      //Command
                {
                 do
                  {
                        Delay(6);
                        I2CStart();        
                        }while(I2C_Write_Byte(SHT20ADDR|0x01)==NACK);     //I2C address + read        + NACK 

                        MSB = I2C_Read_Byte(ACK);                                              //Data(MSB)
                        LSB = I2C_Read_Byte(ACK);                                              //Data(LSB)
                        I2C_Read_Byte(NACK);                                                          //Checksum  + NACK 
                        I2CStop();                                                                              //Stop I2C
                        LSB &= 0xfc;                                          //Data (LSB) 的后两位在进行物理计算前前须置‘0’ 
                        temp = MSB*256 + LSB;                                                          //十六进制转成十进制

                        if (whatdo==((char)0xf5))                                          //No Hold Master Mode，read humidity
                        {        
                          /*-- calculate relative humidity [%RH] --*/ 
                                Humidity =(temp*125)/65536-6;                 //公式: RH%= -6 + 125 * SRH/2^16
                                return Humidity;                              //返回值：humidity
                        }                                                                                                  
                        else                                                                                      //No Hold Master Mode，read temperature
                        {        
                           /*-- calculate temperature [°C] --*/
                                Temperature = (temp*175.72)/65536-46.85;      //公式:T= -46.85 + 175.72 * ST/2^16
                                return Temperature;                                      //返回值：temperature
                        }
                 }
          }
        return 0;
}
