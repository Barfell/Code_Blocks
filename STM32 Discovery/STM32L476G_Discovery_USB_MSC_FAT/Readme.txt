Example source code for STM32L476G (Discovery) for using a filesystem.

1) Access the on-board 16MB SPI NOR Flash through USB. The memory can be accessed internally by the MCU as well by mounting the FAT filesystem.

2) If USB VBUS is to be used to detect USB connection/disconnection with host, then ensure that PC9 is not enabled as the OTG Power Switch and turned on. If that's the case, then the USB VBUS line will be powered internally by the MCU.