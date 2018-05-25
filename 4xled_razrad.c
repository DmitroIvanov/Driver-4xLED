//4xled.c
//функции для работы с 4 разрядным LED-индикатором (Vmetr=0...30V)
//********************************************************
#include <4xled.h>

//********************************************************
void gpio_4xled_init(void)
{
//--------GPIO_Init---------------------------------
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOFEN;
	//PA0 - SEG_G (output)
	GPIOA->MODER |= GPIO_MODER_MODER0_0;
	//PA1 - SEG_C (output)
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	//PA2 - SEG_DP (output)
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	//PA3 - SEG_D (output)
	GPIOA->MODER |= GPIO_MODER_MODER3_0;
	//PA4 - SEG_E (output)
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	//PA5 - SEG_B (output)
	GPIOA->MODER |= GPIO_MODER_MODER5_0;	
	//PA6 - SEG_F (output)
	GPIOA->MODER |= GPIO_MODER_MODER6_0;
	//PA7 - SEG_A (output)
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
	
	//PF1 - R1 (output)
	GPIOF->MODER |= GPIO_MODER_MODER1_0;
	//PF0 - R2 (output)
	GPIOF->MODER |= GPIO_MODER_MODER0_0;
	//PA10 - R3 (output)
	GPIOA->MODER |= GPIO_MODER_MODER10_0;
	//PA9 - R4 (output)
	GPIOA->MODER |= GPIO_MODER_MODER9_0;
	
//-----Исходное положене ног - все выкл------------------------------
	R1_OFF; R2_OFF; R3_OFF; R4_OFF;
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
//*******************************************************************
//функции управления разрядами индикатора
void display_off()//погасить все разряды
{
	R1_OFF; R2_OFF; R3_OFF; R4_OFF;
}
void display_on_1()//вкл 1й разряд
{
	R1_ON; R2_OFF; R3_OFF; R4_OFF;
}
void display_on_2()//вкл 2й разряд
{
	R1_OFF; R2_ON; R3_OFF; R4_OFF;
}
void display_on_3()//вкл 3й разряд
{
	R1_OFF; R2_OFF; R3_ON; R4_OFF;
}
void display_on_4()//вкл 4й разряд
{
	R1_OFF; R2_OFF; R3_OFF; R4_ON;
}
void set_zero()//вкл пустое место
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
//*******************************************************************
//библиотека символов индикатора (вкл сегменты индикатора)
//-----------------------------------------------------------
void set_segment (uint8_t segment_simvol)
{
	switch (segment_simvol)
	{
		case 0: //цифра 0
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 1: //цифра 1
			{
				SEG_A_OFF; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 2: //цифра 2
			{
				SEG_A_ON; SEG_B_ON; SEG_C_OFF; SEG_D_ON; SEG_E_ON; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 3: //цифра 3
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 4: //цифра 4
			{
				SEG_A_OFF; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 5: //цифра 5
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 6: //цифра 6
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 7: //цифра 7
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 8: //цифра 8
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 9: //цифра 9
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 10: //буква А
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_ON;
				break;
			}
		case 11: //буква b
			{
				SEG_A_OFF; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_ON;
				break;
			}
		case 12: //буква C
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_OFF; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_OFF; SEG_DP_ON;
				break;
			}
		default://минус и без точек
		    {
			    SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
		    }
	}
}
//******************************************************************
//вызов функции разбивает десятичное число (uint16_t num) на разряды для вывода на индикатор
void razradCalculate(uint16_t num, uint8_t *razradDigits)
{
		if (num >9999) {num = 0;} //ограничили индикатор от переполнения(uint16_t num_МАХ=65535)
		uint8_t razr = 0;
		//--- разбили на разряды в формате индикатора ----
		while(num >= 1000)
		{
			num -= 1000;
			razr++;//вычислии цифру 4 разряда
		}
		razradDigits[3] = razr;
		razr =0;		
		
		while(num >= 100)
		{
			num -= 100;
			razr++;//вычислии цифру 3 разряда
		}
		razradDigits[2] = razr;
		razr = 0;

		while(num >= 10)
		{
			num -= 10;
			razr++;//вычислии цифру 2 разряда
		}
		razradDigits[1] = razr;
		razr = 0;

		razr = num;
		razradDigits[0] = razr;
}
//******************************************************************
//--------высвечивание индикатора---------------------
//каждый вызов функции высвечивает 1н разряд индикатора.
//Нужно вызвать функцию 4-ре раза что бы высветить все число.
void display(uint8_t *razradDigits)
{   	
	//в матрице razradDigits[4] - хранятся значения разрядов индикатора.
		static uint8_t razrad_num=0;
		uint8_t segment_simvol;
		switch (razrad_num)
		{
			        case 0:
						{
							segment_simvol = razradDigits[0];
							display_off();//погасили индикатор перед сменой информации
							set_segment (segment_simvol);//вкл сегменты разряда 1
							display_on_1();//засветили 1-й разряд
							break;
						}
					case 1:
						{
							segment_simvol = razradDigits[1];
							display_off();//погасили индикатор перед сменой информации
							set_segment (segment_simvol);//вкл сегменты разряда 2
							display_on_2();//засветили 2-й разряд
							break;
						}
					case 2:
						{
							segment_simvol = razradDigits[2];
							display_off();
							set_segment (segment_simvol);
							SEG_DP_ON;//добавили десятичную точку после 2го разряда							
							display_on_3();
							break;
						}
					case 3:
						{
							segment_simvol = razradDigits[3];
							if (segment_simvol == 0) {//гасим не значащий ноль
								set_zero();
							}else {
								display_off();
								set_segment (segment_simvol);
							}
							display_on_4();						
							break;
						}
		}
			    //счетчик - какой разряд высвечивать
				if (razrad_num == 3) {razrad_num = 0;}
			   	else {razrad_num++;}
}
//******************************************************************
