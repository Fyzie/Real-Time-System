# Demo Counting Semaphore

<img src="https://user-images.githubusercontent.com/76240694/117097342-efd33880-ad9d-11eb-848d-ce4f2cabaa56.png" width="500">

# Solution Demo Counting Semaphore

### using Mutex to declare critical section(so that, required lines will be prioritized)  

`xSemaphoreTake(mutex, portMAX_DELAY);`  
 ` // Print out message contents`  
 ` Serial.print("Received: ");`  
 ` Serial.print(msg.body);`  
 ` Serial.print(" | len: ");`  
 ` Serial.println(msg.len);`  
 ` xSemaphoreGive(mutex);`  

<img src="https://user-images.githubusercontent.com/76240694/117101194-3c237600-ada8-11eb-927b-3d0b01dceeef.png" width="500">

