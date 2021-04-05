# ISSUE
For the second challenge, it is adviced to apply as the following:
1. Adding these three line to your continuous rtos function (void loop or any other task that you have added),

TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;  
TIMERG0.wdt_feed=1;  
TIMERG0.wdt_wprotect=0;  

2. Add this header

#include "soc/timer_group_struct.h"  
#include "soc/timer_group_reg.h"

For some reason, without the above applied, the task watchdog get triggered. It causes the esp32 keep resetting.  
Some said the problem is due to some code/function is making the CPU wait too long.  
The above alternative might not be the solution but it does counter the problem which believed due to the esp inner firmware.  
The solution is referred from the link below.
https://github.com/espressif/arduino-esp32/issues/922
