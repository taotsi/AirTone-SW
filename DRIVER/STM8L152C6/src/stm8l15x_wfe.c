/**
  ******************************************************************************
  * @file    stm8l15x_wfe.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Wait for Event (WFE) peripheral:           
  *           - WFE Source configuration and management
  *             
  *  @verbatim
  *               
  *          ===================================================================
  *                               WFE specific features
  *          ===================================================================
  *
  *           Wait for event mode (WFE) stops the CPU but allows the other peripherals
  *           and interrupt controller to continue running.
  *           This mode is entered from Run mode by executing a WFE instruction.
  *           Peripheral events can be generated by the timers, serial interfaces, 
  *           DMA controller, comparators and I/O ports. 
  *           These are enabled by using the WFE_WakeUpSourceEventCmd() function.
  *           
  *           When a peripheral event is enabled, the corresponding interrupts are 
  *           not served and you have to clear the corresponding flag status.
  *           
  *           There are two ways to wake up the CPU from WFE mode:
  *            - Interrupts: When an interrupt occurs, the CPU wakes up from WFE mode
  *              serves the interrupt then goes back to WFE mode.
  *            - Wake up event: when a wake up event occurs, the CPU wakes up and 
  *              resumes processing, in this case and to save time and power consumption
  *              there is no context save/restore activity.            
  *                          
  *
  *  @endverbatim
  *                 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_wfe.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */
  
/** @defgroup WFE 
  * @brief WFE driver modules
  * @{
  */
   
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup WFE_Private_Functions
  * @{
  */

/** @defgroup WFE_Group1 WFE Source configuration and management functions 
 *  @brief   WFE Source configuration and management functions  
 *
@verbatim   
 ===============================================================================
               WFE Source configuration and management functions 
 ===============================================================================  

@endverbatim
  * @{
  */
 
/**
  * @brief  Deinitializes the WFE registers to their default reset value.
  * @param  None
  * @retval None
  */
void WFE_DeInit(void)
{
  WFE->CR1 = WFE_CRX_RESET_VALUE;
  WFE->CR2 = WFE_CRX_RESET_VALUE;
  WFE->CR3 = WFE_CRX_RESET_VALUE;
  WFE->CR4 = WFE_CRX_RESET_VALUE;
}

/**
  * @brief  Set the source that can generate the wake-up event.
  * @param  WFE_Source: The wake-up event source .
  *          This parameter can be one of the following values:
  *            @arg WFE_Source_TIM2_EV0: TIM2 Update/Trigger and Break interrupt  
  *            @arg WFE_Source_TIM2_EV1: TIM2 Capture/Compare interrupt 
  *            @arg WFE_Source_TIM1_EV0: TIM1 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM1_EV1: TIM1 Capture/Compare interrupt 
  *            @arg WFE_Source_EXTI_EV0: I/O port interrupt from Pins 0
  *            @arg WFE_Source_EXTI_EV1: I/O port interrupt from Pins 1
  *            @arg WFE_Source_EXTI_EV2: I/O port interrupt from Pins 2
  *            @arg WFE_Source_EXTI_EV3: I/O port interrupt from Pins 3
  *            @arg WFE_Source_EXTI_EV4: I/O port interrupt from Pins 4
  *            @arg WFE_Source_EXTI_EV5: I/O port interrupt from Pins 5
  *            @arg WFE_Source_EXTI_EV6: I/O port interrupt from Pins 6
  *            @arg WFE_Source_EXTI_EV7: I/O port interrupt from Pins 7
  *            @arg WFE_Source_EXTI_EVB_G: I/O port interrupt from port B and G
  *            @arg WFE_Source_EXTI_EVD_H: I/O port interrupt from Port D and H
  *            @arg WFE_Source_EXTI_EVE_F: I/O port interrupt from Port E and F 
  *            @arg WFE_Source_ADC1_COMP_EV: ADC1, COMP1 and COMP2 interrupts
  *            @arg WFE_Source_TIM3_EV0: TIM3 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM3_EV1: TIM3 Capture/Compare interrupt
  *            @arg WFE_Source_TIM4_EV: TIM4 Update and Trigger interrupt
  *            @arg WFE_Source_SPI1_EV: SPI1 Rx and Tx interrupt
  *            @arg WFE_Source_I2C1_EV: I2C1 Rx and Tx interrupt
  *            @arg WFE_Source_USART1_EV: USART1 Rx and Tx interrupt
  *            @arg WFE_Source_DMA1CH01_EV: DMA1 channel 0 and  1 interrupt
  *            @arg WFE_Source_DMA1CH23_EV: DMA1 channel 2 and  3  interrupt 
  *            @arg WFE_Source_RTC_CSS_EV: RTC or CSS on LSE event
  *            @arg WFE_Source_SPI2_EV: SPI2 Rx and Tx interrupt
  *            @arg WFE_Source_USART2_EV: USART2 Rx and Tx interrupt
  *            @arg WFE_Source_USART3_EV: USART3 Rx and Tx interrupt
  *            @arg WFE_Source_TIM5_EV0: TIM5 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM5_EV1: TIM5 Capture/Compare interrupt                                                        
  * @param  NewState : The wake-up new state.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WFE_WakeUpSourceEventCmd(WFE_Source_T WFE_Source, FunctionalState NewState)
{
  uint8_t register_index = 0;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE(WFE_Source));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* The mask is reversed in order to  */
  register_index = (uint8_t)((uint16_t)WFE_Source >> 0x08);

  if (NewState != DISABLE)
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 |= (uint8_t)WFE_Source;
        break;

      case 2:
        WFE->CR2 |= (uint8_t)WFE_Source;
        break;

      case 3:
        WFE->CR3 |= (uint8_t)WFE_Source;
        break;

      case 4:
        WFE->CR4 |= (uint8_t)WFE_Source;
        break;

      default:
        break;
    }
  }
  else
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      case 2:
        WFE->CR2 &= (uint8_t)(~ (uint8_t)WFE_Source);
        break;

      case 3:
        WFE->CR3 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      case 4:
        WFE->CR4 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      default:
        break;
    }
  }
}

