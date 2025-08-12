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
#define PWDN 18
#define VSYNC 26
#define HREF 25
#define PCLK 19
#define RST 23
#define D0 17
#define D1 13
#define D2 16
#define D3 12
#define D4 15
#define D5 4
#define D6 14
#define D7 2


//Thermal Printer (TTL)
#define RX 3
#define TX 1

// TFT Display (SPI)
#define MISO 35
#define MOSI 33
#define SCK 34
#define CS 27
#define DC 32
#define RST 5

const int SPIMAXFREQ = 3000000

Adafruit_ILI9341 tft = Adafruit_ILI9341(CS, DC, RST);
 

/*
Okay  so here's how I think we're going to do it:
1. We want to be able to configure the camera first using the library esp_camera.h - DONE
2. Afterwards, we want to be able to get a RGBDepthMap of the output using  a function from the Adafruit GFX (RGB bit map)
3. Pass the values of that in the TFT display
*/

void setup() {
  //Initialize all communication protocols here
  Wire.begin();
  SPI.begin();
  Serial.begin(115200);

  //Configure the camera settings
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
    .jpeg_quality = 12,
    .fb_count = 1,

  }; 
  
  //Initialize the camera using the settings 
  esp_err_t ret_val = esp_camera_init(&camera_config);
  if (ret_val != ESP_OK) {
    Serial.printf("Camera did not initialize properly with error 0x%x", ret_val);
    return;
  }

  Serial.printf("Camera initialized properly.");

  //Begin communication with the TFT
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

}

void loop() {
  //Display the current RGB depth map in order to preview the photo

  
  // Loop to check if the shutter button has been pressed
  if (SHUTTER_BUTTON == 1) {
    Serial.println("Shutter button pressed!")
    Serial.println("Taking a picture...")
    camera_fb_t *fb = esp_camera_fb_get;
    if (!fb) {
      Serial.printf("Picture was not taken properly.");
      return;
    }
    Serial.println("Photo captured successfully!")

    esp_camera_fb_return(fb)

    while *(SHUTTER_BUTTON == 1) {
      delay(10);
    }

    //Print out the photo using the thermal printer

    Serial.println("Ready for next photo!");
  }

  delay(50);
  //Display the output on the TFT display
  
}

void setup_video_stream() {
  
}

void get_RGB_Data() {
  Serial.println("Getting the RGB Bit Depth Map data...")

  camera_fb_t *fb = esp_camera_fb_get;
    if (!fb) {
      Serial.printf("Picture was not taken properly.");
      return;
    }

    Serial.println("Checking if format is RGB565...")
    //Utilizing the frame buffer structure, we are able to get data about each image which makes up a video
  if (fb->format == PIXFORMAT_RGB565) {
    uint16_t *RGB565_data = (uint16_t) *fb->buf;



  }

  esp_camera_fb_return(fb)

}
