/**
  ******************************************************************************
  * @file    air001xx_hal_cortex.c
  * @author  MCU Application Team
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and Configuration functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    *** How to configure Interrupts using CORTEX HAL driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex M0+ exceptions are managed by CMSIS functions.
      (#) Enable and Configure the priority of the selected IRQ Channels.
             The priority can be 0..3.

        -@- Lower priority values gives higher priority.
        -@- Priority Order:
            (#@) Lowest priority.
            (#@) Lowest hardware priority (IRQn position).

      (#)  Configure the priority of the selected IRQ Channels using HAL_NVIC_SetPriority()

      (#)  Enable the selected IRQ Channels using HAL_NVIC_EnableIRQ()

      -@-  Negative value of IRQn_Type are not allowed.

    *** How to configure Systick using CORTEX HAL driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base.

   (+) The HAL_SYSTICK_Config()function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value (0x03).
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.

   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the macro
       __HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       HAL_SYSTICK_Config() function call. The __HAL_CORTEX_SYSTICKCLK_CONFIG() macro is defined
       inside the air001xx_hal_cortex.h file.

   (+) You can change the SysTick IRQ priority by calling the
       HAL_NVIC_SetPriority(SysTick_IRQn,...) function just after the HAL_SYSTICK_Config() function
       call. The HAL_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for HAL_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) AirM2M.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "air001xx_hal.h"

/** @addtogroup AIR001xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @{
  */

#ifdef HAL_CORTEX_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup CORTEX_Exported_Functions
  * @{
  */


/** @addtogroup CORTEX_Exported_Functions_Group1
 *  @brief    Initialization and Configuration functions
 *
@verbatim
  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
      This section provides the CORTEX HAL driver functions allowing to configure Interrupts
      Systick functionalities

@endverbatim
  * @{
  */

/**
  * @brief Sets the priority of an interrupt.
  * @param IRQn External interrupt number .
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *
  * @param PreemptPriority The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 3.
  *         A lower priority value indicates a higher priority
  * @param SubPriority the subpriority level for the IRQ channel.
  *         with air001xx devices, this parameter is a dummy value and it is ignored, because
  *         no subpriority supported in Cortex M0+ based products.
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
  NVIC_SetPriority(IRQn,PreemptPriority);
}

/**
  * @brief  Enable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file
  * @retval None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file (air001xx.h))
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}

/**
  * @brief  Initiate a system reset request to reset the MCU.
  * @retval None
  */
void HAL_NVIC_SystemReset(void)
{
  /* System Reset */
  NVIC_SystemReset();
}

uint32_t SysTick_Config2(uint32_t ticks) {
    if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk) {
        return (1UL);                                                   /* Reload value impossible */
    }

    SysTick->LOAD = (uint32_t)(ticks - 1UL);                         /* set reload register */
    NVIC_SetPriority(SysTick_IRQn, (1) - 1UL); /* set Priority for Systick Interrupt */
    SysTick->VAL = 0UL;                                             /* Load the SysTick Counter Value */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
    return (0UL);                                                     /* Function successful */
}

/**
  * @brief  Initialize the System Timer with interrupt enabled and start the System Tick Timer (SysTick):
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
    return SysTick_Config(TicksNumb);
//   return SysTick_Config2(TicksNumb);
}
/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2
 *  @brief   Cortex control functions
 *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
    [..]
      This subsection provides a set of functions allowing to control the CORTEX
      (NVIC, SYSTICK, MPU) functionalities.


@endverbatim
  * @{
  */

/**
  * @brief  Get the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file (air001xx.h))
  * @retval None
  */
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn)
{
  /* Get priority for Cortex-M system or device specific interrupts */
  return NVIC_GetPriority(IRQn);
}

/**
  * @brief  Set Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file (air001xx.h))
  * @retval None
  */
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Set interrupt pending */
  NVIC_SetPendingIRQ(IRQn);
}

/**
  * @brief  Get Pending Interrupt (read the pending register in the NVIC
  *         and return the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file (air001xx.h))
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Return 1 if pending else 0 */
  return NVIC_GetPendingIRQ(IRQn);
}

/**
  * @brief  Clear the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete AirMCU Devices IRQ Channels list, please refer to the appropriate CMSIS device file (air001xx.h))
  * @retval None
  */
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Clear pending interrupt */
  NVIC_ClearPendingIRQ(IRQn);
}

/**
  * @brief  Configure the SysTick clock source.
  * @param CLKSource specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
  if (CLKSource == SYSTICK_CLKSOURCE_HCLK)
  {
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
  }
  else
  {
    SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
  }
}

/**
  * @brief  Handle SYSTICK interrupt request.
  * @retval None
  */
void HAL_SYSTICK_IRQHandler(void)
{
  HAL_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
__weak void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}




/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_CORTEX_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT AirM2M *****END OF FILE****/