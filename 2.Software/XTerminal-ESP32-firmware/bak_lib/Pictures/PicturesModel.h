#ifndef __Pictures_MODEL_H
#define __Pictures_MODEL_H

#include <string>

#include "lvgl.h"

namespace Page
{

class PicturesModel
{
public:
    void Init();
    void DeInit();

    std::string termText;
    // char* termText;
private:

    void Println(char* text);

};
// extern std::string globalTermText;

}

#endif
