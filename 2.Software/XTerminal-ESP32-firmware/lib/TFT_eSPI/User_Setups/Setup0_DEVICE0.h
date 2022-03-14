#if defined(USE_ST7789) 
#define ST7789_DRIVER
#elif defined(USE_ILI9341) 
#define ILI9341_DRIVER
#endif

#if defined(TFT240X320)
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#elif defined(TFT240X240)
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#elif defined(TFT240X280)
#define TFT_WIDTH 240
#define TFT_HEIGHT 280
#endif
// #define TFT_WIDTH 240
// #define TFT_HEIGHT 280
#define TFT_RGB_ORDER TFT_BGR

#if defined(DEVICE0)
#define TFT_MISO -1 
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    -1
#define TFT_DC    2
#define TFT_RST   4
#define TFT_INVERSION_ON
#elif defined(DEVICE3)
#define TFT_MISO -1
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    5
#define TFT_DC    12
#define TFT_RST   -1
#define TFT_INVERSION_OFF
#endif

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
#define SMOOTH_FONT

#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
