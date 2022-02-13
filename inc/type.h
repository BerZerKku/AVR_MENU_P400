/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_type.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the common data types used for the
*                      STM32F10x firmware library.
********************************************************************************
* History:
* 04/02/2007: V0.2
* 02/05/2007: V0.1
* 09/29/2006: V0.01
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_TYPE_H
#define __STM32F10x_TYPE_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef signed long s32;
typedef signed int s16;
typedef signed char s8;

typedef volatile signed long vs32;
typedef volatile signed int vs16;
typedef volatile signed char vs8;

typedef unsigned long u32;
typedef unsigned int u16;
typedef unsigned char u8;

typedef unsigned long const uc32; /* Read Only */
typedef unsigned short int uc16; /* Read Only */
typedef unsigned char const uc8; /* Read Only */

typedef volatile unsigned long vu32;
typedef volatile unsigned int vu16;
typedef volatile unsigned char vu8;

typedef volatile unsigned long const vuc32; /* Read Only */
typedef volatile unsigned int const vuc16; /* Read Only */
typedef volatile unsigned char const vuc8; /* Read Only */

//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum { RESET = 0,
    SET = !RESET } FlagStatus,
    ITStatus;

typedef enum { DISABLE = 0,
    ENABLE = !DISABLE } FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) ((STATE == DISABLE) || (STATE == ENABLE))

typedef enum { ERROR = 0,
    SUCCESS = !ERROR } ErrorStatus;

#define U8_MAX ((u8)255)
#define S8_MAX ((s8)127)
#define S8_MIN ((s8)-128)
#define U16_MAX ((u16)65535u)
#define S16_MAX ((s16)32767)
#define S16_MIN ((s16)-32768)
#define U32_MAX ((u32)4294967295uL)
#define S32_MAX ((s32)2147483647)
#define S32_MIN ((s32)2147483648uL)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __STM32F10x_TYPE_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
