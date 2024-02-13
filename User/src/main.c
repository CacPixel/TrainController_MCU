#include "main.h"
#include "air001xx_hal.h"

UART_HandleTypeDef UartHandle;

void usart1_init(void);
void gpio_init(void);
void disable_swd(void);
void rcc_init(void);
void get_notch_status(void);

volatile uint8_t notch_status = 0x00;
volatile uint8_t prev_status = 0x00;

int main(void) {
    rcc_init();
    HAL_Init();
    gpio_init();
    usart1_init();
    if (!P5_VALUE) {
        while (1) {
            while (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_TXE) == 0);
            UartHandle.Instance->DR = 0x00;
            HAL_Delay(1000);
        }
    }
    disable_swd();
    get_notch_status();
    prev_status = notch_status;
    while (1) {
        get_notch_status();
        while (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_TXE) == 0) {}
        if (prev_status != notch_status) {
            UartHandle.Instance->DR = notch_status;
        }
        prev_status = notch_status;
        // HAL_Delay(1);
    }
}

void get_notch_status(void) {
    if (!P5_VALUE) {
        HAL_Delay(1);
        if (!P5_VALUE) {
            notch_status = NOTCH_P5;
            return;
        }
    } else if (!P4_VALUE) {
        HAL_Delay(1);
        if (!P4_VALUE) {
            notch_status = NOTCH_P4;
            return;
        }
    } else if (!P3_VALUE) {
        HAL_Delay(1);
        if (!P3_VALUE) {
            notch_status = NOTCH_P3;
            return;
        }
    } else if (!P2_VALUE) {
        HAL_Delay(1);
        if (!P2_VALUE) {
            notch_status = NOTCH_P2;
            return;
        }
    } else if (!P1_VALUE) {
        HAL_Delay(1);
        if (!P1_VALUE) {
            notch_status = NOTCH_P1;
            return;
        }
    } else if (!N_VALUE) {
        HAL_Delay(1);
        if (!N_VALUE) {
            notch_status = NOTCH_N;
            return;
        }
    } else if (!B1_VALUE) {
        HAL_Delay(1);
        if (!B1_VALUE) {
            notch_status = NOTCH_B1;
            return;
        }
    } else if (!B2_VALUE) {
        HAL_Delay(1);
        if (!B2_VALUE) {
            notch_status = NOTCH_B2;
            return;
        }
    } else if (!B3_VALUE) {
        HAL_Delay(1);
        if (!B3_VALUE) {
            notch_status = NOTCH_B3;
            return;
        }
    } else if (!B4_VALUE) {
        HAL_Delay(1);
        if (!B4_VALUE) {
            notch_status = NOTCH_B4;
            return;
        }
    } else if (!B5_VALUE) {
        HAL_Delay(1);
        if (!B5_VALUE) {
            notch_status = NOTCH_B5;
            return;
        }
    } else if (!B6_VALUE) {
        HAL_Delay(1);
        if (!B6_VALUE) {
            notch_status = NOTCH_B6;
            return;
        }
    } else if (!B7_VALUE) {
        HAL_Delay(1);
        if (!B7_VALUE) {
            notch_status = NOTCH_B7;
            return;
        }
    } else if (!B8_VALUE) {
        HAL_Delay(1);
        if (!B8_VALUE) {
            notch_status = NOTCH_B8;
            return;
        }
    } else if (!EB_VALUE) {
        HAL_Delay(1);
        if (!EB_VALUE) {
            notch_status = NOTCH_EB;
            return;
        }
    } else {
        HAL_Delay(1);
        return;
    }
}

void rcc_init(void) {
    RCC_PLLInitTypeDef sPLL = {
        .PLLState = RCC_PLL_ON,
        .PLLSource = RCC_PLLSOURCE_HSI,
    };
    RCC_OscInitTypeDef sOscInit = {
        .OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI,
        .HSEState = RCC_HSE_OFF,
        .LSEState = RCC_LSE_OFF,
        .HSIState = RCC_HSI_ON,
        .LSIState = RCC_LSI_ON,
        .HSIDiv = RCC_HSI_DIV1,
        .HSICalibrationValue = RCC_HSICALIBRATION_24MHz,
        .PLL = sPLL,
    };
    HAL_RCC_OscConfig(&sOscInit);

    RCC_ClkInitTypeDef sClk = {
        .ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1,
        .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1,
    };

    __HAL_RCC_PLL_ENABLE();
    HAL_RCC_ClockConfig(&sClk, FLASH_LATENCY_1);
}

void gpio_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitTypeDef gpio = { 0 };
    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3
        | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
        | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &gpio);

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOF, &gpio);
}

void disable_swd(void) {
    GPIO_InitTypeDef gpio = { 0 };
    gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);
}

void usart1_init(void) {
    __HAL_RCC_USART1_CLK_ENABLE();
    UartHandle.Instance = USART1;
    UartHandle.Init.BaudRate = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode = UART_MODE_TX;
    HAL_UART_Init(&UartHandle);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART1) {
        GPIO_InitTypeDef gpio = { 0 };
        gpio.Pin = GPIO_PIN_2;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = GPIO_AF1_USART1;
        HAL_GPIO_Init(GPIOA, &gpio);
    }
}