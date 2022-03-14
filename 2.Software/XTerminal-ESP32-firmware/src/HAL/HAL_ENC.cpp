#include "HAL/HAL.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"
#include "App/Accounts/Account_Master.h"
#include "Game/GamePrivate.h"
#include "PCF8574.h"

// #undef USE_PCF8574
// #undef USE_EKEY

extern uint32_t enc_dir_event_time;
extern uint8_t enc_btn_down_flag;

#ifdef USE_KEY
static ButtonEvent EncoderUp(2000);
static ButtonEvent EncoderDown(2000);
#endif

#ifdef USE_EKEY
static ButtonEvent ExtraKeyUp(2000);
static ButtonEvent ExtraKeyDown(2000);
#endif

#ifdef USE_PCF8574
PCF8574 pcf8574(0x20);
static ButtonEvent KeyStart(2000);
static ButtonEvent KeySelect(2000);
static ButtonEvent KeyA(2000);
static ButtonEvent KeyB(2000);
static ButtonEvent KeyUp(2000);
static ButtonEvent KeyDown(2000);
static ButtonEvent KeyLeft(2000);
static ButtonEvent KeyRight(2000);
#endif

static ButtonEvent EncoderPush(2000);
static volatile float EncoderDiff = 0;
static bool EncoderEnable = true;
Account *actEncoder;

void HAL::Encoder_SetEnable(bool en)
{
    EncoderEnable = en;
}

bool HAL::Encoder_GetIsPush()
{
    if (!EncoderEnable)
    {
        return false;
    }

    return (digitalRead(CONFIG_ENCODER_PUSH_PIN) == LOW);
}

static void Encoder_Key_Handler(ButtonEvent *btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED)
    {
        if (0)
        {
        }
        else if (btn == &EncoderPush)
        {
            HAL::enc_btn_first_push_flag = 1;
            Game_SetButtonState(GAME_BUTTON_A, true);
            Game_SetButtonState(GAME_BUTTON_B, true);
            HAL::Buzz_Tone(500, 20);
        }

#ifdef USE_KEY
        else if (btn == &EncoderDown)
        {
            EncoderDiff++;
        }
        else if (btn == &EncoderUp)
        {
            EncoderDiff--;
        }
#endif

#ifdef USE_PCF8574

        else if (btn == &KeyA)
        {
            Game_SetButtonState(GAME_BUTTON_A, true);
        }
        else if (btn == &KeyB)
        {
            Game_SetButtonState(GAME_BUTTON_B, true);
        }
        else if (btn == &KeyUp)
        {
            if (EncoderEnable)
            {
                EncoderDiff--;
            }
            Game_SetButtonState(GAME_BUTTON_UP, true);
        }
        else if (btn == &KeyDown)
        {
            if (EncoderEnable)
            {
                EncoderDiff++;
            }
            Game_SetButtonState(GAME_BUTTON_DOWN, true);
        }
        else if (btn == &KeyLeft)
        {
            Game_SetButtonState(GAME_BUTTON_LEFT, true);
        }
        else if (btn == &KeyRight)
        {
            Game_SetButtonState(GAME_BUTTON_RIGHT, true);
        }
#endif
    }
    else if (event == ButtonEvent::EVENT_RELEASED)
    {
        if (0)
        {
        }
        else if (btn == &EncoderPush)
        {
            Game_SetButtonState(GAME_BUTTON_A, false);
            Game_SetButtonState(GAME_BUTTON_B, false);
            Serial.println("EncoderPush EVENT_RELEASED");
            HAL::Buzz_Tone(700, 20);
        }

#ifdef USE_KEY
        else if (btn == &EncoderDown)
        {
        }
        else if (btn == &EncoderUp)
        {
        }
#endif
#ifdef USE_PCF8574
        else if (btn == &KeyA)
        {
            Game_SetButtonState(GAME_BUTTON_A, false);
        }
        else if (btn == &KeyB)
        {
            Game_SetButtonState(GAME_BUTTON_B, false);
        }
        else if (btn == &KeyUp)
        {
            key_value = LV_DIR_TOP;
            Game_SetButtonState(GAME_BUTTON_UP, false);
        }
        else if (btn == &KeyDown)
        {
            key_value = LV_DIR_BOTTOM;
            Game_SetButtonState(GAME_BUTTON_DOWN, false);
        }
        else if (btn == &KeyLeft)
        {
            key_value = LV_DIR_LEFT;
            Game_SetButtonState(GAME_BUTTON_LEFT, false);
        }
        else if (btn == &KeyRight)
        {
            key_value = LV_DIR_RIGHT;
            Game_SetButtonState(GAME_BUTTON_RIGHT, false);
        }
#endif
    }
    else if (event == ButtonEvent::EVENT_LONG_PRESSED)
    {
        if (btn == &EncoderPush)
        {
            gflag.enc_long_push_flag = 1;
            // HAL::Power_Shutdown();
            HAL::Audio_PlayMusic("Shutdown");
            Serial.println("Encoder btn EVENT_LONG_PRESSED");
        }
    }
}

#ifdef USE_EKEY
static void Encoder_ExtraKey_Handler(ButtonEvent *btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED)
    {
        if (btn == &ExtraKeyUp)
        {
            EncoderDiff--;
            // Game_SetButtonState(GAME_BUTTON_UP, true);
        }
        else if (btn == &ExtraKeyDown)
        {
            EncoderDiff++;
            // Game_SetButtonState(GAME_BUTTON_DOWN, true);
        }
    }
    else if (event == ButtonEvent::EVENT_RELEASED)
    {
        if (btn == &ExtraKeyUp)
        {
            // Game_SetButtonState(GAME_BUTTON_UP, false);
        }
        else if (btn == &ExtraKeyDown)
        {
            // Game_SetButtonState(GAME_BUTTON_DOWN, false);
        }
    }
    else if (event == ButtonEvent::EVENT_LONG_PRESSED)
    {
    }
}
#endif