/**
  * @brief  Gets the status of the specified source event.
  * @param  WFE_Source: The wake-up event source.
  *          This parameter can be one of the following values:
  *            @arg WFE_Source_TIM2_EV0: TIM2 Update/Trigger and Break interrupt  
  *            @arg WFE_Source_TIM2_EV1: TIM2 Capture/Compare interrupt 
  *            @arg WFE_Source_TIM1_EV0: TIM1 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM1_EV1: TIM1 Capture/Compare interrupt 
  *            @arg WFE_Source_EXTI_EV0: I/O port interrupt from Pins 0
  *            @arg WFE_Source_EXTI_EV1: I/O port interrupt from Pins 1
  *            @arg WFE_Source_EXTI_EV2: I/O port interrupt from Pins 2
  *            @arg WFE_Source_EXTI_EV3: I/O port interrupt from Pins 3
  *            @arg WFE_Source_EXTI_EV4: I/O port interrupt from Pins 4
  *            @arg WFE_Source_EXTI_EV5: I/O port interrupt from Pins 5
  *            @arg WFE_Source_EXTI_EV6: I/O port interrupt from Pins 6
  *            @arg WFE_Source_EXTI_EV7: I/O port interrupt from Pins 7
  *            @arg WFE_Source_EXTI_EVB_G: I/O port interrupt from port B and G
  *            @arg WFE_Source_EXTI_EVD_H: I/O port interrupt from Port D and H
  *            @arg WFE_Source_EXTI_EVE_F: I/O port interrupt from Port E and F 
  *            @arg WFE_Source_ADC1_COMP_EV: ADC1, COMP1 and COMP2 interrupts
  *            @arg WFE_Source_TIM3_EV0: TIM3 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM3_EV1: TIM3 Capture/Compare interrupt
  *            @arg WFE_Source_TIM4_EV: TIM4 Update and Trigger interrupt
  *            @arg WFE_Source_SPI1_EV: SPI1 Rx and Tx interrupt
  *            @arg WFE_Source_I2C1_EV: I2C1 Rx and Tx interrupt
  *            @arg WFE_Source_USART1_EV: USART1 Rx and Tx interrupt
  *            @arg WFE_Source_DMA1CH01_EV: DMA1 channel 0 and  1 interrupt
  *            @arg WFE_Source_DMA1CH23_EV: DMA1 channel 2 and  3  interrupt 
  *            @arg WFE_Source_RTC_CSS_EV: RTC or CSS on LSE event
  *            @arg WFE_Source_SPI2_EV: SPI2 Rx and Tx interrupt
  *            @arg WFE_Source_USART2_EV: USART2 Rx and Tx interrupt
  *            @arg WFE_Source_USART3_EV: USART3 Rx and Tx interrupt
  *            @arg WFE_Source_TIM5_EV0: TIM5 Update/Trigger and Break interrupt
  *            @arg WFE_Source_TIM5_EV1: TIM5 Capture/Compare interrupt  
  * @retval Source Event state, ENABLE or DISABLE
  */
FunctionalState WFE_GetWakeUpSourceEventStatus(WFE_Source_T WFE_Source)
{
  FunctionalState status = DISABLE;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE(WFE_Source));

  switch (WFE_Source)
  {
    case WFE_Source_TIM2_EV0:
    case WFE_Source_TIM2_EV1:
    case WFE_Source_TIM1_EV0:
    case WFE_Source_TIM1_EV1:
    case WFE_Source_EXTI_EV0:
    case WFE_Source_EXTI_EV1:
    case WFE_Source_EXTI_EV2:
    case WFE_Source_EXTI_EV3:

      if ((WFE->CR1 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;

    case WFE_Source_EXTI_EV4:
    case WFE_Source_EXTI_EV5:
    case WFE_Source_EXTI_EV6:
    case WFE_Source_EXTI_EV7:
    case WFE_Source_EXTI_EVB_G:
    case WFE_Source_EXTI_EVD_H:
    case WFE_Source_EXTI_EVE_F:
    case WFE_Source_ADC1_COMP_EV:

      if ((WFE->CR2 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;
    case WFE_Source_TIM3_EV0:
    case WFE_Source_TIM3_EV1:
    case WFE_Source_TIM4_EV:
    case WFE_Source_SPI1_EV:
    case WFE_Source_I2C1_EV:
    case WFE_Source_USART1_EV:
    case WFE_Source_DMA1CH01_EV:
    case WFE_Source_DMA1CH23_EV:

      if ((WFE->CR3 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;

    case WFE_Source_TIM5_EV0:
    case WFE_Source_TIM5_EV1:
    case WFE_Source_AES_EV:
    case WFE_Source_SPI2_EV:
    case WFE_Source_USART2_EV:
    case WFE_Source_USART3_EV:
    case WFE_Source_RTC_CSS_EV:

      if ((WFE->CR4 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;
    default:
      break;
  }
  return status;
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
