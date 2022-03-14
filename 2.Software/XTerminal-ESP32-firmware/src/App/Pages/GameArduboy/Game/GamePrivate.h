#ifndef __GAMEPRIVATE_H
#define __GAMEPRIVATE_H

#include <cstdint>
#include "HAL/CommonMacro.h"

typedef enum {
    GAME_BUTTON_A,
    GAME_BUTTON_B,
    GAME_BUTTON_UP,
    GAME_BUTTON_DOWN,
    GAME_BUTTON_LEFT,
    GAME_BUTTON_RIGHT,
    GAME_BUTTON_MAX
}GameButton_Type;

typedef enum {
    GAME_LED_RED,
    GAME_LED_GREEN,
    GAME_LED_BLUE,
    GAME_LED_MAX
}GameLED_Type;

enum {
    GAME_NONE,
    GAME_chribocchi,
    GAME_Arduboy3D,
    GAME_MAX
};

void Game_Begin();
const char* Game_GetNameList();
const char* Game_GetName(uint8_t id);
int16_t Game_GetNameID(const char* name);
bool Game_GetButtonPressed(uint8_t btn_id);
void Game_SetButtonState(uint8_t btn_id, bool state);
void Game_ClearButtonState();

void Game_SetLEDState(uint8_t led_id, bool val);
void Game_SetLEDBright(uint8_t led_id, uint8_t val);

bool Game_DispIsBusy();
bool Game_DispReqUpdate(bool clear = false);
void Game_DispTaskUpdate();
uint8_t* Game_DispGetBuffer();

#endif
