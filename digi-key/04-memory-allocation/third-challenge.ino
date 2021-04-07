#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t input_limit = 10;

// Globals
static char *msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;

// Read message from Serial buffer
void readSerial(void *parameters) {

  char c;
  char input[input_limit];
  uint8_t idx = 0;

  // Clear whole buffer (fill all elements with '0')
  memset(input, 0, input_limit);
  
  // Loop forever
  while (1) {

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      // Store received character to buffer if not over buffer limit
      if (idx < input_limit + 1) {
        input[idx] = c;
        //Serial.println(input[idx]);
        idx++;
      }

      // Create a message buffer for print task
      if (c == '\n') {

        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        input[idx - 1] = '\0';

        // Try to allocate memory and copy over message. If message buffer is
        // still in use, ignore the entire message.
        if (msg_flag == 0) {
          msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));

          // If malloc returns 0 (out of memory), throw an error and reset
          configASSERT(msg_ptr);

          // Copy message
          memcpy(msg_ptr, input, idx);

          // Notify other task that message is ready
          msg_flag = 1;
        }

        // Reset receive buffer and index counter
        memset(input, 0, input_limit);
        idx = 0;
      }
    }
  }
}

// Print message whenever flag is set and free buffer
void printMessage(void *parameters) {
  while (1) {

    // Wait for flag to be set and print message
    if (msg_flag == 1) {
      Serial.println(msg_ptr);

      // Give amount of free heap memory
      //Serial.print("Free heap (bytes): ");
      //Serial.println(xPortGetFreeHeapSize());

      // Free buffer, set pointer to null, and clear flag
      vPortFree(msg_ptr);
      msg_ptr = NULL;
      msg_flag = 0;
    }
  }
}

void setup() {

  Serial.begin(115200);

  vTaskDelay(2000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Heap Demo---");
  Serial.print("Limit printed input: ");
  Serial.println(input_limit);
  Serial.println("Enter a string");

  // Start Serial receive task
  xTaskCreatePinnedToCore(readSerial,
                          "Read Serial",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  // Start Serial print task
  xTaskCreatePinnedToCore(printMessage,
                          "Print Message",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
  
  vTaskDelete(NULL);
}

void loop() {
}
