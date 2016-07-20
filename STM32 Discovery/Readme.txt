To run examples, just copy paste files in Src folder.

Steps to enable debug print() using OpenOCD:

1) In Debug configuration > Startup tab , add:


monitor arm semihosting enable

2) And in Project > Properties > C/C++ Build > Settings > MCU GCC Linker > Miscellaneous > Linker flags, add: 


-specs=nosys.specs -specs=nano.specs -specs=rdimon.specs -lc -lrdimon

3) And finally in main.c, you have to call initialize_monitor_handles() at the beginning of main() as shown:


#include <stdio.h>
#include <stdlib.h>
 
int main(void) 
{
  initialise_monitor_handles();
 
  printf("Hello !\n");
 
  HAL_Init();
  SystemClock_Config();
 
  printf("Check your openocd console.\n");
}