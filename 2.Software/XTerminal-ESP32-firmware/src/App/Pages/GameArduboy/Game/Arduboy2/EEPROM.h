
#ifndef EEPROM_h
#define EEPROM_h
#ifndef EEPROM_FLASH_PARTITION_NAME
#define EEPROM_FLASH_PARTITION_NAME "eeprom"
#endif
#include <Arduino.h>

#define float_t float
#define double_t double
typedef uint32_t nvs_handle;

class EEPROMClass {
  public:
    EEPROMClass(uint32_t sector){}
    EEPROMClass(const char* name, uint32_t user_defined_size){}
    EEPROMClass(void){}
    ~EEPROMClass(void){}

    bool begin(size_t size){return 0; }
    uint8_t read(int address) { return 1; }
    void write(int address, uint8_t val){}
    uint16_t length(){return 0; }
    bool commit(){return 0; }
    void end(){}

    uint8_t * getDataPtr(){return 0; }
    uint16_t convert(bool clear, const char* EEPROMname = "eeprom", const char* nvsname = "eeprom"){return 0; }

    template<typename T>
    T &get(int address, T &t) {
        if (address < 0 || address + sizeof(T) > _size)
            return t;

        memcpy((uint8_t*)&t, _data + address, sizeof(T));
      return t;
    }

    template<typename T>
    const T &put(int address, const T &t) {
        if (address < 0 || address + sizeof(T) > _size)
            return t;

        memcpy(_data + address, (const uint8_t*)&t, sizeof(T));
      _dirty = true;
      return t;
    }

    // uint8_t readByte(int address){return 0; }
    // int8_t readChar(int address){return 0; }
    // uint8_t readUChar(int address){return 0; }
    // int16_t readShort(int address){return 0; }
    // uint16_t readUShort(int address){return 0; }
    // int32_t readInt(int address){return 0; }
    // uint32_t readUInt(int address){return 0; }
    // int32_t readLong(int address){return 0; }
    // uint32_t readULong(int address){return 0; }
    // int64_t readLong64(int address){return 0; }
    // uint64_t readULong64(int address){return 0; }
    // float_t readFloat(int address){return 0; }
    // double_t readDouble(int address){return 0; }
    // bool readBool(int address){return 0; }
    // size_t readString(int address, char* value, size_t maxLen){return 0; }
    // String readString(int address){}
    // size_t readBytes(int address, void * value, size_t maxLen){return 0; }
    // template <class T> T readAll (int address, T &){}

    // size_t writeByte(int address, uint8_t value){return 0; }
    // size_t writeChar(int address, int8_t value){return 0; }
    // size_t writeUChar(int address, uint8_t value){return 0; }
    // size_t writeShort(int address, int16_t value){return 0; }
    // size_t writeUShort(int address, uint16_t value){return 0; }
    // size_t writeInt(int address, int32_t value){return 0; }
    // size_t writeUInt(int address, uint32_t value){return 0; }
    // size_t writeLong(int address, int32_t value){return 0; }
    // size_t writeULong(int address, uint32_t value){return 0; }
    // size_t writeLong64(int address, int64_t value){return 0; }
    // size_t writeULong64(int address, uint64_t value){return 0; }
    // size_t writeFloat(int address, float_t value){return 0; }
    // size_t writeDouble(int address, double_t value){return 0; }
    // size_t writeBool(int address, bool value) { return 0; }
    // size_t writeString(int address, const char* value){return 0; }
    // size_t writeString(int address, String value){return 0; }
    // size_t writeBytes(int address, const void* value, size_t len){return 0; }
    template <class T> T writeAll (int address, const T &){}

  protected:
    nvs_handle _handle;
    uint8_t* _data;
    size_t _size;
    bool _dirty;
    const char* _name;
    uint32_t _user_defined_size;
};

// #if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EEPROM)
// extern EEPROMClass EEPROM;
// #endif

#endif
