//4xled.c
//19.05.2018 функции для работы с 4хLED-индикатором при посегментном высвечивании
//********************************************************
#include <4xled.h>
//********************************************************
//переменная в которой хранится текущее значение высвечив сегмента
static volatile SEGMENT_t segment = SEG_A;
//получить отображаемый сегмент
SEGMENT_t getSegment(void)
{
	return segment;
}
//установить следующий сегмент
void setSegment(SEGMENT_t newSegment)
{
	segment = newSegment;
}

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
//функции управления сегментами индикатора
void display_off()//погасить все сегменты
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_A()//вкл сегммент А
{
	SEG_A_ON; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;	
}
void display_on_B()//вкл сегммент B
{
	SEG_A_OFF; SEG_B_ON; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_C()//вкл сегммент C
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_D()//вкл сегммент D
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_ON; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_E()//вкл сегммент E
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_ON; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_F()//вкл сегммент F
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_ON; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_G()//вкл сегммент G
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
}
void display_on_DP()//вкл сегммент DP
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_ON;
}

//*******************************************************************
//вызов функции разбивает десятичное число (uint16_t num) на разряды
void razradCalculate(uint16_t num, uint8_t *razradDigits)
{
		if (num >9999) {num = 0;} //ограничили индикатор от переполнения(uint16_t num_МАХ=65535)
		uint8_t razr = 0;//значение разрядов
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
//библиотека символов индикатора (вкл разрядов индикатора)
//для цифр от 0 до 9
//-----------------------------------------------------------
void setRazradForSegmentA (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==4)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента А
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_A();//засветили сегмент А
}
void setRazradForSegmentB (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==5 || razradDigits[i]==6)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента B
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_B();//засветили сегмент B
}
void setRazradForSegmentC (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==2)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента C
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_C();//засветили сегмент C
}
void setRazradForSegmentD (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==4 || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента D
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_D();//засветили сегмент D
}
void setRazradForSegmentE (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==0 || razradDigits[i]==2 || razradDigits[i]==6 || razradDigits[i]==8)
		{
			razradFlag[i] = 1;
		}
		else {razradFlag[i] = 0;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента E
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_E();//засветили сегмент E
}
void setRazradForSegmentF (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==2  || razradDigits[i]==3 || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента F
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_F();//засветили сегмент F
}
void setRazradForSegmentG (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//флаг вкл i-го разряда
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==0 || razradDigits[i]==1  || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента G
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_G();//засветили сегмент G
}
void setRazradForSegmentDP (uint8_t point)
{
	display_off();//погасили индикатор перед сменой информации
	//вкл разряды для сегмента DP
	if(point == 1) 		{R1_ON;   R2_OFF;  R3_OFF;  R4_OFF;}//десятичная точка в 1-м разряде(младшем)
	else if(point == 2) {R1_OFF;  R2_ON;   R3_OFF;  R4_OFF;}//десятичная точка во 2-м разряде
	else if(point == 3) {R1_OFF;  R2_OFF;  R3_ON;   R4_OFF;}//десятичная точка в 3-м разряде
	else if(point == 4) {R1_OFF;  R2_OFF;  R3_OFF;  R4_ON;}//десятичная точка в 4-м разряде
	display_on_DP();//засветили сегмент DP
}
//******************************************************************
//--------высвечивание индикатора---------------------
//каждый вызов функции высвечивает 1н сегмент всех разрядов индикатора.
//Нужно вызвать функцию 8-м раз что бы высветить все число(не зависимо от разрядности индикатора)
void display(uint8_t *razradDigits)
{//в матрице razradDigits[4] - хранятся значения разрядов индикатора.
		switch (getSegment())
		{
			        case SEG_A:
						{
							setRazradForSegmentA (razradDigits);//вкл разряды сегмента А & засветили сегмент А
							setSegment(SEG_B);
							break;
						}
					case SEG_B:
						{
							setRazradForSegmentB (razradDigits);//вкл разряды сегмента B & засветили сегмент B
							setSegment(SEG_C);
							break;
						}
					case SEG_C:
						{
							setRazradForSegmentC (razradDigits);//вкл разряды сегмента C & засветили сегмент C
							setSegment(SEG_D);
							break;
						}
					case SEG_D:
						{
							setRazradForSegmentD (razradDigits);//вкл разряды сегмента D
							setSegment(SEG_E);
							break;
						}
					case SEG_E:
						{
							setRazradForSegmentE (razradDigits);//вкл разряды сегмента E
							setSegment(SEG_F);
							break;
						}
					case SEG_F:
						{
							setRazradForSegmentF (razradDigits);//вкл разряды сегмента F
							setSegment(SEG_G);
							break;
						}
					case SEG_G:
						{
							setRazradForSegmentG (razradDigits);//вкл разряды сегмента G
							setSegment(SEG_DP);
							break;
						}
					case SEG_DP:
						{
							setRazradForSegmentDP (3);//вкл разряды сегмента DP
							setSegment(SEG_A);
							break;
						}
		}
}
//******************************************************************
