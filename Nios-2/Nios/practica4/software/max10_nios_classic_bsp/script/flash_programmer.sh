#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting Binary File: C:\FPGAs\practica4\software\max10_nios_classic_bsp\flash\max10_nios_classic_flash.flash to: "..\flash/max10_nios_classic.flash.flash.flash"
#
bin2flash --input="C:/FPGAs/practica4/software/max10_nios_classic_bsp/flash/max10_nios_classic_flash.flash" --output="../flash/max10_nios_classic.flash.flash.flash" --location=0x0 

#
# Programming File: "..\flash/max10_nios_classic.flash.flash.flash" To Device: flash
#
nios2-flash-programmer "../flash/max10_nios_classic.flash.flash.flash" --base=0x1001000 --sidp=0x1002040 --id=0x0 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

