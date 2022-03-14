/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// #include "AppFactory.h"
// #include "Weather/Weather.h"
// #include "SystemInfos/SystemInfos.h"
// #include "StartUp/StartUp.h"
// #include "AppList/AppList.h"
// #include "WifiText/WifiText.h"
// #include "NumTweak/NumTweak.h"
// #include "Settings/Settings.h"
// #include "Clock/Clock.h"
// #include "HeartBeat/HeartBeat.h"

// //game
// #include "GameList/GameList.h"
// #include "GameArduboy/GameArduboy.h"
// #include "MusicPlayer/MusicPlayer.h"
// #include "MusicPlayer/MusicPlayer.h"
#include "_APP_INC.inc"

PageBase* AppFactory::CreatePage(const char* name)
{
#define APP_DEF(className)\
do{\
    if (strcmp(name, #className) == 0)\
    {\
        return new Page::className;\
    }\
}while(0)

#include "_APP_DEF.inc"

#undef APP_DEF

    return nullptr;
}
