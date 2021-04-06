#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

void testTask(void *parameter) {
  while (1) {
    int a = 1;
    int b[100];
    int *ptr;

    for (int i = 0; i < 100; i++) {
      b[i] = a + 1;
    }

    //print remaining stack mem
    Serial.print("High water mark (words): ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    //print free heap mem before malloc
    Serial.print("Heap before malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
    ptr = (int*)pvPortMalloc(1024 * sizeof(int));

    //check malloc output (prevent heap overflow)
    if (ptr == NULL) {
      Serial.println("Not enough heap.");
      vPortFree(NULL);
    } else {

      //fill up the mem
      for (int i = 0; i < 1024; i++) {
        ptr[i] = 3;
      }
    }

    //print free heap mem after malloc
    Serial.print("Heap after malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());

    //vPortFree(ptr); //to free up mem

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {

  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Memory Demo---");

  xTaskCreatePinnedToCore(testTask,
                          "Test Task",
                          1500,   // stack size
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  vTaskDelete(NULL);
}

void loop() {

}
