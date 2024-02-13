#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air001xx_hal.h"

#define EB_VALUE        (GPIOA->IDR & (1<<13))
#define B8_VALUE        (GPIOA->IDR & (1<<14))
#define B7_VALUE        (GPIOB->IDR & (1<<1))
#define B6_VALUE        (GPIOB->IDR & (1<<2))
#define B5_VALUE        (GPIOB->IDR & (1<<0))
#define B4_VALUE        (GPIOA->IDR & (1<<7))
#define B3_VALUE        (GPIOA->IDR & (1<<4))
#define B2_VALUE        (GPIOA->IDR & (1<<3))
#define B1_VALUE        (GPIOA->IDR & (1<<1))
#define N_VALUE         (GPIOA->IDR & (1<<0))
#define P1_VALUE        (GPIOF->IDR & (1<<1))
#define P2_VALUE        (GPIOF->IDR & (1<<0))
#define P3_VALUE        (GPIOA->IDR & (1<<5))
#define P4_VALUE        (GPIOA->IDR & (1<<6))
#define P5_VALUE        (GPIOB->IDR & (1<<3))


#define NOTCH_ERROR     0x00
#define NOTCH_P5        0x11
#define NOTCH_P4        0x22
#define NOTCH_P3        0x33
#define NOTCH_P2        0x44
#define NOTCH_P1        0x55
#define NOTCH_N         0x66
#define NOTCH_B1        0x77
#define NOTCH_B2        0x88
#define NOTCH_B3        0x99
#define NOTCH_B4        0xaa
#define NOTCH_B5        0xbb
#define NOTCH_B6        0xcc
#define NOTCH_B7        0xdd
#define NOTCH_B8        0xee
#define NOTCH_EB        0xff



    extern UART_HandleTypeDef UartHandle;


#ifdef __cplusplus
}
#endif

#endif