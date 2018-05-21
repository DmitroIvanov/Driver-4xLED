//4xled.h
//19.05.2018 функции для работы с 4 разрядным индикатором.
//	Управление 7-сегментным 4-разрядным индикатором. ПОСЕГМЕНТНАЯ индикация(параллельно вкл разряды, 
//соответствующие всем цифрам высвечиваемого числа, после вкл соответствующий сегмент). 
//При таком подходе ток разряда=току одного сегмента(т.е. около 5мА и можно исключить транзисторы из схемы,
//а установить резистор). Для сегментов - макс ток=Isegm*Nrazradov, для 4xled Isegm_МАХ=20mA).
//	управление напрямую от STM32 F030 F4P6
/*----работа с библиотекой-----------
1. инициировать GPIO - void gpio_4xled_init();
2. необходимое для отображения число должны быть уже получено и хранится в - uint16_t num	
3. вызов функции void razradCalculate (uint16_t num, uint8_t *razradDigits) - пересчитывает десятичное число 
	uint16_t num в цифры разрядов индикатора uint8_t razradDigits[4].
4. после вызываем void display(uint8_t *razradDigits) - 1н вызов высвечив 1 сегмент, поэтому для высвечивания
   необходимо 8-м вызовов функции не зависимо от числа разрядов. Частота 3мс, подбирается эксперим,
   чтобы не моргал индикатор.
*/
//********************************************************
#ifndef __4XLED_H__
#define __4XLED_H__

#include <stm32f0xx.h>
#include <system_stm32f0xx.h>
#include "string.h" //Подключение функций Си
#include "stdlib.h"

//********************************************************
//------вкл + выкл сегментов индикатора------------------------
#define SEG_A_ON    GPIOA->BSRR |= GPIO_BSRR_BS_7
#define SEG_A_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_7

#define SEG_B_ON    GPIOA->BSRR |= GPIO_BSRR_BS_5
#define SEG_B_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_5

#define SEG_C_ON    GPIOA->BSRR |= GPIO_BSRR_BS_1
#define SEG_C_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_1

#define SEG_D_ON    GPIOA->BSRR |= GPIO_BSRR_BS_3
#define SEG_D_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_3

#define SEG_E_ON    GPIOA->BSRR |= GPIO_BSRR_BS_4
#define SEG_E_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_4

#define SEG_F_ON    GPIOA->BSRR |= GPIO_BSRR_BS_6
#define SEG_F_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_6

#define SEG_G_ON    GPIOA->BSRR |= GPIO_BSRR_BS_0
#define SEG_G_OFF   GPIOA->BSRR |= GPIO_BSRR_BR_0

#define SEG_DP_ON   GPIOA->BSRR |= GPIO_BSRR_BS_2
#define SEG_DP_OFF  GPIOA->BSRR |= GPIO_BSRR_BR_2

//------вкл + выкл разрядов индикатора------------------------
#define R1_OFF    GPIOF->BSRR |= GPIO_BSRR_BS_1
#define R1_ON   GPIOF->BSRR |= GPIO_BSRR_BR_1

#define R2_OFF    GPIOF->BSRR |= GPIO_BSRR_BS_0
#define R2_ON   GPIOF->BSRR |= GPIO_BSRR_BR_0

#define R3_OFF    GPIOA->BSRR |= GPIO_BSRR_BS_10
#define R3_ON   GPIOA->BSRR |= GPIO_BSRR_BR_10

#define R4_OFF    GPIOA->BSRR |= GPIO_BSRR_BS_9
#define R4_ON   GPIOA->BSRR |= GPIO_BSRR_BR_9

//********************************************************
//текущий высвечиваемый сегмент
typedef enum {
	SEG_A,
	SEG_B,
	SEG_C,
	SEG_D,
	SEG_E,
	SEG_F,
	SEG_G,
	SEG_DP
} SEGMENT_t;
//состояние cегментов
SEGMENT_t getSegment(void);//получить текущее состояние
void setSegment(SEGMENT_t newSegment);//установить состояние

//********************************************************
//инициализация GPIO и установка их в исходное положение(все выкл)
void gpio_4xled_init(void);

//********************************************************
//пересчет десятичного числа (uint16_t num) в цифры разрядов индикатора (uint8_t razradDigits[4])
void razradCalculate(uint16_t num, uint8_t *razradDigits);

//********************************************************
//каждый вызов функции высвечивает 1н сегмент всех разрядов из(uint8_t *razradDigits), 
//	для высвечивания всего числа нужно вызвать функцию 8 раз
void display(uint8_t *razradDigits);

#endif /* __4XLED_H__ */
