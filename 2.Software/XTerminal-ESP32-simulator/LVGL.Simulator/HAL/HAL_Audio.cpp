#include "HAL.h"
#include "App/Utils/TonePlayer/TonePlayer.h"
#include "App/Utils/TonePlayer/MusicCode.h"
#include "lvgl/lvgl.h"

static TonePlayer player;


void audio_init()
{
#ifdef USE_I2S

    audio = new Audio();

    if (audio != nullptr)
    {
        audio->setPinout(CONFIG_I2S_BCLK, CONFIG_I2S_LRC, CONFIG_I2S_DOUT);
        audio->setVolume(8); // 0...21
    }

#endif
}

void audio_start()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        audio->connecttoFS(SD, "/1.mp3");
    }
#endif
}

void audio_play(const char* name)
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        audio->connecttoFS(SD, name);
    }
#endif
}

void audio_pause()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        gflag.audio_en_flag = 0;
        audio->stopSong();
        gflag.audio_en_flag = 1;
}
#endif
}

void audio_resume()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        gflag.audio_en_flag = 0;
        audio->pauseResume();
        gflag.audio_en_flag = 1;
    }
#endif
}

void	audio_vol_plus()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        audio_vol_num++;
        __LimitValue(audio_vol_num, 1, 20);
        audio->setVolume(audio_vol_num); // 0...21
    }
#endif
}

void	audio_vol_minus()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        audio_vol_num--;
        __LimitValue(audio_vol_num, 1, 20);
        audio->setVolume(audio_vol_num); // 0...21
    }
#endif
}

void audio_loop()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        audio->loop();
    }
#endif
}

void audio_delete()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        delete audio;
    }
#endif
}


static void Tone_Callback(uint32_t freq, uint16_t volume)
{
    HAL::Buzz_Tone(freq);
}

void HAL::Audio_Init()
{
    player.SetCallback(Tone_Callback);
    Buzz_Tone(1000, 1000);
}

void HAL::Audio_Update()
{
    player.Update(lv_tick_get());
}

bool HAL::Audio_PlayMusic(const char* name)
{
    bool retval = false;
    for (int i = 0; i < sizeof(MusicList) / sizeof(MusicList[0]); i++)
    {
        if (strcmp(name, MusicList[i].name) == 0)
        {
            player.Play(MusicList[i].mc, MusicList[i].length);
            retval = true;
            break;
        }
    }
    return retval;
}
