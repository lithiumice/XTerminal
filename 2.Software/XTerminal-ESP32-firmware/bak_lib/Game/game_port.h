//
// Created by lithiumice on 2021/11/29.
//

#ifndef PEAK_ESP32_FW_GAME_PORT_H
#define PEAK_ESP32_FW_GAME_PORT_H

////#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
//#define bitWrite(value, bit, bitvalue)
////#define portOutputRegister(Port)    (&((Port)->ODR))
//#define portOutputRegister(Port)
////#define digitalPinToPort(Pin)       (PIN_MAP[Pin].GPIOx)
////#define digitalPinToBitMask(Pin)    (PIN_MAP[Pin].GPIO_Pin_x)
//#define digitalPinToPort(Pin)
//#define digitalPinToBitMask(Pin)

#define F_CPU 240000000
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000U)

#endif //PEAK_ESP32_FW_GAME_PORT_H
