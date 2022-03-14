#ifndef __EEPROM_H
#define __EEPROM_H

//#include "SdFat.h"
#include <stdint.h>

class EEPROM_File
{
public:
    bool begin(const char* path, const char* fileName, uint32_t size = 1024){
        return false;
    }
    void end(){

    }
    
    uint8_t read(uint32_t idx){
        return 0;
    }
    void write(uint32_t idx, uint8_t val){

    }
    void update(uint32_t idx, uint8_t val){

    }

//    SdFile file;
};

#endif
