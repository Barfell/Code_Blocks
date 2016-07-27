1)Put the implementation of CDC_Receive_FS() in usbd_cdc_if.c in the appropriate User Code section. Also remove "static" from it's declaration to allow it to be accessible in main.c and change it's return type to "uint8_t" instead of 
"int8_t".

2)Cut the prototype of CDC_Receive_FS() from usbd_cdc_if.c and put it in usbd_cdc_if.h in the appropriate User Code section. Also remove "static" from it's declaration to allow it to be accessible in main.c and change it's return type to "uint8_t" instead of 
"int8_t".