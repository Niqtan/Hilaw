// Libraries

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_IL9341.h>

#include "esp_camera.h"

//Define GPIOs
//MCU Pins

#define SHUTTER_BUTTON 0

// Camera (I2C)

#define SCL 22 
#define SDA 21
#define PWDN 2
#define VSYNC 23
#define HREF 25
#define PCLK 26 
#define XCLK 19
#define RST 18
#define D0 17
#define D1 16
#define D2 15
#define D3 14
#define D4 13
#define D5 12
#define D6 5
#define D7 4


//Thermal Printer (TTL)
#define RX 3
#define TX 1

// TFT Display (SPI)
#define MISO 32
#define MOSI 33
#define SCK 34
#define CS 35
#define DC 27
#define RST 0

const int SPIMAXFREQ = 3000000

Adafruit_ILI9341 tft = Adafruit_ILI9341(CS, DC, RST);
 

/*
Okay  so here's how I think we're going to do it:
1. We want to be able to configure the camera first using the library esp_camera.h
2. Afterwards, we want to be able to get a RGBDepthMap of the output using  a function from the Adafruit GFX (RGB bit map)
3. Pass the values of that in the TFT display
*/

void setup() {
  //Initialize all communication protocols here
  Serial.begin(115200);

  camera_config_t camera_config = {
    .pin_d0 = D0,
    .pin_d1 = D1,
    .pin_d2 = D2,
    .pin_d3 = D3,
    .pin_d4 = D4,
    .pin_d5 = D5,
    .pin_d6 = D6,
    .pin_d7 = D7,
    .pin_reset = RST,
    .pin_pwdn = PWDN,
    .pin_xclk = XCLK,
    .pin_pclk = PCLK,
    .pin_vsync = VSYNC,
    .pin_href = HREF,
    .pin_sscb_sda = SDA,
    .pin_sscb_scl = SCL,
    .xclk_freq_hz = 20000000,
    .pixel_format = PIXFORMAT_RGB565,
    .frame_size = FRAMESIZE_QVGA,
    .config_fb_count = 1,

  };

  esp_err_t ret_val = esp_camera_init(&camera_config);
  if (ret_val != ESP_OK) {
    Serial.printf("Camera did not initialize properly with erorr 0x%x", ret_val);
    return;
  }

  Serial.printf("Camera initialized properly.")
  /* Before intializing SPI, you must have these variables:
  - The ILI9341 is stable up to 30MHz
  - 
  */
  Wire.begin();

  tft.begin()
  tft.setRotation(1)

}

void loop() {
    // Loop to check if the shutter button has been pressed
  if (SHUTTER_BUTTON == 1) {
    camera_fb_t *fb = esp_camera_fb_get;
    if (!fb) {
      Serial.printf("Picture was not taken properly.");
      return;
    }
  }

  //Display the output on the TFT display
  
}
