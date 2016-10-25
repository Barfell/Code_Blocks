Example source code for STM32L476G (Discovery) for creating a USB CDC device.

1)Put the implementation of CDC_Receive_FS() in Src/usbd_cdc_if.c in the appropriate User Code section. Also remove "static" from it's declaration to allow it to be accessible in main.c and change it's return type to "uint8_t" instead of 
"int8_t".

2)Cut the prototype of CDC_Receive_FS() from Src/usbd_cdc_if.c and put it in Inc/usbd_cdc_if.h in the appropriate User Code section. Also remove "static" from it's declaration to allow it to be accessible in main.c and change it's return type to "uint8_t" instead of 
"int8_t".

3) If USB VBUS is to be used to detect USB connection/disconnection with host, then ensure that PC9 is not enabled as the OTG Power Switch and turned on. If that's the case, then the USB VBUS line will be powered internally by the MCU.