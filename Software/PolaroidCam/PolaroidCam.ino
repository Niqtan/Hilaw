// Libraries

#include <SPI.h>
#include <Wire.h>

//TFT Display

#include <Adafruit_GFX.h>
#include <Adafruit_IL9341.h>

//Camera
#include "esp_camera.h"

// Thermal Printing

#include "TPrinter.h"
#include <HardwareSerial.h>


/*
**********************
*****Define GPIOs*****
**********************
*/



//MCU Pins

#define SHUTTER_BUTTON 0

// Camera (I2C)

#define SCL 22 
#define SDA 21
#define PWDN 18

#define PCLK 19
#define CAM_RST 23
#define D0 36
#define D1 13
#define D2 39
#define D3 12
#define D4 15
#define D5 4
#define D6 14
#define D7 2


//Thermal Printer (TTL) (Serial number 2)
#define RX 25
#define TX 26

// TFT Display (SPI)
#define MISO 17
#define MOSI 33
#define SCK 16
#define CS 27
#define DC 32
#define TFT_RST 5

// Input Only pins
#define VSYNC 35
#define HREF 34

const int printerBaudrate = 9600;
const int SPIMAXFREQ = 3000000;
const uint16_t display_width = 240;
const uint16_t display_height = 320;

uint16_t *RGB565_data = NULL;
uint8_t *bitmap = NULL;

HardwareSerial printerSerial(2);
Tprinter myPrinter(&printerSerial, printerBaudrate);

Adafruit_ILI9341 tft = Adafruit_ILI9341(CS, DC, TFT_RST);

void setup() {
  //Initialize all communication protocols here
  micros();
  Wire.begin();
  SPI.begin();
  Serial.begin(115200);

  //Reset the camera first
  pinMode(CAM_RST, OUTPUT);
  digitalWrite(CAM_RST, HIGH);

  // Reset TFT as well
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, HIGH);
  
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
    .pin_reset = CAM_RST,
    .pin_pwdn = PWDN,
    .pin_xclk = -1,
    .pin_pclk = PCLK,
    .pin_vsync = VSYNC,
    .pin_href = HREF,
    .pin_sscb_sda = SDA,
    .pin_sscb_scl = SCL,
    .xclk_freq_hz = 0,                                                                                                   
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

  printerSerial.begin(printerBaudrate, SERIAL_8N1, RX, TX);
  myPrinter.begin();

  //Button
  pinMode(SHUTTER_BUTTON, INPUT);
}

void loop() {
  //Display the current RGB depth map in order to preview the photo
  camera_fb_t *final_fb = NULL;
  final_fb = stream_video();
  
  // Loop to check if the shutter button has been pressed
  if (digitalRead(SHUTTER_BUTTON) == 1) {
    Serial.println("Shutter button pressed!");
    Serial.println("Taking a picture...");

    while (digitalRead(SHUTTER_BUTTON) == 1) {
      delay(10);
    }
    
    displayImage(final_fb);
    Serial.println("Photo captured successfully!");

    //Print out the photo using the thermal printer

    uint16_t picture_width = 384; // 384 pixels per line
    uint16_t picture_height = 288; // Makes it so that it looks shart wiuthout being huge 

    bitmap = convertToBitmap(RGB565_data, picture_width, picture_height);
    printBitmap(bitmap, picture_width, picture_height, 1, true);
    Serial.println("Photo printed!");
    delay(100);

    free(bitmap);
    esp_camera_fb_return(final_fb);
    Serial.println("Ready for next photo!");
  }

  delay(50);
  
}

uint8_t* convertToBitmap(uint16_t *RGB565_data, uint16_t picture_width, uint16_t picture_height) {
  /* To convert from RGB565 data to bitmap, remember that RGB565 means: 
  5 bits represent red, 6 bits represent green, and 5 bits represent blue.
  This means each pixel is stored as a 2-byte value.
  */
  // We're gonna go for a 1-bit-per-pixel bitmap (monochrome)

  uint16_t rowBytes = (picture_width + 7) / 8;
  uint8_t *bitmap = (uint8_t*) malloc(rowBytes * picture_height); 

  // Go over each pixel in the picture
  for (uint16_t y = 0; y < picture_height; y++) {
    for (uint16_t x = 0; x < picture_width; x++) {
      uint16_t *pixel = RGB565_data[y * picture_width + x];

      // Right now, each pixel is monochrome (1-bit). 
      // Hence, we need to convert it back to the original 565 format
      uint8_t r = (pixel >> 11) & 0x1F;
      uint8_t g = (pixel >> 5) & 0x3F;
      uint8_t b = pixel & 0x1F;

      // After conversion, measure the luminance (brightness)
      r = (r * 255) / 31
      g = (g * 255) / 63
      b = (b * 255) / 31

      uint8_t brightness = (r * 30 + g * 59 + b * 11) / 100;
      
      uint16_t byteIndex = y * rowBytes + (x / 8);
      uint8_t bitIndex = 7 -  (x % 8);

      // black
      if (brightness < 128) {
        bitmap[byteIndex] |= (1 << bitIndex);
      }

      // white
      else {
        bitmap[byteIndex] &= ~(1 << bitIndex) ;
      }
    }
  }

  return bitmap;
}

camera_fb_t* displayImage(fb) {

  uint16_t w = fb->width;
  uint16_t h = fb->height;

  //Calculate center image
  uint16_t x = (display_width - w) / 2 
  uint16_t y = (display_height - h) / 2

  Serial.println("Displaying the image...");
  tft.drawRGBBitmap(x, y, RGB565_data, w, h)

  Serial.println("Do u like it?");

  delay(2000);

  return fb;
}

// Function for converting the current format to a RGB Bit Depth Map for the TFT Display
camera_fb_t* stream_video() {
  Serial.println("Getting the RGB Bit Depth Map data...");

  camera_fb_t *last_fb = NULL;

  while (digitalRead(SHUTTER_BUTTON) == 0) {
  
   camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.printf("Picture was not taken properly.");
      return;
  }

  uint16_t w = fb->width;
  uint16_t h = fb->height;

  //Calculate center image
  uint16_t x = (display_width - w) / 2 
  uint16_t y = (display_height - h) / 2
  
  Serial.println("Checking if format is RGB565...")
    //Utilizing the frame buffer structure, we are able to get data about each image which makes up a video
  if (fb->format == PIXFORMAT_RGB565) {
    RGB565_data = (uint16_t *) fb->buf;

    Serial.print("Image is in RGB565 format!");
    
    //Displaying the image
    tft.drawRGBBitmap(x, y, RGB565_data, w, h)
  }
  else {
    Serial.println("Image is not in RGB565 format")

    // Reconfigure the camera

    sensor_t *reconfigure = esp_camera_sensor_get();
    if (reconfigure) {
      reconfigure->set_pixformat(reconfigure, PIXFORMAT_RGB565);
      Seiral.println("Reconfigured to a RGB565 format!");
    }

    Serial.println("Skipping the current frame for now. Will be RGB565 next frame!");
  }

  //Keep getting a new frame
  esp_camera_fb_return(fb);
  delay(33); //~30 FPS
  
  }
  
  //If button pressed, return.
  final_fb = esp_camera_fb_get();
  return final_fb;

}
