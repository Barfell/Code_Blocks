#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

//ISR for key interrupts
static void key_interrupt_handler(void *context, alt_u32 id)
{
    volatile int* edge_capture_ptr=(volatile int*) context;
    *edge_capture_ptr=IORD_ALTERA_AVALON_PIO_EDGE_CAP(DE2_PIO_KEYS4_BASE);     //store edge value
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(DE2_PIO_KEYS4_BASE, 0);           //reset edge cap register value
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(DE2_PIO_KEYS4_BASE, 0xF);         //clear interrupt flag
    printf("Interrupt occurred: %d\n", *edge_capture_ptr);          //alert the user
}
volatile int edge_capture;      //edge values stored here
int main()
{
//************************************************I/O*************************************************
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_REDLED18_BASE, 0x3FFFF);   //turn on all RED LEDs on DE2
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_REDLED18_BASE, 0x00000);   //turn off all RED LEDs on DE2
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_GREENLED9_BASE, 0xFF);   //turn on all GREEN LEDs on DE2
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_GREENLED9_BASE, 0x00);   //turn off all GREEN LEDs on DE2
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_REDLED18_BASE, 0x00001);   //turn on RED LED0 on DE2
//  while (1)
//  {
//    IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_GREENLED9_BASE, IORD_ALTERA_AVALON_PIO_DATA(DE2_PIO_KEYS4_BASE));   //read data from pushbuttons and send to green LEDS
//    IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_REDLED18_BASE, IORD_ALTERA_AVALON_PIO_DATA(DE2_PIO_TOGGLES18_BASE));  //read data from toggle buttons and send them to red LEDs
//  }

//*******************************************7-seg displays********************************************
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF80);      //turn off HEX 1-3, use HIGH28 for HEX-4 and above
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFFC0);      //0- 100 0000
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFFF9);      //1- 111 1001
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFFA4);      //2- 010 0100
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFFB0);      //3- 011 0000
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF99);      //4- 001 1001
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF92);      //5- 001 0010
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF82);      //6- 000 0010
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFFD8);      //7- 101 1000
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF80);      //8- 000 0000
//  IOWR_ALTERA_AVALON_PIO_DATA(DE2_PIO_HEX_LOW28_BASE, 0x0FFFFF90);      //9- 001 0000

//***********************************************INTERRUPTS************************************************
//    //register ISR with interrupt handler
//    alt_irq_register(DE2_PIO_KEYS4_IRQ, (void*) &edge_capture, key_interrupt_handler);
//    /* Enable all 4 button interrupts. */
//    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(DE2_PIO_KEYS4_BASE, 0xF);   //0x08-> Key 4 interrupt enabled, 0x04-> Key 3 interrupt enabled, 0x02-> Key 2 interrupt enabled, 0x01 Key 1 interrupt enabled
//    /* Reset the edge capture register. */
//    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(DE2_PIO_KEYS4_BASE, 0x0);
//
//  while(1);
  return 0;
}