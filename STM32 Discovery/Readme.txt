Example source code for various STM32 MCUs.

Steps to enable debug print() using OpenOCD:

1) In Debug configuration > Startup tab , add:


monitor arm semihosting enable

2) And in Project > Properties > C/C++ Build > Settings > MCU GCC Linker > Miscellaneous > Linker flags, add: 


-specs=nosys.specs -specs=nano.specs -specs=rdimon.specs -lc -lrdimon

3) And finally in main.c, you have to call initialise_monitor_handles() at the beginning of main() as shown:


#include <stdio.h>
#include <stdlib.h>

extern void initialise_monitor_handles(void);                 //might not be needed

int main(void) 
{
  initialise_monitor_handles();                        //to enable debug printf()
 
  printf("Hello !\n");
 
  HAL_Init();
  SystemClock_Config();
 
  printf("Check your openocd console.\n");
}