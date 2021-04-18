#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <ESP32Servo.h>
#include <stdlib.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t buf_len = 20;

// Servo
Servo myservo;
static int range = 0;    // range rotation
static int pos = 180;    // intial range

void controlServo(void *parameter) {
  while (1) {
    for (pos = 0; pos <= range; pos++) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = range; pos >= 0; pos--) { 
    myservo.write(pos);             
    delay(15);                      
  }
  }
}

//Read from serial terminal
void readSerial(void *parameters) {

  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);

  // Loop forever
  while (1) {

    TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed = 1;
    TIMERG0.wdt_wprotect = 0;

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      if (c == '\n') {
        range = atoi(buf);
        Serial.print("Updated range rotation: ");
        Serial.println(range);
        memset(buf, 0, buf_len);
        idx = 0;
      } else {

        if (idx < buf_len - 1) {
          buf[idx] = c;
          idx++;
        }
      }
    }
  }
}

void setup() {
  myservo.attach(13, 500, 2400);

  // Configure serial and wait a second
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Enter an angle position.");

  // Start blink task
  xTaskCreate(  // Use xTaskCreate() in vanilla FreeRTOS
    controlServo,      // Function to be called
    "Control Servo",   // Name of task
    1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,           // Parameter to pass
    1,              // Task priority
    NULL);       // Run on one core for demo purposes (ESP32 only)

  // Start serial read task
  xTaskCreate(  // Use xTaskCreate() in vanilla FreeRTOS
    readSerial,     // Function to be called
    "Read Serial",  // Name of task
    1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,           // Parameter to pass
    1,              // Task priority (must be same to prevent lockup)
    NULL);       // Run on one core for demo purposes (ESP32 only)

  vTaskDelete(NULL);
}

void loop() {

}
