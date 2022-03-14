#ifndef __Terminal_MODEL_H
#define __Terminal_MODEL_H

#include <string>

#include "lvgl.h"

namespace Page
{

class TerminalModel
{
public:
    void Init();
    void DeInit();

    std::string termText;

private:

    void Println(char* text);

};

}

#endif
