#include "HAL/HAL.h"
#include "HAL_Audio.h"
#include "App/Utils/TonePlayer/TonePlayer.h"
#include "App/Utils/TonePlayer/MusicCode.h"
#include "lvgl.h"
#include "HAL/HAL_Audio.h"
#include "Audio.h"
Audio *audio;
int audio_vol_num = 8;
static TonePlayer player;

static void Tone_Callback(uint32_t freq, uint16_t volume)
{
    HAL::Buzz_Tone(freq);
}

void HAL::Audio_Init()
{
    player.SetCallback(Tone_Callback);
}

void HAL::Audio_Update()
{
    player.Update(lv_tick_get());
}

bool HAL::Audio_PlayMusic(const char *name)
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
#define AUDIO_DBG printf
void audio_init()
{
#ifdef USE_I2S

    audio = new Audio();

    if (audio != nullptr)
    {
        AUDIO_DBG("audio_init");
        audio->setPinout(CONFIG_I2S_BCLK, CONFIG_I2S_LRC, CONFIG_I2S_DOUT);
        audio->setVolume(8); // 0...21
        // audio->setFileLoop(true);
    }

#endif
}

void audio_start()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        AUDIO_DBG("audio_play");
        audio->connecttoFS(SD, "/Sweden-C418.mp3");
    }
#endif
}

void audio_play(const char *name)
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        AUDIO_DBG("audio_play");
        audio->connecttoFS(SD, name);
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

void audio_pause()
{
#ifdef USE_I2S
    if (audio != nullptr)
    {
        gflag.audio_en_flag = 0;
        // audio->stopSong();
        audio->pauseResume();
        AUDIO_DBG("audio_pause");

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
        AUDIO_DBG("audio_resume");
        audio->pauseResume();
        gflag.audio_en_flag = 1;
    }
#endif
}

void audio_vol_plus()
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

void audio_vol_minus()
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

void audio_info(const char *info)
{
    Serial.print("info        ");
    Serial.println(info);
}
void audio_id3data(const char *info)
{ // id3 metadata
    Serial.print("id3data     ");
    Serial.println(info);
}
void audio_showstation(const char *info)
{
    Serial.print("station     ");
    Serial.println(info);
}
void audio_showstreamtitle(const char *info)
{
    Serial.print("streamtitle ");
    Serial.println(info);
}
void audio_bitrate(const char *info)
{
    Serial.print("bitrate     ");
    Serial.println(info);
}
void audio_commercial(const char *info)
{ // duration in sec
    Serial.print("commercial  ");
    Serial.println(info);
}
void audio_icyurl(const char *info)
{ // homepage
    Serial.print("icyurl      ");
    Serial.println(info);
}
void audio_lasthost(const char *info)
{ // stream URL played
    Serial.print("lasthost    ");
    Serial.println(info);
}
void audio_eof_speech(const char *info)
{
    Serial.print("eof_speech  ");
    Serial.println(info);
}
