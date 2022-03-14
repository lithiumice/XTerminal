/*
  Mystic Balloon: http://www.team-arg.org/mybl-manual.html

  Arduboy version 1.7.2:  http://www.team-arg.org/mybl-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016-2018 - GAVENO - CastPixel - JO3RI - Martian220

  Game License: MIT : https://opensource.org/licenses/MIT
*/
//determine the game
#define GAME_ID 34
// #include "Games.h"
// using namespace mybl;

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  mybl_stateMenuIntro,
  mybl_stateMenuMain,
  mybl_stateMenuHelp,
  mybl_stateMenuPlaySelect,
  mybl_stateMenuInfo,
  mybl_stateMenuSoundfx,
  mybl_stateGameNextLevel,
  mybl_stateGamePlaying,
  mybl_stateGamePause,
  mybl_stateGameOver,
  mybl_stateMenuPlayContinue,
  mybl_stateMenuPlayNew,
};

void mybl_setup()
{
  arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  arduboy.audio.begin();
  arduboy.bootLogoSpritesSelfMasked();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  loadSetEEPROM();
}

void mybl_loop() {
  if (!(arduboy.nextFrame())) return;
  if (mybl_gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer)mainGameLoop[mybl_gameState])();
  // ((FunctionPointer) pgm_read_word (&mainGameLoop[mybl_gameState]))();
  arduboy.display();
}

