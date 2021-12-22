// Based of the example sketch for Adafruit_ImageReader test for Adafruit ILI9341 TFT Shield for Arduino.
// Demonstrates loading images from SD card or flash memory to the screen,
// to RAM, and how to query image file dimensions.
// Requires BMP files in root directory of SD card:
// Uses SPI interface for image display.
// Personal Electronic Badge, ver. 1.0

#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ILI9341.h>     // Hardware-specific library
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Image-reading functions

// Comment out the next line to load from SPI/QSPI flash instead of SD card:
#define USE_SD_CARD

// TFT display and SD card share the hardware SPI interface, using
// 'select' pins for each to identify the active device on the bus.

#define SD_CS   4 // SD card select pin
#define TFT_CS 10 // TFT select pin
#define TFT_DC  9 // TFT display/command pin

#if defined(USE_SD_CARD)
  SdFat                SD;         // SD card filesystem
  Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys
#else
  // SPI or QSPI flash filesystem (i.e. CIRCUITPY drive)
  #if defined(__SAMD51__) || defined(NRF52840_XXAA)
    Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS,
      PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
  #else
    #if (SPI_INTERFACES_COUNT == 1)
      Adafruit_FlashTransport_SPI flashTransport(SS, &SPI);
    #else
      Adafruit_FlashTransport_SPI flashTransport(SS1, &SPI1);
    #endif
  #endif
  Adafruit_SPIFlash    flash(&flashTransport);
  FatFileSystem        filesys;
  Adafruit_ImageReader reader(filesys); // Image-reader, pass in flash filesys
#endif

Adafruit_ILI9341     tft    = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_Image       img;        // An image loaded into RAM
int32_t              width  = 0, // BMP image dimensions
                     height = 0;

void setup(void) {

  ImageReturnCode stat; // Status from image-reading functions

  Serial.begin(9600);
#if !defined(ESP32)
  while(!Serial);       // Wait for Serial Monitor before continuing
#endif

  tft.begin();          // Initialize screen

  // The Adafruit_ImageReader constructor call (above, before setup())
  // accepts an uninitialized SdFat or FatFileSystem object. This MUST
  // BE INITIALIZED before using any of the image reader functions!
  Serial.print(F("Initializing filesystem..."));
#if defined(USE_SD_CARD)
  // SD card is pretty straightforward, a single call...
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) { // ESP32 requires 25 MHz limit
    Serial.println(F("SD begin() failed"));
    for(;;); // Fatal error, do not continue
  }
#else
  // SPI or QSPI flash requires two steps, one to access the bare flash
  // memory itself, then the second to access the filesystem within...
  if(!flash.begin()) {
    Serial.println(F("flash begin() failed"));
    for(;;);
  }
  if(!filesys.begin(&flash)) {
    Serial.println(F("filesys begin() failed"));
    for(;;);
  }
#endif
  Serial.println(F("OK!"));

  // Fill screen blue. Not a required step, this just shows that we're
  // successfully communicating with the screen.
  tft.fillScreen(ILI9341_BLUE);

  // Load full-screen BMP file 'purple.bmp' at position (0,0) (top left).
  // Notice the 'reader' object performs this, with 'tft' as an argument.
  Serial.print(F("Loading welcome.bmp to screen..."));
  stat = reader.drawBMP("/welcome.bmp", tft, 0, 0);
  reader.printStatus(stat);   // How'd we do?

  delay(2000); // Pause 2 seconds before moving on to loop()
  
}

void loop() {

Serial.print(F("Loading Badge1.bmp to screen..."));
//tft.setRotation(1);    // Set rotation
reader.drawBMP("/Badge1.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(2000); // Pause 2 sec.

Serial.print(F("Loading Badge2.bmp to screen..."));
reader.drawBMP("/Badge2.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(2000); // Pause 2 sec.

Serial.print(F("Loading Badge1.bmp to screen..."));
//tft.setRotation(1);    // Set rotation
reader.drawBMP("/Badge1.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(2000); // Pause 2 sec.

Serial.print(F("Loading Badge2.bmp to screen..."));
reader.drawBMP("/Badge2.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(2000); // Pause 2 sec.

Serial.print(F("Loading Badge3.bmp to screen..."));
reader.drawBMP("/Badge3.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(3000); // Pause 3 sec.

Serial.print(F("Loading Badge4.bmp to screen..."));
reader.drawBMP("/Badge4.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(3000); // Pause 3 sec.

Serial.print(F("Loading Badge3.bmp to screen..."));
reader.drawBMP("/Badge3.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(3000); // Pause 3 sec.

Serial.print(F("Loading Badge4.bmp to screen..."));
reader.drawBMP("/Badge4.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(3000); // Pause 3 sec.

Serial.print(F("Loading Badge5.bmp to screen..."));
reader.drawBMP("/Badge5.bmp", tft, 0, 0);
//reader.printStatus(stat);   // How'd we do?

delay(4000); // Pause 4 sec.

}
