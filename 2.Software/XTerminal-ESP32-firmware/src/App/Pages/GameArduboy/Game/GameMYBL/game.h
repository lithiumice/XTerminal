#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"

#define TOTAL_TONES 10
PROGMEM const byte tones[] = {
  //200, 100, 250, 125, 300, 150, 350, 400, 425, 475
  131, 145, 139, 152, 131, 172, 200, 188, 213, 255
};

byte toneindex = 0;

void mybl_stateMenuPlayNew()
{
  level = LEVEL_TO_START_WITH - 1;
  coinsCollected = 0;
  totalCoins = 0;
  balloonsLeft = 0;
  mybl_scorePlayer = 0;
  mybl_globalCounter = 0;
  kid.balloons = 3;
  mybl_gameState = STATE_GAME_NEXT_LEVEL;
  scoreIsVisible = false;
  nextLevelIsVisible = true;
  pressKeyIsVisible = false;
}

void mybl_stateMenuPlayContinue()
{
  level = EEPROM.read(OFFSET_LEVEL);
  totalCoins = EEPROM.read(OFFSET_COINS);
  coinsCollected = 0;
  balloonsLeft = 0;
  //mybl_scorePlayer = 0;
  EEPROM.get(OFFSET_SCORE, mybl_scorePlayer);
  mybl_globalCounter = 0;
  kid.balloons = 3;
  mybl_gameState = STATE_GAME_NEXT_LEVEL;
  scoreIsVisible = false;
  nextLevelIsVisible = true;
  pressKeyIsVisible = false;
}


void mybl_stateGameNextLevel()
{
  //if (level < TOTAL_LEVELS)
  //{
    if (arduboy.everyXFrames(20))
    {
      canPressButton = false;
      if (coinsCollected > 0)
      {
        coinsCollected--;
        mybl_scorePlayer += 20;
        sound.tone(pgm_read_byte(tones + toneindex++), 150);
      }
      else if (balloonsLeft > 0)
      {
        balloonsLeft--;
        mybl_scorePlayer += 30;
        sound.tone(pgm_read_byte(tones + toneindex++), 150);
      }
      else
      {
        canPressButton = true;
        scoreIsVisible = false;
        pressKeyIsVisible = !pressKeyIsVisible;
        if (toneindex < TOTAL_TONES)
        {
          sound.tone(pgm_read_byte(tones + toneindex++), 200);
          toneindex = TOTAL_TONES;
        }
        if (level >= TOTAL_LEVELS)
          mybl_gameState = STATE_GAME_OVER;
      }
    }
  /*}
  else
  {
    mybl_gameState = STATE_GAME_OVER;
    return;
  }*/

  // Update EEPROM
  EEPROM.put(OFFSET_LEVEL, level);
  EEPROM.put(OFFSET_COINS, totalCoins);
  EEPROM.put(OFFSET_SCORE, mybl_scorePlayer);


  //if (nextLevelIsVisible)
  //{
  if (level < TOTAL_LEVELS)
  {
    sprites.drawSelfMasked(35, 4, badgeNextLevel, 0);
    drawNumbers(78, 13, FONT_BIG, DATA_LEVEL);
  }
  else
  {
    EEPROM.put(OFFSET_LEVEL, (byte)LEVEL_TO_START_WITH - 1);
    // Score remains after completing game? (no)
    EEPROM.put(OFFSET_SCORE, (unsigned long)0);
  }
  drawNumbers(43, 49, FONT_BIG, DATA_SCORE);
  //}

  if (scoreIsVisible)
  {
    byte totalBadges = coinsCollected + balloonsLeft;

    for (byte i = 0; i < totalBadges; ++i)
    {
      if (i < coinsCollected) sprites.drawOverwrite(65 - (7 * totalBadges) + (i * 14), 27, badgeElements, 0);
      else sprites.drawOverwrite(65 - (7 * totalBadges) + (i * 14), 27, badgeElements, 1);
    }
  }

  if (canPressButton)
  {

    if (pressKeyIsVisible) sprites.drawOverwrite(38, 29, badgePressKey, 0);
    if (arduboy.justPressed(A_BUTTON | B_BUTTON))
    {
      toneindex = 0;
      sound.tone(425, 20);
      setKid();
      //cam.pos = vec2(0, 0);
      cam.pos = vec2(0, LEVEL_HEIGHT - 64);
      cam.offset = vec2(0, 0);
      enemiesInit();
      levelLoad(levels[level]);
      mybl_gameState = STATE_GAME_PLAYING;
    }
  }
};


void mybl_stateGamePlaying()
{
  checkInputs();
  checkKid();
  updateCamera();

  drawGrid();
  enemiesUpdate();

  drawKid();
  drawHUD();

  checkCollisions();
}


void mybl_stateGamePause()
{
  sprites.drawSelfMasked(47, 17, badgePause, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    mybl_gameState = STATE_GAME_PLAYING;
  }
}


void mybl_stateGameOver()
{
  byte x = 35 + 12;
  if (level < TOTAL_LEVELS)
  {
    drawNumbers(78, 26, FONT_BIG, DATA_LEVEL);
    x -= 12;
  }
  sprites.drawSelfMasked(x, 17, badgeGameOver, 0);
  drawNumbers(43, 49, FONT_BIG, DATA_SCORE);

  unsigned long highscore = 0;
  EEPROM.get(OFFSET_HSCORE, highscore);
  if (mybl_scorePlayer > highscore) {
    EEPROM.put(OFFSET_COINSHS, totalCoins);
    EEPROM.put(OFFSET_HSCORE, mybl_scorePlayer);
  }
    
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    mybl_gameState = STATE_MENU_MAIN;
  }
}

#endif
