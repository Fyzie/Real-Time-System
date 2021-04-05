<details><summary>Blinky 2 LEDs</summary>
<p>

<img src="media/2leds-circuit.jpeg" width="300" height="300">  
  
<details><summary>Issue</summary>
<p>  
  
1. Instead of applying xTaskCreatePinnedtoCore, do only apply xTaskCreate.  

2. If builtin LED is used, make sure that the led rate from both tasks does not have same interval.  
Correct: 500, 300  
Wrong: 500, 1000  

</p>
</details>
