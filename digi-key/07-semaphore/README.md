# Demo Counting Semaphore

<img src="https://user-images.githubusercontent.com/76240694/117097342-efd33880-ad9d-11eb-848d-ce4f2cabaa56.png" width="500">

# Solution Demo Counting Semaphore

### declare these lines as critical section using Mutex (so that, it will be prioritized)

`if (xSemaphoreTake(mutex, 0) == pdTRUE) {`  
`// Print out message contents`  
`Serial.print("Received: ");`  
`Serial.print(msg.body);`  
`Serial.print(" | len: ");`  
`Serial.println(msg.len);`  
`xSemaphoreGive(mutex);`  
`}`  

<img src="https://user-images.githubusercontent.com/76240694/117097558-928bb700-ad9e-11eb-86d1-eeac8cd299ab.png" width="500">

