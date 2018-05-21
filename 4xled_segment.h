//4xled.h
//19.05.2018 ������� ��� ������ � 4 ��������� �����������.
//	���������� 7-���������� 4-��������� �����������. ������������ ���������(����������� ��� �������, 
//��������������� ���� ������ �������������� �����, ����� ��� ��������������� �������). 
//��� ����� ������� ��� �������=���� ������ ��������(�.�. ����� 5�� � ����� ��������� ����������� �� �����,
//� ���������� ��������). ��� ��������� - ���� ���=Isegm*Nrazradov, ��� 4xled Isegm_���=20mA).
//	���������� �������� �� STM32 F030 F4P6
/*----������ � �����������-----------
1. ������������ GPIO - void gpio_4xled_init();
2. ����������� ��� ����������� ����� ������ ���� ��� �������� � �������� � - uint16_t num	
3. ����� ������� void razradCalculate (uint16_t num, uint8_t *razradDigits) - ������������� ���������� ����� 
	uint16_t num � ����� �������� ���������� uint8_t razradDigits[4].
4. ����� �������� void display(uint8_t *razradDigits) - 1� ����� �������� 1 �������, ������� ��� ������������
   ���������� 8-� ������� ������� �� �������� �� ����� ��������. ������� 3��, ����������� ��������,
   ����� �� ������ ���������.
*/
//********************************************************
#ifndef __4XLED_H__
#define __4XLED_H__

#include <stm32f0xx.h>
#include <system_stm32f0xx.h>
#include "string.h" //����������� ������� ��
#include "stdlib.h"

//********************************************************
//------��� + ���� ��������� ����������------------------------
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

//------��� + ���� �������� ����������------------------------
#define R1_OFF    GPIOF->BSRR |= GPIO_BSRR_BS_1
#define R1_ON   GPIOF->BSRR |= GPIO_BSRR_BR_1

#define R2_OFF    GPIOF->BSRR |= GPIO_BSRR_BS_0
#define R2_ON   GPIOF->BSRR |= GPIO_BSRR_BR_0

#define R3_OFF    GPIOA->BSRR |= GPIO_BSRR_BS_10
#define R3_ON   GPIOA->BSRR |= GPIO_BSRR_BR_10

#define R4_OFF    GPIOA->BSRR |= GPIO_BSRR_BS_9
#define R4_ON   GPIOA->BSRR |= GPIO_BSRR_BR_9

//********************************************************
//������� ������������� �������
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
//��������� c��������
SEGMENT_t getSegment(void);//�������� ������� ���������
void setSegment(SEGMENT_t newSegment);//���������� ���������

//********************************************************
//������������� GPIO � ��������� �� � �������� ���������(��� ����)
void gpio_4xled_init(void);

//********************************************************
//�������� ����������� ����� (uint16_t num) � ����� �������� ���������� (uint8_t razradDigits[4])
void razradCalculate(uint16_t num, uint8_t *razradDigits);

//********************************************************
//������ ����� ������� ����������� 1� ������� ���� �������� ��(uint8_t *razradDigits), 
//	��� ������������ ����� ����� ����� ������� ������� 8 ���
void display(uint8_t *razradDigits);

#endif /* __4XLED_H__ */
