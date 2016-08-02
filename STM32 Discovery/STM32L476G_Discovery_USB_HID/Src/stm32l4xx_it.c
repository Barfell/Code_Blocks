/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "stm32l4xx_it.h"

/* USER CODE BEGIN 0 */
#include "usbd_def.h"

#define CURSOR_STEP     5

uint8_t HID_Buffer[4];
uint32_t joyReady=0;
extern USBD_HandleTypeDef hUsbDeviceFS;

uint16_t BSP_JOY_GetState(void);                      //read joystick
static void GetPointerData(uint8_t *pbuf);            //decode joystick input
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  static uint32_t counter=0;
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  GetPointerData(HID_Buffer);         //get user input

  if (joyReady == 1)                  //input received
  {
    /* check Joystick state every polling interval (10ms); standard for mice */
    if (counter++ == USBD_HID_GetPollingInterval(&hUsbDeviceFS))
    {
      /* send data though IN endpoint*/
      if((HID_Buffer[1] != 0) || (HID_Buffer[2] != 0))
      {
        USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
      }
      counter=0;
    }
  }
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USB OTG FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/**
  * @brief  Decode joystick data
  * @param  pbuf: Pointer to report
  * @retval None
  */
static void GetPointerData(uint8_t *pbuf)
{
  int8_t  x = 0, y = 0 ;

  switch(BSP_JOY_GetState())
  {
    case JOY_LEFT_Pin:
      x -= CURSOR_STEP;
      break;

    case JOY_RIGHT_Pin:
      x += CURSOR_STEP;
      break;

    case JOY_UP_Pin:
      y -= CURSOR_STEP;
      break;

    case JOY_DOWN_Pin:
      y += CURSOR_STEP;
      break;

    default:
	  break;
  }

  pbuf[0] = 0;
  pbuf[1] = x;
  pbuf[2] = y;
  pbuf[3] = 0;
}

/**
  * @brief  Read joystick input
  * @param  none
  * @retval Joystick button pressed
  */
uint16_t BSP_JOY_GetState(void)
{
  uint16_t joystick_pin[5]={JOY_LEFT_Pin, JOY_RIGHT_Pin, JOY_UP_Pin, JOY_DOWN_Pin, JOY_CENTER_Pin};
  uint32_t i;

  for(i=0; i<5; i++)
  {
    if (HAL_GPIO_ReadPin(GPIOA, joystick_pin[i])==GPIO_PIN_SET)
	{
      joyReady=1;
	  /* Return Code Joystick key pressed */
	  return joystick_pin[i];
	}
  }

  joyReady=0;
  return 0;           //no button pressed
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
