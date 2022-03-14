#pragma once

#ifdef ARDUINO
#include "Audio.h"
extern Audio* audio;
#endif

void audio_init();
void audio_start();
void audio_loop();
void audio_delete();
void audio_resume();
void audio_pause();
void audio_play(const char *name);
void	audio_vol_plus();
void	audio_vol_minus();
