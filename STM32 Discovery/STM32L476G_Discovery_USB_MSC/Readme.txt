Example source code for STM32L476G (Discovery) for creating a USB MSC device.

1) Access the on-board 16MB SPI NOR Flash through USB.

2) If USB VBUS is to be used to detect USB connection/disconnection with host, then ensure that PC9 is not enabled as the OTG Power Switch and turned on. If that's the case, then the USB VBUS line will be powered internally by the MCU.