#ifdef USE_ENC
static void Encoder_IrqHandler()
{
    if (!EncoderEnable)
    {
        return;
    }

    static volatile int count, countLast;
    static volatile uint8_t a0, b0;
    static volatile uint8_t ab0;
    uint8_t a = digitalRead(CONFIG_ENCODER_UP_PIN);
    uint8_t b = digitalRead(CONFIG_ENCODER_DOWN_PIN);
    if (a != a0)
    {
        a0 = a;
        if (b != b0)
        {
            b0 = b;
            count += ((a == b) ? 1 : -1);
            if ((a == b) != ab0)
            {
                count += ((a == b) ? 1 : -1);
            }
            ab0 = (a == b);
        }
    }

    if (count != countLast)
    {
        EncoderDiff += (count - countLast) > 0 ? 0.5 : -0.5;
        // EncoderDiff += (count - countLast) > 0 ? 1 : -1;
        countLast = count;
    }
}
#endif

void HAL::Encoder_Init()
{
#ifdef USE_PCF8574
    pcf8574.pinMode(P0, INPUT); // start
    pcf8574.pinMode(P1, INPUT); // select
    pcf8574.pinMode(P2, INPUT); // up
    pcf8574.pinMode(P3, INPUT); // down
    pcf8574.pinMode(P4, INPUT); // left
    pcf8574.pinMode(P5, INPUT); // right
    pcf8574.pinMode(P6, INPUT); // a
    pcf8574.pinMode(P7, INPUT); // b
    Serial.println(pcf8574.begin() ? "pcf8574 OK" : "pcf8574 KO");

    KeyStart.EventAttach(Encoder_Key_Handler);
    KeySelect.EventAttach(Encoder_Key_Handler);
    KeyUp.EventAttach(Encoder_Key_Handler);
    KeyDown.EventAttach(Encoder_Key_Handler);
    KeyLeft.EventAttach(Encoder_Key_Handler);
    KeyRight.EventAttach(Encoder_Key_Handler);
    KeyA.EventAttach(Encoder_Key_Handler);
    KeyB.EventAttach(Encoder_Key_Handler);
#endif

    pinMode(CONFIG_ENCODER_UP_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_DOWN_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_PULLUP);
    EncoderPush.EventAttach(Encoder_Key_Handler);

#ifdef USE_KEY
    EncoderDown.EventAttach(Encoder_Key_Handler);
    EncoderUp.EventAttach(Encoder_Key_Handler);
#endif

#ifdef USE_EKEY
    pinMode(CONFIG_BTN_A_PIN, INPUT_PULLUP);
    pinMode(CONFIG_BTN_B_PIN, INPUT_PULLUP);
    ExtraKeyUp.EventAttach(Encoder_ExtraKey_Handler);
    ExtraKeyDown.EventAttach(Encoder_ExtraKey_Handler);
#endif

#ifdef USE_ENC
    attachInterrupt(CONFIG_ENCODER_UP_PIN, Encoder_IrqHandler, CHANGE);
#endif

    actEncoder = new Account("Encoder", AccountSystem::Broker(), sizeof(int16_t), nullptr);
}

void HAL::Encoder_Update()
{

    EncoderPush.EventMonitor(Encoder_GetIsPush());

#ifdef USE_KEY
    EncoderUp.EventMonitor((digitalRead(CONFIG_ENCODER_UP_PIN) == LOW));
    EncoderDown.EventMonitor((digitalRead(CONFIG_ENCODER_DOWN_PIN) == LOW));
#endif

#ifdef USE_EKEY
    ExtraKeyUp.EventMonitor((digitalRead(CONFIG_BTN_A_PIN) == LOW));
    ExtraKeyDown.EventMonitor((digitalRead(CONFIG_BTN_B_PIN) == LOW));
#endif

#ifdef USE_PCF8574
    PCF8574::DigitalInput di = pcf8574.digitalReadAll();
    KeyStart.EventMonitor(!di.p0);
    KeySelect.EventMonitor(!di.p1);
    KeyUp.EventMonitor(!di.p2);
    KeyDown.EventMonitor(!di.p3);
    KeyLeft.EventMonitor(!di.p4);
    KeyRight.EventMonitor(!di.p5);
    KeyA.EventMonitor(!di.p6);
    KeyB.EventMonitor(!di.p7);
#endif
}

int16_t HAL::Encoder_GetDiff()
{
    // #ifdef USE_ENC
    //     int16_t diff = (EncoderDiff/2);
    //     #else
    //     int16_t diff = (EncoderDiff);
    //     #endif
    int16_t diff = (EncoderDiff);

    if (diff != 0)
    {
        EncoderDiff = 0;
        HAL::Buzz_Tone(300, 5);
        HAL::enc_btn_first_push_flag = 1;
        actEncoder->Commit((const void *)&diff, sizeof(int16_t));
        actEncoder->Publish();

        if (diff < 0)
        {
            Game_SetButtonState(GAME_BUTTON_LEFT, true);
            enc_btn_down_flag = 1;
            enc_dir_event_time = millis();
        }
        else
        {
            Game_SetButtonState(GAME_BUTTON_RIGHT, true);
            enc_btn_down_flag = 1;
            enc_dir_event_time = millis();
        }
    }

    return diff;
}
