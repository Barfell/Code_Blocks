To run examples, just copy paste files in Src folder.

Steps to enable debug print() using OpenOCD:

1) In Debug configuration > Startup Tab , add this :


monitor arm semihosting enable

2) And in Project, Properties, C/C++ Build, Settings, MCU GCC Linker, Miscellaneous, Linker flags, add this: 


-specs=nosys.specs -specs=nano.specs -specs=rdimon.specs -lc -lrdimon

3) And finally in your code, you have only to call the initialize_monitor_handles in the begin of the main routine:


 initialise_monitor_handles();
#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
  initialise_monitor_handles();
 
  printf("Hello !\n");
 
  HAL_Init();
  SystemClock_Config();
 
  puts("Check your openocd console.\n");
  printf("This works too\n");
  //……………
}