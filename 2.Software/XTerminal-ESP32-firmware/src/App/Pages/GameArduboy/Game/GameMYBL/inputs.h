#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "globals.h"
#include "player.h"

#define TIMER_AMOUNT 48

void checkInputs()
{
  if (kid.balloons <= 0)
    return; // Cannot control player if dead

    
  cam.offset = vec2(0, 0);
  kid.isWalking = false;
  if (arduboy.pressed(DOWN_BUTTON))
  {
    cam.offset.y = -CAMERA_OFFSET;
  }
  else if (arduboy.pressed(UP_BUTTON))
  {
    cam.offset.y = CAMERA_OFFSET;
  }
  if (!kid.isSucking) 
  {
    if (arduboy.pressed(LEFT_BUTTON))
    {
      mapTimer = TIMER_AMOUNT;
      cam.offset.x = CAMERA_OFFSET;
      kid.direction = FACING_LEFT;
      if (!(kid.isJumping || kid.isBalloon || kid.isLanding))
      {
        if (!gridGetSolid((kid.pos.x - 1) >> 4, (kid.pos.y + 8) >> 4))
          kid.actualpos.x -= PLAYER_SPEED_WALKING;
        kid.isWalking = true;
        kid.speed.x = -1;
      }
      else
      {
        //kid.speed.x = max(kid.speed.x - PLAYER_SPEED_AIR, -MAX_XSPEED);
        if (kid.speed.x > -MAX_XSPEED)
          kid.speed.x -= PLAYER_SPEED_AIR;
      }
    }
    else if (arduboy.pressed(RIGHT_BUTTON))
    {
      //mapTimer = TIMER_AMOUNT;
      cam.offset.x = -CAMERA_OFFSET;
      kid.direction = FACING_RIGHT;
      if (!(kid.isJumping || kid.isBalloon || kid.isLanding))
      {
        if (!gridGetSolid((kid.pos.x + 12) >> 4, (kid.pos.y + 8) >> 4))
          kid.actualpos.x += PLAYER_SPEED_WALKING;
        kid.isWalking = true;
        kid.speed.x = 1;
      }
      else
      {
        //kid.speed.x = min(kid.speed.x + PLAYER_SPEED_AIR, MAX_XSPEED);
        if (kid.speed.x < MAX_XSPEED)
          kid.speed.x += PLAYER_SPEED_AIR;
      }
    }
  }
  kid.isSucking = false;
  if (arduboy.pressed(A_BUTTON))
  {
    if (arduboy.pressed(DOWN_BUTTON))
      mybl_gameState = STATE_GAME_PAUSE;
    else //if (!kid.isBalloon)
    {
      kid.isBalloon = false;
      kid.isSucking = true;
    }
  }
  /*if (arduboy.pressed(A_BUTTON + DOWN_BUTTON))  mybl_gameState = STATE_GAME_PAUSE;
  if (arduboy.pressed(A_BUTTON) && !kid.isBalloon)
  {
    kid.isSucking = true;
  }
  else
    kid.isSucking = false;*/

  // Jump Button
  if (arduboy.justPressed(B_BUTTON))
  {
    if (kid.speed.y == 0 && kid.isJumping == false && kid.isLanding == false)
    {
      sound.tone(200, 100);
      kid.isWalking = false;
      kid.isJumping = true;
      kid.jumpLetGo = false;
      kid.jumpTimer = PLAYER_JUMP_TIME;
      kid.speed.y = PLAYER_JUMP_VELOCITY;
      if (arduboy.pressed(RIGHT_BUTTON)) kid.speed.x = MAX_XSPEED;
      else if (arduboy.pressed(LEFT_BUTTON)) kid.speed.x = -MAX_XSPEED;
    }
    else
    {
      if (kid.balloons > 0)
      {
        kid.isBalloon = true;
        kid.balloonOffset = 16;
        kid.isJumping = false;
        kid.isLanding = true;
      }
    }
  }
  if (!arduboy.pressed(B_BUTTON))
  {
    kid.isBalloon = false;
    if (kid.isJumping) kid.jumpLetGo = true;
  }
}

#endif
